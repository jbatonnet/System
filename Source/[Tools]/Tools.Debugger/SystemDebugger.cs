using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.IO;
using System.IO.Pipes;
using System.Linq;
using System.Text;

using Microsoft.VisualStudio.Shared.VSCodeDebugProtocol;
using Microsoft.VisualStudio.Shared.VSCodeDebugProtocol.Messages;
using Microsoft.VisualStudio.Shared.VSCodeDebugProtocol.Utilities;

using Newtonsoft.Json.Linq;

using Tools.Debugger.Model;
using Tools.Debugger.Wrappers;
using Tools.Gdb;
using Tools.Pdb;
using Tools.VirtualMachine;

using Interlocked = System.Threading.Interlocked;

namespace SampleDebugAdapter
{
    internal class SampleDebugAdapter : DebugAdapterBase
    {
        private NamedPipeServerStream serialStream;
        private List<PdbSession> pdbSessions = new List<PdbSession>();
        private VirtualMachine virtualMachine;
        private x86GdbClient gdbClient;

        private PdbSymbol debuggerAttachedField, debuggerInitializeFunction, debuggerBreakFunction;
        //private PdbSymbol exceptionAssertFunction;
        private PdbSymbol profilerTraceFunction;
        private PdbSymbol taskFirstField, taskKernelField, taskCurrentField, processesField;

        private Pointer<Task> firstTask, kernelTask, currentTask;
        //private Collection<Pointer<Process>> Processes;

        private int nextInternalFrameId = 0;
        private ConcurrentDictionary<int, InternalFrame> internalFrames = new ConcurrentDictionary<int, InternalFrame>();
        private ConcurrentDictionary<string, List<GdbBreakpoint>> gdbBreakpoints = new ConcurrentDictionary<string, List<GdbBreakpoint>>();

        private byte[] serialBuffer = new byte[1];
        private string serialLine = "";

        internal SampleDebugAdapter(Stream stdIn, Stream stdOut)
        {
            base.InitializeProtocolClient(stdIn, stdOut);

            AppDomain.CurrentDomain.UnhandledException += CurrentDomain_UnhandledException;
        }
        private void CurrentDomain_UnhandledException(object sender, UnhandledExceptionEventArgs e)
        {
            if (System.Diagnostics.Debugger.IsAttached)
                System.Diagnostics.Debugger.Break();
            else
                System.Diagnostics.Debugger.Launch();
        }

        internal void Run()
        {
            Protocol.Run();
        }
        private void LoadOptions(JObject optionsObject)
        {
            bool? debuggerInception = optionsObject["debugging"]["inception"].Value<bool?>();
            if (debuggerInception == true)
            {
                if (System.Diagnostics.Debugger.IsAttached)
                    System.Diagnostics.Debugger.Break();
                else
                    System.Diagnostics.Debugger.Launch();
            }
        }

        private void InitializeVirtualMachine()
        {
            string virtualMachinePath = Path.Combine(Bootstrap.Root, @"VMware\Disk.vmdk");
            if (!File.Exists(virtualMachinePath))
                throw new FileNotFoundException("Could not find virtual machine", virtualMachinePath);

            virtualMachine = new QemuVirtualMachine(virtualMachinePath);
            virtualMachine.Stopped += VirtualMachine_Stopped;

            if (virtualMachine.Running)
                virtualMachine.Stop();

            virtualMachine.Start();
        }
        private void InitializeSerial()
        {
            serialStream = new NamedPipeServerStream("System", PipeDirection.InOut, 1, PipeTransmissionMode.Byte, PipeOptions.Asynchronous);
            serialStream.BeginWaitForConnection(SerialStream_WaitForConnection, null);
        }
        private void InitializeSymbols()
        {
            string pdbPath = Path.Combine(Bootstrap.Source, @"Kernel\Kernel.pdb");
            if (!File.Exists(pdbPath))
                throw new FileNotFoundException("Could not find kernel symbols", pdbPath);

            PdbFile pdbFile = new PdbFile(pdbPath);
            pdbSessions.Add(pdbFile.OpenSession(0x100000));

            debuggerAttachedField = FindSymbolByName("Debugger::attached");
            debuggerInitializeFunction = FindSymbolByName("Debugger::Initialize");
            debuggerBreakFunction = FindSymbolByName("System::Runtime::Debugger::Break");

            profilerTraceFunction = FindSymbolByName("System::Runtime::Profiler::Trace");

            taskFirstField = FindSymbolByName("Task::First");
            taskKernelField = FindSymbolByName("Task::Kernel");
            taskCurrentField = FindSymbolByName("Task::Current");
            processesField = FindSymbolByName("System::Runtime::Process::processes");
        }
        private void InitializeGdb()
        {
            gdbClient = new x86GdbClient();
            gdbClient.BreakpointHit += Gdb_BreakpointHit;

            if (gdbClient.Running)
                gdbClient.Break();

            gdbClient.Continue();
            System.Threading.Thread.Sleep(1750);
            gdbClient.Break();

            gdbClient.Breakpoints.Add(GdbBreakpointType.Memory, debuggerBreakFunction.VirtualAddress);
            gdbClient.Memory.Write(debuggerAttachedField.VirtualAddress, 0x01);

            //gdbClient.Continue();
        }
        private void InitializeWrappers()
        {
            firstTask = new Pointer<Task>(gdbClient.Memory, taskFirstField.VirtualAddress);
            kernelTask = new Pointer<Task>(gdbClient.Memory, taskKernelField.VirtualAddress);
            currentTask = new Pointer<Task>(gdbClient.Memory, taskCurrentField.VirtualAddress);
            //Processes = new Collection<Pointer<Process>>(gdbClient.Memory, processesField.VirtualAddress);
        }

        private PdbSymbol FindSymbolByName(string name)
        {
            PdbSymbol result = pdbSessions
                .SelectMany(s => s.GlobalScope.FindChildren(name))
                .FirstOrDefault();

            return result;
        }
        private PdbSession FindSessionByNothing()
        {
            PdbSession result = pdbSessions
                .FirstOrDefault();

            return result;
        }
        private Type GetTypeFromSymbol(PdbSymbol type)
        {
            PdbSymbolTag tag = type.SymTag;

            if (tag == PdbSymbolTag.PointerType)
                return typeof(IntPtr);
            else if (tag == PdbSymbolTag.BaseType || tag == PdbSymbolTag.Enum)
            {
                ulong size = type.Length;
                PdbSymbolBaseType baseType = type.BaseType;

                switch (baseType)
                {
                    case PdbSymbolBaseType.Char: return typeof(char);
                    case PdbSymbolBaseType.WChar: return typeof(char);
                    case PdbSymbolBaseType.Int: return size == 2 ? typeof(short) : size == 4 ? typeof(int) : size == 8 ? typeof(long) : null;
                    case PdbSymbolBaseType.UInt: return size == 2 ? typeof(ushort) : size == 4 ? typeof(uint) : size == 8 ? typeof(ulong) : null;
                    case PdbSymbolBaseType.Float: return typeof(float);
                    case PdbSymbolBaseType.Bool: return typeof(bool);
                    case PdbSymbolBaseType.Long: return typeof(long);
                    case PdbSymbolBaseType.ULong: return typeof(ulong);
                }

                return null;
            }
            //else if (tag == PdbSymbolTag.Enum)
            //    return typeof(Enum);
            else if (tag == PdbSymbolTag.ArrayType)
            {

            }
            else if (tag == PdbSymbolTag.FunctionType)
            {

            }
            else if (tag == PdbSymbolTag.CustomType)
            {

            }

            return null;
        }
        private string GetTypeNameFromSymbol(PdbSymbol type)
        {
            if (type == null)
                return "";

            PdbSymbolTag tag = type.SymTag;

            string name = type.Name;
            if (name != null)
                return name;

            if (tag == PdbSymbolTag.PointerType)
                return GetTypeNameFromSymbol(type.Type) + "*";
            else if (tag == PdbSymbolTag.BaseType)
            {
                ulong size = type.Length;
                PdbSymbolBaseType baseType = type.BaseType;

                switch (baseType)
                {
                    case PdbSymbolBaseType.Char: return "char";
                    case PdbSymbolBaseType.WChar: return "char";
                    case PdbSymbolBaseType.Int: return size == 2 ? "s16" : size == 4 ? "s32" : size == 8 ? "s64" : "";
                    case PdbSymbolBaseType.UInt: return size == 2 ? "u16" : size == 4 ? "u32" : size == 8 ? "u64" : "";
                    case PdbSymbolBaseType.Float: return "float";
                    case PdbSymbolBaseType.Bool: return "bool";
                    case PdbSymbolBaseType.Long: return "s64";
                    case PdbSymbolBaseType.ULong: return "u64";
                }

                return "";
            }
            else if (tag == PdbSymbolTag.ArrayType)
            {

            }
            else if (tag == PdbSymbolTag.FunctionType)
            {

            }
            else if (tag == PdbSymbolTag.CustomType)
            {

            }

            return "";
        }



        #region Virtual machine

        private void VirtualMachine_Stopped(object sender, EventArgs e)
        {
            Protocol.SendEvent(new ExitedEvent(exitCode: 0));
            Protocol.SendEvent(new TerminatedEvent());
        }

        #endregion

        #region Serial

        private void SerialStream_WaitForConnection(IAsyncResult asyncResult)
        {
            try
            {
                serialStream.EndWaitForConnection(asyncResult);
                serialStream.BeginRead(serialBuffer, 0, 1, SerialStream_Read, null);
            }
            catch { }
        }
        private void SerialStream_Read(IAsyncResult asyncResult)
        {
            int count = serialStream.EndRead(asyncResult);
            if (count != 1)
            {
                try
                {
                    serialStream.Close();
                    gdbClient.Dispose();
                }
                catch { }

                InitializeSerial();

                return;
            }

            SerialStream_ReadByte(serialBuffer[0]);

            serialStream.BeginRead(serialBuffer, 0, 1, SerialStream_Read, null);
        }
        private void SerialStream_ReadByte(byte value)
        {
            // Carriage return
            if (value == '\r')
                return;

            // Full line
            if (value == '\n')
            {
                Protocol.SendEvent(new OutputEvent() { Output = serialLine + Environment.NewLine, Category = OutputEvent.CategoryValue.Stdout });
                
                serialLine = "";
                return;
            }

            // Simple character
            serialLine += new string((char)value, 1).Replace("{", "{{").Replace("}", "}}");
        }

        #endregion

        #region Gdb

        private void Gdb_BreakpointHit(GdbClient gdbStub, GdbBreakpointHitData breakpointHitData)
        {
            ulong address = breakpointHitData.Address;

            // Debugger::Break() function
            if (address == debuggerBreakFunction.VirtualAddress)
            {
                gdbClient.Registers.Eip++;
                gdbClient.Step();
            }

            int taskId = (int)currentTask.Object.Id;
            Protocol.SendEvent(new StoppedEvent() { Reason = StoppedEvent.ReasonValue.Breakpoint, ThreadId = taskId, AllThreadsStopped = true });
        }

        #endregion



        #region Initialize/Disconnect

        protected override InitializeResponse HandleInitializeRequest(InitializeArguments arguments)
        {
            Protocol.SendEvent(new InitializedEvent());

            InitializeResponse response = new InitializeResponse();

            response.SupportsConfigurationDoneRequest = true;
            response.SupportsDisassembleRequest = true;
            response.SupportsEvaluateForHovers = true;
            response.SupportsReadMemoryRequest = true;
            response.SupportsTerminateRequest = true;
            //response.SupportsModulesRequest = true;

            return response;
        }
        protected override DisconnectResponse HandleDisconnectRequest(DisconnectArguments arguments)
        {
            try
            {
                if (!gdbClient.Running)
                    gdbClient.Continue();
            }
            catch { }

            try
            {
                if (virtualMachine.Running)
                    virtualMachine.Stop();
            }
            catch { }

            return new DisconnectResponse();
        }
        protected override TerminateResponse HandleTerminateRequest(TerminateArguments arguments)
        {
            try
            {
                if (!gdbClient.Running)
                    gdbClient.Continue();
            }
            catch { }

            try
            {
                if (virtualMachine.Running)
                    virtualMachine.Stop();
            }
            catch { }

            return new TerminateResponse();
        }

        #endregion

        #region Launch/Attach

        protected override LaunchResponse HandleLaunchRequest(LaunchArguments arguments)
        {
            JObject optionsObject = arguments.ConfigurationProperties.GetValueAsObject("options");
            LoadOptions(optionsObject);

            InitializeVirtualMachine();

            InitializeSerial();
            InitializeSymbols();
            InitializeGdb();
            InitializeWrappers();

            return new LaunchResponse();
        }
        protected override AttachResponse HandleAttachRequest(AttachArguments arguments)
        {
            JObject optionsObject = arguments.ConfigurationProperties.GetValueAsObject("options");
            LoadOptions(optionsObject);

            InitializeSerial();
            InitializeSymbols();
            InitializeGdb();
            InitializeWrappers();

            return new AttachResponse();
        }

        #endregion

        #region Continue/Stepping

        protected override ConfigurationDoneResponse HandleConfigurationDoneRequest(ConfigurationDoneArguments arguments)
        {
            gdbClient.Continue();

            PdbSession session = FindSessionByNothing();

            Protocol.SendEvent(new ProcessEvent()
            {
                Name = "Kernel",
                SystemProcessId = 1,
                IsLocalProcess = true,
                StartMethod = ProcessEvent.StartMethodValue.Launch,
                PointerSize = 4
            });

            Protocol.SendEvent(new ModuleEvent(ModuleEvent.ReasonValue.New, new Module()
            {
                Id = 1,
                Name = "Kernel",
                Path = "Kernel",
                SymbolFilePath = Path.Combine(Bootstrap.Source, @"Kernel\Kernel.pdb"),
                SymbolStatus = "Loaded",
                VsLoadAddress = session.LoadAddress.ToString(),
                VsPreferredLoadAddress = session.LoadAddress.ToString(),
                VsLoadOrder = 0
            }));

            return new ConfigurationDoneResponse();
        }
        protected override ContinueResponse HandleContinueRequest(ContinueArguments arguments)
        {
            gdbClient.Continue();

            return new ContinueResponse();
        }
        protected override StepInResponse HandleStepInRequest(StepInArguments arguments)
        {
            PdbSession session = FindSessionByNothing();

            while (true)
            {
                PdbLineNumber lineNumber = SourceStep();

                uint eip = gdbClient.Registers.Eip;
                PdbSymbol function = session?.GetSymbolAtVirtualAddress(PdbSymbolTag.Function, eip);
                if (function == null)
                    continue;

                break;
            }

            int taskId = (int)currentTask.Object.Id;
            Protocol.SendEvent(new StoppedEvent() { Reason = StoppedEvent.ReasonValue.Breakpoint, ThreadId = taskId, AllThreadsStopped = true });
            
            return new StepInResponse();
        }
        protected override StepOutResponse HandleStepOutRequest(StepOutArguments arguments)
        {
            SourceStep();

            int taskId = (int)currentTask.Object.Id;
            Protocol.SendEvent(new StoppedEvent() { Reason = StoppedEvent.ReasonValue.Breakpoint, ThreadId = taskId, AllThreadsStopped = true });

            return new StepOutResponse();
        }
        protected override NextResponse HandleNextRequest(NextArguments arguments)
        {
            PdbSession session = FindSessionByNothing();

            uint ebp = gdbClient.Registers.Ebp;
            uint eip = gdbClient.Registers.Eip;

            PdbLineNumber originalLineNumber = session?.FindLinesByVirtualAddress(eip, 1).FirstOrDefault();
            PdbSymbol originalFunction = session?.GetSymbolAtVirtualAddress(PdbSymbolTag.Function, eip);

            while (true)
            {
                PdbLineNumber lineNumber = SourceStep();

                eip = gdbClient.Registers.Eip;
                PdbSymbol function = session?.GetSymbolAtVirtualAddress(PdbSymbolTag.Function, eip);
                if (function == null)
                    continue;

                if (originalFunction == null || originalLineNumber == null)
                    break;

                if (function.VirtualAddress != originalFunction.VirtualAddress)
                {
                    if (gdbClient.Registers.Ebp <= ebp)
                        continue;
                }
                else if (lineNumber.LineNumber == originalLineNumber.LineNumber && lineNumber.ColumnNumber == originalLineNumber.ColumnNumber)
                    continue;

                break;
            }

            int taskId = (int)currentTask.Object.Id;
            Protocol.SendEvent(new StoppedEvent() { Reason = StoppedEvent.ReasonValue.Breakpoint, ThreadId = taskId, AllThreadsStopped = true });

            return new NextResponse();
        }
        protected override PauseResponse HandlePauseRequest(PauseArguments arguments)
        {
            gdbClient.Break();

            int taskId = (int)currentTask.Object.Id;
            Protocol.SendEvent(new StoppedEvent() { Reason = StoppedEvent.ReasonValue.Breakpoint, ThreadId = taskId, AllThreadsStopped = true });

            return new PauseResponse();
        }

        private PdbLineNumber SourceStep()
        {
            PdbSession session = FindSessionByNothing();

            uint eip = gdbClient.Registers.Eip;

            PdbLineNumber originalLineNumber = session?.FindLinesByVirtualAddress(eip, 1).FirstOrDefault();

            while (true)
            {
                gdbClient.Step();
                eip = gdbClient.Registers.Eip;

                PdbLineNumber lineNumber = session?.FindLinesByVirtualAddress(eip, 1).FirstOrDefault();
                if (lineNumber == null)
                    continue;
                if (lineNumber.LineNumber == 0xf00f00)
                    continue;

                if (originalLineNumber == null)
                    return lineNumber;

                if (lineNumber.CompilandId != originalLineNumber.CompilandId)
                    return lineNumber;
                if (lineNumber.LineNumber != originalLineNumber.LineNumber)
                    return lineNumber;
                if (lineNumber.ColumnNumber != originalLineNumber.ColumnNumber)
                    return lineNumber;
            }
        }

        #endregion

        #region Breakpoints

        protected override SetBreakpointsResponse HandleSetBreakpointsRequest(SetBreakpointsArguments arguments)
        {
            string sourcePath = arguments.Source.Path;
            List<Breakpoint> breakpoints = new List<Breakpoint>();

            bool wasRunning = gdbClient.Running;
            if (wasRunning)
                gdbClient.Break();

            List<GdbBreakpoint> sourceBreakpoints = gdbBreakpoints.GetOrAdd(sourcePath, _ => new List<GdbBreakpoint>());

            foreach (GdbBreakpoint sourceBreakpoint in sourceBreakpoints)
                gdbClient.Breakpoints.Remove(sourceBreakpoint);
            sourceBreakpoints.Clear();

            foreach (SourceBreakpoint sourceBreakpoint in arguments.Breakpoints)
            {
                PdbLineNumber[] pdbLineNumbers = pdbSessions
                    .SelectMany(s =>
                    {
                        PdbSourceFile pdbSourceFile = s.SourceFiles.FirstOrDefault(f => string.Equals(f.FileName, sourcePath, StringComparison.InvariantCultureIgnoreCase));
                        if (pdbSourceFile == null)
                            return Enumerable.Empty<PdbLineNumber>();

                        return pdbSourceFile.Compilands
                            .SelectMany(c => s.FindLinesByLineColumn(c, pdbSourceFile, (uint)sourceBreakpoint.Line, (uint)sourceBreakpoint.Column));
                    })
                    .ToArray();

                foreach (PdbLineNumber pdbLineNumber in pdbLineNumbers)
                {
                    GdbBreakpoint gdbBreakpoint = gdbClient.Breakpoints.Add(GdbBreakpointType.Memory, pdbLineNumber.VirtualAddress);
                    sourceBreakpoints.Add(gdbBreakpoint);
                }

                Breakpoint breakpoint = new Breakpoint()
                {
                    Verified = pdbLineNumbers.Length > 0,
                    Source = new Source()
                    {
                        Name = Path.GetFileName(sourcePath),
                        Path = sourcePath
                    },
                    Line = (int?)pdbLineNumbers.FirstOrDefault()?.LineNumber,
                    Column = (int?)pdbLineNumbers.FirstOrDefault()?.ColumnNumber
                };

                breakpoints.Add(breakpoint);
            }

            if (wasRunning)
                gdbClient.Continue();

            return new SetBreakpointsResponse(breakpoints);
        }

        #endregion

        #region Debugger Properties

        protected override SetDebuggerPropertyResponse HandleSetDebuggerPropertyRequest(SetDebuggerPropertyArguments arguments)
        {
            //IsJustMyCodeOn = GetValueAsVariantBool(arguments.DebuggerProperties, "JustMyCodeStepping") ?? IsJustMyCodeOn;
            //IsStepFilteringOn = GetValueAsVariantBool(arguments.DebuggerProperties, "EnableStepFiltering") ?? IsStepFilteringOn;

            return new SetDebuggerPropertyResponse();
        }

        #endregion

        #region Inspection

        protected override ThreadsResponse HandleThreadsRequest(ThreadsArguments arguments)
        {
            if (gdbClient.Running)
                throw new ProtocolException("Not in break mode!");

            // Get tasks
            List<Task> tasks = new List<Task>();

            Task task = firstTask.Object;
            while (task != null)
            {
                tasks.Add(task);
                task = task.Next;
            }

            // Convert to threads
            List<Thread> threads = tasks
                .Select(t => new Thread() { Id = (int)t.Id, Name = t.Id == 0 ? "Kernel" : $"Task #{t.Id}" })
                .ToList();

            return new ThreadsResponse(threads: threads);
        }
        protected override ScopesResponse HandleScopesRequest(ScopesArguments arguments)
        {
            PdbSession session = FindSessionByNothing();

            List<Scope> scopes = new List<Scope>()
            {
                new Scope()
                {
                    Name = "Registers",
                    VariablesReference = -1,
                    Expensive = false,
                    PresentationHint = Scope.PresentationHintValue.Registers
                }
            };

            if (!internalFrames.TryGetValue(arguments.FrameId, out InternalFrame internalFrame))
                return new ScopesResponse(scopes);

            scopes.Add(new Scope()
            {
                Name = "Locals",
                VariablesReference = arguments.FrameId,
                Expensive = false,
                PresentationHint = Scope.PresentationHintValue.Locals
            });

            return new ScopesResponse(scopes);
        }
        protected override ModulesResponse HandleModulesRequest(ModulesArguments arguments)
        {
            if (arguments.StartModule == 0 && arguments.ModuleCount == 1)
            {
                PdbSession session = FindSessionByNothing();

                return new ModulesResponse()
                {
                    Modules = new List<Module>()
                    {
                        new Module()
                        {
                            Id = 1,
                            Name = "Kernel",
                            Path = "Kernel",
                            SymbolFilePath = Path.Combine(Bootstrap.Source, @"Kernel\Kernel.pdb"),
                            SymbolStatus = "Loaded",
                            VsLoadAddress = session.LoadAddress.ToString(),
                            VsPreferredLoadAddress = session.LoadAddress.ToString(),
                            VsLoadOrder = 0
                        }
                    },
                    TotalModules = 1
                };
            }

            return new ModulesResponse()
            {
                Modules = new List<Module>(),
                TotalModules = 1
            };
        }
        protected override StackTraceResponse HandleStackTraceRequest(StackTraceArguments arguments)
        {
            if (gdbClient.Running)
                throw new ProtocolException("Not in break mode!");

            // Get task
            Task currentTask = this.currentTask.Object;
            Task task = null;

            if (arguments.ThreadId == currentTask.Id)
            {
                task = currentTask;
            }
            else if (arguments.ThreadId > 0)
            {
                task = firstTask.Object;
                while (task != null && task.Id != arguments.ThreadId)
                    task = task.Next;
            }
            else
                task = kernelTask.Object;

            if (task == null)
                return new StackTraceResponse();

            // Get stack trace
            List<StackFrame> stackFrames = new List<StackFrame>();

            uint eip = task == currentTask ? gdbClient.Registers.Eip : task.Eip;
            uint ebp = task == currentTask ? gdbClient.Registers.Ebp : task.Ebp;
            //uint esp = task == currentTask ? gdbClient.Registers.Esp : task.Esp;

            // Add current method
            {
                PdbSession session = FindSessionByNothing();

                PdbSymbol function = session?.GetSymbolAtVirtualAddress(PdbSymbolTag.Function, eip);
                PdbLineNumber lineNumber = session?.FindLinesByVirtualAddress(eip, 1).FirstOrDefault();

                InternalFrame internalFrame = new InternalFrame()
                {
                    Symbol = function,
                    Ebp = ebp
                };

                int internalFrameId = Interlocked.Increment(ref nextInternalFrameId);
                internalFrames[internalFrameId] = internalFrame;

                StackFrame frame = new StackFrame()
                {
                    Id = internalFrameId,
                    Name = function?.UndecoratedName ?? "Unknown",
                    Line = (int?)lineNumber?.LineNumber ?? 0,
                    Column = (int?)lineNumber?.ColumnNumber ?? 0,
                    Source = lineNumber == null ? null : new Source()
                    {
                        Name = Path.GetFileName(lineNumber.SourceFile.FileName),
                        Path = lineNumber.SourceFile.FileName
                    },
                    ModuleId = 1,
                    InstructionPointerReference = eip.ToString()
                };

                stackFrames.Add(frame);
            }

            uint stackPointer = ebp;

            /*// Search first frame
            while (stackPointer < esp + 0x100)
            {
                // We found a stack pointer
                uint stackValue = gdbClient.Memory.ReadUInt32(stackPointer);
                if ((stackValue & 0xFFFF0000) == (stackPointer & 0xFFFF0000))
                {
                    // And this stack pointer leads to another one
                    uint stackValueValue = gdbClient.Memory.ReadUInt32(stackValue);
                    if ((stackValueValue & 0xFFFF0000) == (stackPointer & 0xFFFF0000))
                    {
                        // Then stop, this should be the one :)
                        break;
                    }
                }

                stackPointer += 4;
            }/**/

            // Decode frames
            while (true)
            {
                ebp = gdbClient.Memory.ReadUInt32(stackPointer);
                uint ret = gdbClient.Memory.ReadUInt32(stackPointer + 4);

                PdbSession session = FindSessionByNothing();

                if (ret == 0 || ret == 2 || ret < session.LoadAddress)
                    break;

                PdbSymbol function = session?.GetSymbolAtVirtualAddress(PdbSymbolTag.Function, ret);
                PdbLineNumber lineNumber = session?.FindLinesByVirtualAddress(ret, 1).FirstOrDefault();

                InternalFrame internalFrame = new InternalFrame()
                {
                    Symbol = function,
                    Ebp = ebp
                };

                int internalFrameId = Interlocked.Increment(ref nextInternalFrameId);
                internalFrames[internalFrameId] = internalFrame;

                StackFrame frame = new StackFrame()
                {
                    Id = internalFrameId,
                    Name = function?.UndecoratedName ?? "Unknown",
                    Line = (int?)lineNumber?.LineNumber ?? 0,
                    Column = (int?)lineNumber?.ColumnNumber ?? 0,
                    Source = lineNumber == null ? null : new Source()
                    {
                        Name = Path.GetFileName(lineNumber.SourceFile.FileName),
                        Path = lineNumber.SourceFile.FileName
                    },
                    ModuleId = 1,
                    InstructionPointerReference = ret.ToString()
                };

                stackFrames.Add(frame);

                stackPointer = ebp;
            }

            // Filter down as requested
            int totalCount = stackFrames.Count;

            stackFrames = stackFrames
                .Skip(arguments.StartFrame ?? 0)
                .Take(((arguments.Levels ?? 0) == 0) ? int.MaxValue : arguments.Levels.Value)
                .ToList();

            return new StackTraceResponse() { StackFrames = stackFrames, TotalFrames = totalCount };
        }
        protected override VariablesResponse HandleVariablesRequest(VariablesArguments arguments)
        {
            if (arguments.VariablesReference == -1)
            {
                //Task task = currentTask.Object;

                return new VariablesResponse(new List<Variable>()
                {
                    //new Variable("eip", $"0x{task.Eip:x8}", 0),
                    //new Variable("esp", $"0x{task.Esp:x8}", 0),
                    //new Variable("ebp", $"0x{task.Ebp:x8}", 0),

                    new Variable() { Name = "eax", Value = $"0x{gdbClient.Registers.Eax:x8}", Type = "register", MemoryReference = gdbClient.Registers.Eax.ToString() },
                    new Variable() { Name = "ecx", Value = $"0x{gdbClient.Registers.Ecx:x8}", Type = "register", MemoryReference = gdbClient.Registers.Ecx.ToString() },
                    new Variable() { Name = "edx", Value = $"0x{gdbClient.Registers.Edx:x8}", Type = "register", MemoryReference = gdbClient.Registers.Edx.ToString() },
                    new Variable() { Name = "ebx", Value = $"0x{gdbClient.Registers.Ebx:x8}", Type = "register", MemoryReference = gdbClient.Registers.Ebx.ToString() },
                    new Variable() { Name = "esp", Value = $"0x{gdbClient.Registers.Esp:x8}", Type = "register", MemoryReference = gdbClient.Registers.Esp.ToString() },
                    new Variable() { Name = "ebp", Value = $"0x{gdbClient.Registers.Ebp:x8}", Type = "register", MemoryReference = gdbClient.Registers.Ebp.ToString() },
                    new Variable() { Name = "esi", Value = $"0x{gdbClient.Registers.Esi:x8}", Type = "register", MemoryReference = gdbClient.Registers.Esi.ToString() },
                    new Variable() { Name = "edi", Value = $"0x{gdbClient.Registers.Edi:x8}", Type = "register", MemoryReference = gdbClient.Registers.Edi.ToString() },
                    new Variable() { Name = "eip", Value = $"0x{gdbClient.Registers.Eip:x8}", Type = "register", MemoryReference = gdbClient.Registers.Eip.ToString() },
                    new Variable() { Name = "eflags", Value = $"0x{gdbClient.Registers.Eflags:x8}", Type = "register", MemoryReference = gdbClient.Registers.Eflags.ToString() },
                    new Variable() { Name = "cs", Value = $"0x{gdbClient.Registers.Cs:x8}", Type = "register", MemoryReference = gdbClient.Registers.Cs.ToString() },
                    new Variable() { Name = "ss", Value = $"0x{gdbClient.Registers.Ss:x8}", Type = "register", MemoryReference = gdbClient.Registers.Ss.ToString() },
                    new Variable() { Name = "ds", Value = $"0x{gdbClient.Registers.Ds:x8}", Type = "register", MemoryReference = gdbClient.Registers.Ds.ToString() },
                    new Variable() { Name = "es", Value = $"0x{gdbClient.Registers.Es:x8}", Type = "register", MemoryReference = gdbClient.Registers.Es.ToString() },
                    new Variable() { Name = "fs", Value = $"0x{gdbClient.Registers.Fs:x8}", Type = "register", MemoryReference = gdbClient.Registers.Fs.ToString() },
                    new Variable() { Name = "gs", Value = $"0x{gdbClient.Registers.Gs:x8}", Type = "register", MemoryReference = gdbClient.Registers.Gs.ToString() }
                });
            }

            if (!internalFrames.TryGetValue(arguments.VariablesReference, out InternalFrame internalFrame))
                return new VariablesResponse();

            List<Variable> variables = new List<Variable>();

            if (internalFrame.Symbol != null)
            {
                foreach (PdbSymbol variable in internalFrame.Symbol.FindChildren(PdbSymbolTag.Data))
                {
                    PdbSymbol variableType = variable.Type;
                    if (variableType == null)
                        continue;

                    int offset = variable.Offset;
                    ulong size = variableType.Length;

                    byte[] buffer = new byte[size];
                    gdbClient.Memory.Read((ulong)(internalFrame.Ebp + offset), buffer, 0, (int)size);

                    Type type = GetTypeFromSymbol(variableType);
                    string typeName = GetTypeNameFromSymbol(variableType);
                    string value = "";

                    if (type == null)
                        value = "";
                    else if (type == typeof(string))
                        value = "{ String }";
                    else if (type == typeof(bool))
                        value = buffer[0] != 0 ? "true" : "false";
                    else if (type == typeof(sbyte))
                        value = ((sbyte)buffer[0]).ToString();
                    else if (type == typeof(byte))
                        value = buffer[0].ToString();
                    else if (type == typeof(short))
                        value = BitConverter.ToInt16(buffer, 0).ToString();
                    else if (type == typeof(ushort))
                        value = BitConverter.ToUInt16(buffer, 0).ToString();
                    else if (type == typeof(int))
                        value = BitConverter.ToInt32(buffer, 0).ToString();
                    else if (type == typeof(uint))
                        value = BitConverter.ToUInt32(buffer, 0).ToString();
                    else if (type == typeof(long))
                        value = BitConverter.ToInt64(buffer, 0).ToString();
                    else if (type == typeof(ulong))
                        value = BitConverter.ToUInt64(buffer, 0).ToString();
                    else if (typeName == "char*")
                        value = "\"" + ReadCString(BitConverter.ToUInt32(buffer, 0)) + "\"";
                    else if (typeName == "String*")
                        value = "\"" + ReadString(BitConverter.ToUInt32(buffer, 0)) + "\"";
                    else if (type == typeof(IntPtr))
                        value = "0x" + BitConverter.ToUInt32(buffer, 0).ToString("x8");
                    //else if (type == typeof(Enum))
                    //    value = 

                    variables.Add(new Variable()
                    {
                        Name = variable.Name,
                        Value = value,
                        Type = typeName
                    });
                }
            }

            return new VariablesResponse(variables: variables);
        }
        protected override SetVariableResponse HandleSetVariableRequest(SetVariableArguments arguments)
        {
            return base.HandleSetVariableRequest(arguments);
        }
        protected override EvaluateResponse HandleEvaluateRequest(EvaluateArguments arguments)
        {
            if (uint.TryParse(arguments.Expression, out uint address))
            {
                return new EvaluateResponse() { Result = arguments.Expression, MemoryReference = address.ToString() };
            }

            if (arguments.Expression.StartsWith("0x"))
            {
                try
                {
                    address = Convert.ToUInt32(arguments.Expression, 16);
                    return new EvaluateResponse() { Result = arguments.Expression, MemoryReference = address.ToString() };
                }
                catch { }
            }

            switch (arguments.Expression)
            {
                case "eax": return new EvaluateResponse() { Result = $"0x{gdbClient.Registers.Eax:x8}", MemoryReference = gdbClient.Registers.Eax.ToString() };
                case "ecx": return new EvaluateResponse() { Result = $"0x{gdbClient.Registers.Ecx:x8}", MemoryReference = gdbClient.Registers.Ecx.ToString() };
                case "edx": return new EvaluateResponse() { Result = $"0x{gdbClient.Registers.Edx:x8}", MemoryReference = gdbClient.Registers.Edx.ToString() };
                case "ebx": return new EvaluateResponse() { Result = $"0x{gdbClient.Registers.Ebx:x8}", MemoryReference = gdbClient.Registers.Ebx.ToString() };
                case "esp": return new EvaluateResponse() { Result = $"0x{gdbClient.Registers.Esp:x8}", MemoryReference = gdbClient.Registers.Esp.ToString() };
                case "ebp": return new EvaluateResponse() { Result = $"0x{gdbClient.Registers.Ebp:x8}", MemoryReference = gdbClient.Registers.Ebp.ToString() };
                case "esi": return new EvaluateResponse() { Result = $"0x{gdbClient.Registers.Esi:x8}", MemoryReference = gdbClient.Registers.Esi.ToString() };
                case "edi": return new EvaluateResponse() { Result = $"0x{gdbClient.Registers.Edi:x8}", MemoryReference = gdbClient.Registers.Edi.ToString() };
                case "eip": return new EvaluateResponse() { Result = $"0x{gdbClient.Registers.Eip:x8}", MemoryReference = gdbClient.Registers.Eip.ToString() };
                case "eflags": return new EvaluateResponse() { Result = $"0x{gdbClient.Registers.Eflags:x8}", MemoryReference = gdbClient.Registers.Eflags.ToString() };
                case "cs": return new EvaluateResponse() { Result = $"0x{gdbClient.Registers.Cs:x8}", MemoryReference = gdbClient.Registers.Cs.ToString() };
                case "ss": return new EvaluateResponse() { Result = $"0x{gdbClient.Registers.Ss:x8}", MemoryReference = gdbClient.Registers.Ss.ToString() };
                case "ds": return new EvaluateResponse() { Result = $"0x{gdbClient.Registers.Ds:x8}", MemoryReference = gdbClient.Registers.Ds.ToString() };
                case "es": return new EvaluateResponse() { Result = $"0x{gdbClient.Registers.Es:x8}", MemoryReference = gdbClient.Registers.Es.ToString() };
                case "fs": return new EvaluateResponse() { Result = $"0x{gdbClient.Registers.Fs:x8}", MemoryReference = gdbClient.Registers.Fs.ToString() };
                case "gs": return new EvaluateResponse() { Result = $"0x{gdbClient.Registers.Gs:x8}", MemoryReference = gdbClient.Registers.Gs.ToString() };
            }

            return new EvaluateResponse();
        }
        protected override SetExpressionResponse HandleSetExpressionRequest(SetExpressionArguments arguments)
        {
            return base.HandleSetExpressionRequest(arguments);
        }

        internal string ReadCString(uint address)
        {
            byte[] buffer = new byte[1024];
            uint i = 0;

            while (i < 1024)
            {
                buffer[i] = gdbClient.Memory.ReadUInt8(address + i);
                if (buffer[i] == 0)
                    break;

                i++;
            }

            return Encoding.ASCII.GetString(buffer, 0, (int)i);
        }
        internal string ReadString(uint address)
        {
            byte[] stringBuffer = new byte[8];
            gdbClient.Memory.Read(address, stringBuffer, 0, 8);

            int length = BitConverter.ToUInt16(stringBuffer, 4);
            uint pointer = BitConverter.ToUInt32(stringBuffer, 0);

            byte[] buffer = new byte[length];
            gdbClient.Memory.Read(pointer, buffer, 0, length);

            return Encoding.ASCII.GetString(buffer, 0, length);
        }

        #endregion
        
        #region Source/Disassemble

        protected override DisassembleResponse HandleDisassembleRequest(DisassembleArguments arguments)
        {
            return base.HandleDisassembleRequest(arguments);
        }
        protected override ReadMemoryResponse HandleReadMemoryRequest(ReadMemoryArguments arguments)
        {
            if (!uint.TryParse(arguments.MemoryReference, out uint address))
                return new ReadMemoryResponse();

            byte[] buffer = new byte[arguments.Count];

            if (arguments.Count > 0)
            {
                gdbClient.Memory.Read((ulong)(address + (arguments.Offset ?? 0)), buffer, 0, arguments.Count);
            }

            return new ReadMemoryResponse()
            {
                Address = (address + (arguments.Offset ?? 0)).ToString(),
                Data = Convert.ToBase64String(buffer)
            };
        }

        #endregion

        #region Exceptions

        protected override ExceptionInfoResponse HandleExceptionInfoRequest(ExceptionInfoArguments arguments)
        {
            /*return new ExceptionInfoResponse()
            {
                Description = "Sample Exception"
            };*/
            return base.HandleExceptionInfoRequest(arguments);
        }
        protected override SetExceptionBreakpointsResponse HandleSetExceptionBreakpointsRequest(SetExceptionBreakpointsArguments arguments)
        {
            return new SetExceptionBreakpointsResponse();
            //return base.HandleSetExceptionBreakpointsRequest(arguments);
        }

        #endregion
    }
}

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
        private PdbSymbol exceptionAssertFunction;
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

            gdbClient.Continue();
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
                Protocol.SendEvent(new OutputEvent(output: serialLine + Environment.NewLine, category: OutputEvent.CategoryValue.Stdout));
                
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
            Protocol.SendEvent(new StoppedEvent(reason: StoppedEvent.ReasonValue.Breakpoint, threadId: taskId, allThreadsStopped: true));
        }

        #endregion



        // Protocol.SendEvent(new StoppedEvent(reason: stopReason.Value, threadId: stopThreadId));
        // Protocol.SendEvent(new ExitedEvent(exitCode: 0));
        // Protocol.SendEvent(new TerminatedEvent());
        // Protocol.SendEvent(new OutputEvent(output: Invariant($"{outputText}{Environment.NewLine}"), category: OutputEvent.CategoryValue.Stdout));

        #region Initialize/Disconnect

        protected override InitializeResponse HandleInitializeRequest(InitializeArguments arguments)
        {
            Protocol.SendEvent(new InitializedEvent());

            InitializeResponse response = new InitializeResponse();

            //response.SupportsConfigurationDoneRequest = true;
            //response.SupportsDebuggerProperties = true;

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
            Protocol.SendEvent(new StoppedEvent(reason: StoppedEvent.ReasonValue.Breakpoint, threadId: taskId, allThreadsStopped: true));

            return new StepInResponse();
        }
        protected override StepOutResponse HandleStepOutRequest(StepOutArguments arguments)
        {
            SourceStep();

            int taskId = (int)currentTask.Object.Id;
            Protocol.SendEvent(new StoppedEvent(reason: StoppedEvent.ReasonValue.Breakpoint, threadId: taskId, allThreadsStopped: true));

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
            Protocol.SendEvent(new StoppedEvent(reason: StoppedEvent.ReasonValue.Breakpoint, threadId: taskId, allThreadsStopped: true));

            return new NextResponse();
        }
        protected override PauseResponse HandlePauseRequest(PauseArguments arguments)
        {
            gdbClient.Break();

            int taskId = (int)currentTask.Object.Id;
            Protocol.SendEvent(new StoppedEvent(reason: StoppedEvent.ReasonValue.Breakpoint, threadId: taskId, allThreadsStopped: true));

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

            if (gdbClient.Running)
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

                Breakpoint breakpoint = new Breakpoint
                (
                    verified: pdbLineNumbers.Length > 0,
                    source: new Source
                    (
                        name: Path.GetFileName(sourcePath),
                        path: sourcePath
                    ),
                    line: (int?)pdbLineNumbers.FirstOrDefault()?.LineNumber,
                    column: (int?)pdbLineNumbers.FirstOrDefault()?.ColumnNumber
                );

                breakpoints.Add(breakpoint);
            }

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
                .Select(t => new Thread(id: (int)t.Id, name: t.Id == 0 ? "Kernel" : $"Task #{t.Id}"))
                .ToList();

            return new ThreadsResponse(threads: threads);
        }
        protected override ScopesResponse HandleScopesRequest(ScopesArguments arguments)
        {
            PdbSession session = FindSessionByNothing();

            if (!internalFrames.TryGetValue(arguments.FrameId, out InternalFrame internalFrame))
                return new ScopesResponse();

            List<Scope> scopes = new List<Scope>()
            {
                /*new Scope
                (
                    name: "Registers",
                    variablesReference: -1,
                    expensive: false
                ),*/
                new Scope
                (
                    name: "Variables",
                    variablesReference: arguments.FrameId,
                    expensive: false
                )
            };

            return new ScopesResponse(scopes);
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

                if (function == null || lineNumber == null)
                    return new StackTraceResponse();

                InternalFrame internalFrame = new InternalFrame()
                {
                    Symbol = function,
                    Ebp = ebp
                };

                int internalFrameId = Interlocked.Increment(ref nextInternalFrameId);
                internalFrames[internalFrameId] = internalFrame;

                StackFrame frame = new StackFrame
                (
                    id: internalFrameId,
                    name: function.UndecoratedName,
                    line: (int)lineNumber.LineNumber,
                    column: (int)lineNumber.ColumnNumber,
                    source: new Source
                    (
                        name: Path.GetFileName(lineNumber.SourceFile.FileName),
                        path: lineNumber.SourceFile.FileName
                    )
                );

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

                if (ret == 0)
                    break;

                PdbSession session = FindSessionByNothing();

                PdbSymbol function = session?.GetSymbolAtVirtualAddress(PdbSymbolTag.Function, ret);
                PdbLineNumber lineNumber = session?.FindLinesByVirtualAddress(ret, 1).FirstOrDefault();

                if (function == null || lineNumber == null)
                    break;

                InternalFrame internalFrame = new InternalFrame()
                {
                    Symbol = function,
                    Ebp = ebp
                };

                int internalFrameId = Interlocked.Increment(ref nextInternalFrameId);
                internalFrames[internalFrameId] = internalFrame;

                StackFrame frame = new StackFrame
                (
                    id: internalFrameId,
                    name: function.UndecoratedName,
                    line: (int)lineNumber.LineNumber,
                    column: (int)lineNumber.ColumnNumber,
                    source: new Source
                    (
                        name: Path.GetFileName(lineNumber.SourceFile.FileName),
                        path: lineNumber.SourceFile.FileName
                    )
                );

                stackFrames.Add(frame);

                stackPointer = ebp;
            }

            // Filter down as requested
            int totalCount = stackFrames.Count;

            stackFrames = stackFrames
                .Skip(arguments.StartFrame ?? 0)
                .Take(((arguments.Levels ?? 0) == 0) ? int.MaxValue : arguments.Levels.Value)
                .ToList();

            return new StackTraceResponse(stackFrames: stackFrames, totalFrames: totalCount);
        }
        protected override VariablesResponse HandleVariablesRequest(VariablesArguments arguments)
        {
            if (arguments.VariablesReference == -1)
            {
                return new VariablesResponse(new List<Variable>()
                {
                    new Variable("registers", "", -2),
                });
            }
            else if (arguments.VariablesReference == -2)
            {
                //Task task = currentTask.Object;

                return new VariablesResponse(new List<Variable>()
                {
                    //new Variable("eip", $"0x{task.Eip:x8}", 0),
                    //new Variable("esp", $"0x{task.Esp:x8}", 0),
                    //new Variable("ebp", $"0x{task.Ebp:x8}", 0),

                    new Variable("eax", $"0x{gdbClient.Registers.Eax:x8}", 0, "register"),
                    new Variable("ecx", $"0x{gdbClient.Registers.Ecx:x8}", 0, "register"),
                    new Variable("edx", $"0x{gdbClient.Registers.Edx:x8}", 0, "register"),
                    new Variable("ebx", $"0x{gdbClient.Registers.Ebx:x8}", 0, "register"),
                    new Variable("esp", $"0x{gdbClient.Registers.Esp:x8}", 0, "register"),
                    new Variable("ebp", $"0x{gdbClient.Registers.Ebp:x8}", 0, "register"),
                    new Variable("esi", $"0x{gdbClient.Registers.Esi:x8}", 0, "register"),
                    new Variable("edi", $"0x{gdbClient.Registers.Edi:x8}", 0, "register"),
                    new Variable("eip", $"0x{gdbClient.Registers.Eip:x8}", 0, "register"),
                    new Variable("eflags", $"0x{gdbClient.Registers.Eflags:x8}", 0, "register"),
                    new Variable("cs", $"0x{gdbClient.Registers.Cs:x8}", 0, "register"),
                    new Variable("ss", $"0x{gdbClient.Registers.Ss:x8}", 0, "register"),
                    new Variable("ds", $"0x{gdbClient.Registers.Ds:x8}", 0, "register"),
                    new Variable("es", $"0x{gdbClient.Registers.Es:x8}", 0, "register"),
                    new Variable("fs", $"0x{gdbClient.Registers.Fs:x8}", 0, "register"),
                    new Variable("gs", $"0x{gdbClient.Registers.Gs:x8}", 0, "register")
                });
            }

            if (!internalFrames.TryGetValue(arguments.VariablesReference, out InternalFrame internalFrame))
                return new VariablesResponse();

            List<Variable> variables = new List<Variable>();

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

                variables.Add(new Variable
                (
                    name: variable.Name,
                    value: value,
                    variablesReference: 0,
                    type: typeName
                ));
            }

            return new VariablesResponse(variables: variables);
        }
        protected override SetVariableResponse HandleSetVariableRequest(SetVariableArguments arguments)
        {
            return base.HandleSetVariableRequest(arguments);
        }
        protected override EvaluateResponse HandleEvaluateRequest(EvaluateArguments arguments)
        {
            return new EvaluateResponse(result: null, variablesReference: 0);
        }
        protected override SetExpressionResponse HandleSetExpressionRequest(SetExpressionArguments arguments)
        {
            return base.HandleSetExpressionRequest(arguments);
        }

        internal Type GetTypeFromSymbol(PdbSymbol type)
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
        internal string GetTypeNameFromSymbol(PdbSymbol type)
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

        #region Modules

        protected override ModulesResponse HandleModulesRequest(ModulesArguments arguments)
        {
            //return new ModulesResponse(modules: modules.ToList(), totalModules: this.loadedModules.Count);
            return base.HandleModulesRequest(arguments);
        }

        #endregion

        #region Source Code Requests

        protected override SourceResponse HandleSourceRequest(SourceArguments arguments)
        {
            return new SourceResponse("For now all source requests return this line of 'code'.");
            //return base.HandleSourceRequest(arguments);
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

using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Pipes;
using System.Linq;

using Microsoft.VisualStudio.Shared.VSCodeDebugProtocol;
using Microsoft.VisualStudio.Shared.VSCodeDebugProtocol.Messages;
using Microsoft.VisualStudio.Shared.VSCodeDebugProtocol.Utilities;

using Newtonsoft.Json.Linq;

using Tools.Debugger.Wrappers;
using Tools.Gdb;
using Tools.Pdb;
using Tools.VirtualMachine;

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

            gdbClient.Breakpoints.Add(GdbBreakpointType.Memory, debuggerBreakFunction.RelativeVirtualAddress);
            gdbClient.Memory.Write(debuggerAttachedField.RelativeVirtualAddress, 0x01);

            gdbClient.Continue();
        }
        private void InitializeWrappers()
        {
            firstTask = new Pointer<Task>(gdbClient.Memory, taskFirstField.RelativeVirtualAddress);
            kernelTask = new Pointer<Task>(gdbClient.Memory, taskKernelField.RelativeVirtualAddress);
            currentTask = new Pointer<Task>(gdbClient.Memory, taskCurrentField.RelativeVirtualAddress);
            //Processes = new Collection<Pointer<Process>>(gdbClient.Memory, processesField.VirtualAddress);
        }

        private PdbSymbol FindSymbolByName(string name)
        {
            PdbSymbol result = pdbSessions
                .SelectMany(s => s.GlobalScope.FindChildren(name))
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
            if (address == debuggerBreakFunction.RelativeVirtualAddress)
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
            // Continue(step: false);

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
            gdbClient.Step();

            return new StepInResponse();
        }
        protected override StepOutResponse HandleStepOutRequest(StepOutArguments arguments)
        {
            gdbClient.Step();

            return new StepOutResponse();
        }
        protected override NextResponse HandleNextRequest(NextArguments arguments)
        {
            gdbClient.Step();

            return new NextResponse();
        }
        protected override PauseResponse HandlePauseRequest(PauseArguments arguments)
        {
            gdbClient.Break();

            return new PauseResponse();
        }

        #endregion

        #region Breakpoints

        protected override SetBreakpointsResponse HandleSetBreakpointsRequest(SetBreakpointsArguments arguments)
        {
            string sourcePath = arguments.Source.Path;
            List<Breakpoint> breakpoints = new List<Breakpoint>();

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
                    gdbClient.Breakpoints.Add(GdbBreakpointType.Memory, pdbLineNumber.RelativeVirtualAddress);

                    Breakpoint breakpoint = new Breakpoint
                    (
                        verified: true,
                        source: new Source
                        (
                            name: "Yop" + Path.GetFileName(sourcePath),
                            path: sourcePath
                        ),
                        line: (int)pdbLineNumber.LineNumber,
                        column: (int)pdbLineNumber.ColumnNumber
                    );

                    breakpoints.Add(breakpoint);
                }
            }

            return new SetBreakpointsResponse(breakpoints);
        }

        #endregion

        #region Debugger Properties

        internal bool? IsJustMyCodeOn { get; private set; }
        internal bool? IsStepFilteringOn { get; private set; }

        protected override SetDebuggerPropertyResponse HandleSetDebuggerPropertyRequest(SetDebuggerPropertyArguments arguments)
        {
            IsJustMyCodeOn = GetValueAsVariantBool(arguments.DebuggerProperties, "JustMyCodeStepping") ?? IsJustMyCodeOn;
            IsStepFilteringOn = GetValueAsVariantBool(arguments.DebuggerProperties, "EnableStepFiltering") ?? IsStepFilteringOn;

            return new SetDebuggerPropertyResponse();
        }

        /// <summary>
        /// Turns a debugger property value into a bool.
        /// Debugger properties use variants, so bools come as integers
        /// </summary>
        private static bool? GetValueAsVariantBool(Dictionary<string, JToken> properties, string propertyName)
        {
            int? value = properties.GetValueAsInt(propertyName);

            if (!value.HasValue)
            {
                return null;
            }

            return (int)value != 0;
        }

        #endregion

        #region Inspection

        protected override ThreadsResponse HandleThreadsRequest(ThreadsArguments arguments)
        {
            if (gdbClient.Running)
                throw new ProtocolException("Not in break mode!");

            //return new ThreadsResponse(threads: this.threads.Select(t => t.GetProtocolThread()).ToList());
            return base.HandleThreadsRequest(arguments);
        }
        protected override ScopesResponse HandleScopesRequest(ScopesArguments arguments)
        {
            return base.HandleScopesRequest(arguments);
        }

        protected override StackTraceResponse HandleStackTraceRequest(StackTraceArguments arguments)
        {
            if (gdbClient.Running)
                throw new ProtocolException("Not in break mode!");

            return base.HandleStackTraceRequest(arguments);
        }

        protected override VariablesResponse HandleVariablesRequest(VariablesArguments arguments)
        {
            return base.HandleVariablesRequest(arguments);
        }

        protected override SetVariableResponse HandleSetVariableRequest(SetVariableArguments arguments)
        {
            return base.HandleSetVariableRequest(arguments);
        }

        protected override EvaluateResponse HandleEvaluateRequest(EvaluateArguments arguments)
        {
            //return new EvaluateResponse(result: value, variablesReference: variablesReference);
            return base.HandleEvaluateRequest(arguments);
        }

        protected override SetExpressionResponse HandleSetExpressionRequest(SetExpressionArguments arguments)
        {
            return base.HandleSetExpressionRequest(arguments);
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
            //return new SourceResponse("For now all source requests return this line of 'code'.");
            return base.HandleSourceRequest(arguments);
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

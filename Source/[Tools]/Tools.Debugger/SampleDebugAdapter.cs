﻿// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License.

using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.Serialization;
using System.Text;
using System.Threading;
using Microsoft.VisualStudio.Shared.VSCodeDebugProtocol;
using Microsoft.VisualStudio.Shared.VSCodeDebugProtocol.Messages;
using Microsoft.VisualStudio.Shared.VSCodeDebugProtocol.Serialization;
using Microsoft.VisualStudio.Shared.VSCodeDebugProtocol.Utilities;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using Ookii.CommandLine;
using SampleDebugAdapter.Directives;
using static System.FormattableString;
using SysThread = System.Threading.Thread;

namespace SampleDebugAdapter
{
    internal class SampleDebugAdapter : DebugAdapterBase
    {
        private int currentLineNum;
        private bool stopAtEntry;
        private int hyperStepSpeed;
        private bool stopped;

        private ReadOnlyCollection<string> lines;
        private int nextId = 999;

        private SysThread debugThread;
        private ManualResetEvent runEvent;
        private StoppedEvent.ReasonValue? stopReason;
        private int stopThreadId;

        private object syncObject = new object();

        private DirectiveProcessor directiveProcessor;

        private SampleThread defaultThread;

        #region Constructor

        internal SampleDebugAdapter(Stream stdIn, Stream stdOut)
        {
            this.directiveProcessor = new DirectiveProcessor(this);

            // Register core directives
            this.RegisterDirective<DelayArgs>("Delay", this.DoDelay);
            this.RegisterDirective<SetPropertyArgs>("SetProperty", this.DoSetProperty);
            this.RegisterDirective<StdOutArgs>("StdOut", this.DoStdOut);
            this.RegisterDirective<PromptArgs>("Prompt", this.DoPrompt);
            this.RegisterDirective<ExitBreakArgs>("ExitBreak", this.DoExitBreak);
            this.RegisterDirective<GotoArgs>("Goto", this.DoGoto);

            this.ModuleManager = new ModuleManager(this);
            this.ThreadManager = new ThreadManager(this);
            this.ExceptionManager = new ExceptionManager(this);
            this.BreakpointManager = new BreakpointManager(this);
            this.ScriptManager = new SampleSourceManager(this);

            this.ShowGlobals = true;
            this.GlobalsScope = this.CreateGlobalsScope();

            this.runEvent = new ManualResetEvent(true);
            this.stopReason = null;

            base.InitializeProtocolClient(stdIn, stdOut);
        }

        private SampleScope CreateGlobalsScope()
        {
            SampleScope scope = new SampleScope(this, "Globals", false);
            scope.AddVariable(new WrapperVariable(this, "CurrentLine", "int", () => this.LineToClient(this.currentLineNum).ToString(CultureInfo.InvariantCulture)));
            scope.AddVariable(new WrapperVariable(this, "Line", "string", () => this.CurrentLine));
            scope.AddVariable(new WrapperVariable(this, "JustMyCodeStatus", "bool", () => (this.IsJustMyCodeOn ?? false) ? "on" : "off"));
            scope.AddVariable(new WrapperVariable(this, "StepFilteringStatus", "bool", () => (this.IsStepFilteringOn ?? false) ? "on" : "off"));

            SimpleVariable directiveInfo = new SimpleVariable(this, "DirectiveInfo", null, null);
            directiveInfo.AddChild(new WrapperVariable(this, "LineIsDirective", "bool", () => this.directiveProcessor.IsDirective(this.CurrentLine).ToString()));
            directiveInfo.AddChild(new WrapperVariable(this, "DirectiveArguments", null, () => null, () =>
            {
                string line = this.CurrentLine;
                if (this.directiveProcessor.IsDirective(line))
                {
                    object args = this.directiveProcessor.GetArguments(line);
                    if (args != null)
                    {
                        List<SampleVariable> argsVars = new List<SampleVariable>();

                        foreach (PropertyInfo pi in args.GetType().GetProperties())
                        {
                            object value = pi.GetValue(args);
                            if (value == null)
                            {
                                continue;
                            }

                            if (pi.PropertyType.IsArray)
                            {
                                SimpleVariable argsVar = new SimpleVariable(this, pi.Name, pi.PropertyType.Name, null);

                                int i = 0;
                                IEnumerable argsEnum = value as IEnumerable;
                                if (argsEnum != null)
                                {
                                    foreach (object val in (IEnumerable)value)
                                    {
                                        argsVar.AddChild(new SimpleVariable(this, i++.ToString(CultureInfo.InvariantCulture), null, val.ToString()));
                                    }
                                }

                                argsVars.Add(argsVar);
                            }
                            else
                            {
                                argsVars.Add(new SimpleVariable(this, pi.Name, pi.PropertyType.Name, value.ToString()));
                            }
                        }

                        return argsVars;
                    }
                }

                return null;
            }));

            scope.AddVariable(directiveInfo);

            return scope;
        }

        #endregion

        #region Delay Directive

        private class DelayArgs
        {
            [CommandLineArgument("ms", IsRequired = true, Position = 0, ValueDescription = "delay time in ms")]
            public int DelayTime { get; set; }
        }

        private bool DoDelay(DelayArgs arguments, StringBuilder output)
        {
            output.AppendLine(Invariant($"Sleeping for {arguments.DelayTime}ms"));
            SysThread.Sleep(arguments.DelayTime);

            return true;
        }

        #endregion

        #region SetProperty Directive

        private class SetPropertyArgs
        {
            [CommandLineArgument("name", IsRequired = true, Position = 0)]
            public string Name { get; set; }

            [CommandLineArgument("value", IsRequired = true, Position = 1)]
            public string Value { get; set; }
        }


        // The set of properties with bool values
        private static readonly HashSet<string> BoolProperties = new HashSet<string> {
            "ShowGlobals",
            "UseGlobalsScope",
            "UseArgsScope"
        };

        private void SetBoolProperty(string propertyName, bool value)
        {
            switch (propertyName)
            {
                case "ShowGlobals": this.ShowGlobals = value; return;
                case "UseGlobalsScope": this.UseGlobalsScope = value; return;
                case "UseArgsScope": this.UseArgsScope = value; return;
                default:
                    throw new InvalidOperationException("Bool property mapping isn't defined.");
            }
        }

        private bool DoSetProperty(SetPropertyArgs args, StringBuilder output)
        {
            if (SampleDebugAdapter.BoolProperties.Contains(args.Name))
            {
                bool boolValue;
                if (!Boolean.TryParse(args.Value, out boolValue))
                {
                    output.AppendLine(Invariant($"Could not parse '{args.Value}' as a boolean!"));
                    return false;
                }
                this.SetBoolProperty(args.Name, boolValue);
            }
            else
            {
                output.AppendLine(Invariant($"Unknown property '{args.Name}'!"));
                return false;
            }

            output.AppendLine(Invariant($"Set property '{args.Name}' to '{args.Value}'"));
            return true;
        }

        #endregion

        #region StdOut Directive

        private class StdOutArgs
        {
            [CommandLineArgument("text", IsRequired = true, Position = 0)]
            public string Text { get; set; }
        }

        private bool DoStdOut(StdOutArgs args, StringBuilder output)
        {
            Console.WriteLine(args.Text);
            output.AppendLine("StdOut: " + args.Text);
            return true;
        }

        #endregion

        #region Prompt Directive

        internal class PromptArgs
        {
            [CommandLineArgument("message", IsRequired = true, Position = 0)]
            [JsonProperty("message")]
            public string Message { get; set; }
        }

        internal class PromptResponse : ResponseBody
        {
            public enum ResponseValue
            {
                [EnumMember(Value = "ok")]
                OK,
                [EnumMember(Value = "cancel")]
                Cancel,
                [DefaultEnumValue]
                Unknown = Int32.MaxValue
            }

            public ResponseValue Response { get; set; }
        }

        internal class PromptRequest : DebugClientRequestWithResponse<PromptArgs, PromptResponse>
        {
            internal PromptRequest(string message) : base("prompt")
            {
                this.Args.Message = message;
            }
        }

        private bool DoPrompt(PromptArgs args, StringBuilder output)
        {
            PromptResponse response = this.Protocol.SendClientRequestSync(new PromptRequest(args.Message));

            output.AppendLine("Response: " + response.Response.ToString());
            return true;
        }

        #endregion

        #region ExitBreak Directive

        internal class ExitBreakArgs
        {
            [CommandLineArgument("delay", IsRequired = false, Position = 0, ValueDescription = "milliseconds")]
            public int? Delay { get; set; }
        }

        private bool DoExitBreak(ExitBreakArgs args, StringBuilder output)
        {
            if (this.runEvent.WaitOne(0))
            {
                output.AppendLine("Process is already running!");
                return false;
            }

            return this.ExitBreakCore(args.Delay ?? 0, false, output);
        }

        private Timer exitBreakTimer;
        internal bool ExitBreakCore(int delayMs, bool step = false, StringBuilder output = null)
        {
            Action continueAction = () =>
            {
                this.Protocol.SendEvent(new ContinuedEvent(threadId: this.stopThreadId));
                this.Continue(step);
            };

            if (delayMs != 0)
            {
                if (this.exitBreakTimer != null)
                {
                    output?.AppendLine("Another delayed ExitBreak operation is already pending!");
                    return false;
                }

                // Wait the specified amount of time before leaving break mode.  Do this on a background thread to
                //  avoid blocking VS if the directive is issued from the Immediate window, so we can still switch
                //  processes, etc.
                this.exitBreakTimer = new Timer(
                    (state) =>
                    {
                        continueAction();
                        if (this.exitBreakTimer != null)
                        {
                            this.exitBreakTimer.Dispose();
                            this.exitBreakTimer = null;
                        }
                    },
                    null,
                    delayMs,
                    Timeout.Infinite);

                output?.AppendFormat(CultureInfo.InvariantCulture, "Will exit break state in {0}ms.", delayMs);
                return true;
            }

            continueAction();
            output?.AppendLine("Forced process to exit break mode");
            return true;
        }

        #endregion

        private class GotoArgs
        {
            [CommandLineArgument("line", IsRequired = true, Position = 0, ValueDescription = "line number")]
            public int Line { get; set; }
        }

        private bool DoGoto(GotoArgs arguments, StringBuilder output)
        {
            if (arguments.Line < 1 || arguments.Line > this.lines.Count)
            {
                output.AppendLine("Line out of range");
                return false;
            }

            // Subtact 1 to adjust for 0-based indexing, and another 1 because the number will be incremented
            //  immediately after processing this directive.
            this.currentLineNum = arguments.Line - 2;
            return true;
        }

        internal Source Source { get; private set; }
        internal SampleScope GlobalsScope { get; }

        internal ModuleManager ModuleManager { get; }
        internal ThreadManager ThreadManager { get; }
        internal ExceptionManager ExceptionManager { get; }
        internal BreakpointManager BreakpointManager { get; }
        internal SampleSourceManager ScriptManager { get; }
        internal bool ShowGlobals { get; private set; }
        internal bool UseGlobalsScope { get; private set; }
        internal bool UseArgsScope { get; private set; }

        internal int GetNextId()
        {
            return Interlocked.Increment(ref this.nextId);
        }

        internal void Run()
        {
            this.Protocol.Run();
        }

        internal IReadOnlyList<string> Lines
        {
            get { return this.lines; }
        }

        internal string CurrentLine
        {
            get { return this.lines[this.currentLineNum]; }
        }

        #region Directive Registration

        internal void RegisterDirective<TArgs>(string name, Func<TArgs, StringBuilder, bool> executeFunc)
            where TArgs : class, new()
        {
            FuncWrapperDirective<TArgs> directive = new FuncWrapperDirective<TArgs>(name, executeFunc);
            this.directiveProcessor.RegisterDirective(directive);
        }

        private class FuncWrapperDirective<TArgs> : DirectiveBase<TArgs>
            where TArgs : class, new()
        {
            private Func<TArgs, StringBuilder, bool> executeFunc;

            internal FuncWrapperDirective(string directiveName, Func<TArgs, StringBuilder, bool> executeFunc) : base(directiveName)
            {
                this.executeFunc = executeFunc;
            }

            protected override bool ExecuteCore(TArgs arguments, StringBuilder output)
            {
                return this.executeFunc(arguments, output);
            }
        }

        #endregion

        #region Initialize/Disconnect

        protected override InitializeResponse HandleInitializeRequest(InitializeArguments arguments)
        {
            if (arguments.LinesStartAt1 == true)
                this.clientsFirstLine = 1;

            this.Protocol.SendEvent(new InitializedEvent());

            return new InitializeResponse(
                supportsConfigurationDoneRequest: true,
                supportsSetVariable: true,
                supportsDebuggerProperties: true,
                supportsModulesRequest: true,
                supportsSetExpression: true,
                supportsExceptionOptions: true,
                supportsExceptionConditions: true,
                supportsExceptionInfoRequest: true,
                supportsValueFormattingOptions: true,
                supportsEvaluateForHovers: true,

                // Additional module columns to support VS's "Modules" window
                additionalModuleColumns: new List<ColumnDescriptor>()
                {
                    new ColumnDescriptor(attributeName: "vsLoadAddress", label: "Load Address", type: ColumnDescriptor.TypeValue.String),
                    new ColumnDescriptor(attributeName: "vsPreferredLoadAddress", label: "Preferred Load Address", type: ColumnDescriptor.TypeValue.String),
                    new ColumnDescriptor(attributeName: "vsModuleSize", label: "Module Size", type: ColumnDescriptor.TypeValue.Number),
                    new ColumnDescriptor(attributeName: "vsLoadOrder", label: "Order", type: ColumnDescriptor.TypeValue.Number),
                    new ColumnDescriptor(attributeName: "vsTimestampUTC", label: "Timestamp", type: ColumnDescriptor.TypeValue.UnixTimestampUTC),
                    new ColumnDescriptor(attributeName: "vsIs64Bit", label: "64-bit", type: ColumnDescriptor.TypeValue.Boolean),
                    new ColumnDescriptor(attributeName: "vsAppDomain", label: "AppDomain", type: ColumnDescriptor.TypeValue.String),
                }
            );
        }

        protected override DisconnectResponse HandleDisconnectRequest(DisconnectArguments arguments)
        {
            this.currentLineNum = this.lines.Count + 1;
            this.Continue(step: false);

            // Ensure the debug thread has stopped before sending the response
            this.debugThread.Join();

            return new DisconnectResponse();
        }

        #endregion

        #region Launch

        protected override LaunchResponse HandleLaunchRequest(LaunchArguments arguments)
        {
            string fileName = arguments.ConfigurationProperties.GetValueAsString("program");
            if (String.IsNullOrEmpty(fileName))
            {
                throw new ProtocolException("Launch failed because launch configuration did not specify 'program'.");
            }

            fileName = Path.GetFullPath(fileName);
            if (!File.Exists(fileName))
            {
                throw new ProtocolException("Launch failed because 'program' files does not exist.");
            }

            this.Source = new Source(name: Path.GetFileName(fileName), path: fileName);
            this.stopAtEntry = arguments.ConfigurationProperties.GetValueAsBool("stopAtEntry") ?? false;
            this.hyperStepSpeed = arguments.ConfigurationProperties.GetValueAsInt("hyperStepSpeed") ?? 0;

            // Read the script file
            this.lines = File.ReadAllLines(fileName).Select(l => String.IsNullOrEmpty(l) ? null : l).ToList().AsReadOnly();

            return new LaunchResponse();
        }

        #endregion

        #region Continue/Stepping

        protected override ConfigurationDoneResponse HandleConfigurationDoneRequest(ConfigurationDoneArguments arguments)
        {
            this.defaultThread = this.ThreadManager.StartThread(0, "Main Thread");

            this.defaultThread.PushStackFrame(new SampleStackFrame(
                adapter: this,
                module: null,
                functionName: "ScriptMain",
                args: null,
                fileName: this.Source.Path,
                line: this.LineToClient(0),
                column: 0));

            if (this.stopAtEntry)
            {
                // Clear the event so we'll break at startup
                this.RequestStop(StoppedEvent.ReasonValue.Step);
            }

            this.debugThread = new SysThread(this.DebugThreadProc);
            this.debugThread.Name = "Debug Loop Thread";
            this.debugThread.Start();

            return new ConfigurationDoneResponse();
        }

        protected override ContinueResponse HandleContinueRequest(ContinueArguments arguments)
        {
            this.Continue(step: false);
            return new ContinueResponse();
        }

        protected override StepInResponse HandleStepInRequest(StepInArguments arguments)
        {
            this.Continue(step: true);
            return new StepInResponse();
        }

        protected override StepOutResponse HandleStepOutRequest(StepOutArguments arguments)
        {
            this.Continue(step: true);
            return new StepOutResponse();
        }

        protected override NextResponse HandleNextRequest(NextArguments arguments)
        {
            this.Continue(step: true);
            return new NextResponse();
        }

        /// <summary>
        /// Continues "debugging". This will either step or run until the next breakpoint or until
        /// the end of the file.
        /// </summary>
        private void Continue(bool step)
        {
            lock (this.syncObject)
            {
                // Reset all state before continuing
                this.ClearState();

                if (step)
                {
                    this.stopReason = StoppedEvent.ReasonValue.Step;
                }
                else
                {
                    this.stopReason = null;
                }
            }

            this.stopped = false;
            this.runEvent.Set();
        }

        private void ClearState()
        {
            this.nextId = 999;
            this.ThreadManager.Invalidate();
            this.ExceptionManager.Invalidate();
        }

        protected override PauseResponse HandlePauseRequest(PauseArguments arguments)
        {
            this.RequestStop(StoppedEvent.ReasonValue.Pause);
            return new PauseResponse();
        }

        #endregion

        #region Debug Thread

        private void DebugThreadProc()
        {
            bool needsExtraIncrement = false;

            do
            {
                lock (this.syncObject)
                {
                    if (!this.runEvent.WaitOne(0))
                    {
                        // Waiting on the run event would have blocked, so send a stopped event before we wait for the event to be set
                        if (!this.stopReason.HasValue)
                        {
                            throw new InvalidOperationException("Stopping for no reason!");
                        }

                        this.Protocol.SendEvent(new StoppedEvent(reason: this.stopReason.Value, threadId: this.stopThreadId));

                        if (this.hyperStepSpeed != 0 && this.stopReason.Value == StoppedEvent.ReasonValue.Step)
                        {
                            // In hyper-step mode, we automatically continue and issue another step after each step
                            this.ExitBreakCore(this.hyperStepSpeed, step: true);
                        }

                        this.stopReason = null;
                        this.stopped = true;
                    }
                }

                this.runEvent.WaitOne();

                if (needsExtraIncrement)
                {
                    this.currentLineNum++;
                    needsExtraIncrement = false;
                }

                if (this.currentLineNum >= this.lines.Count)
                {
                    // The "disconnect" request is handled by moving past the end of the list
                    break;
                }

                // Process the current line
                string line = this.CurrentLine;

                if (line != null)
                {
                    line = line.Trim();

                    if (!String.IsNullOrWhiteSpace(line))
                    {
                        if (this.directiveProcessor.IsDirective(line))
                        {
                            StringBuilder outputBuilder = new StringBuilder();
                            this.directiveProcessor.ProcessDirective(line, outputBuilder);

                            this.SendOutput(outputBuilder.ToString());
                        }
                        else if (line.StartsWith("#", StringComparison.Ordinal))
                        {
                            // Comment, do nothing
                        }
                        else
                        {
                            // Not a directive, just send it as an output event
                            this.SendOutput(line);
                        }
                    }
                }

                // If there's a pending exception, send a stopped event
                if (this.ExceptionManager.HasPendingException)
                {
                    // When an exception is hit, we want to stop on the line that threw the exception so things look right in the UI,
                    //  but if we don't move to the next line as we usually do, we'll just hit the throw again as soon as we continue.
                    //  To avoid this, set a flag to cause an extra increment the next time through the loop.
                    needsExtraIncrement = true;
                    this.RequestStop(StoppedEvent.ReasonValue.Exception, this.ExceptionManager.PendingExceptionThread);
                    continue;
                }

                // Move to the next line
                this.currentLineNum++;

                // Update top stack frame
                SampleStackFrame currentFrame = this.defaultThread.GetTopStackFrame();
                currentFrame.Line = this.LineToClient(this.currentLineNum);

                // If a breakpoint is encountered, send a stopped event
                if (this.BreakpointManager.HasLineBreakpoint(this.currentLineNum))
                {
                    this.RequestStop(StoppedEvent.ReasonValue.Breakpoint);
                    continue;
                }

                // If this is a step, stop on the next non-comment line with text
                if (this.stopReason == StoppedEvent.ReasonValue.Step &&
                    this.currentLineNum < this.lines.Count &&
                    this.CurrentLine != null &&
                    !this.CurrentLine.Trim().StartsWith("#", StringComparison.Ordinal))
                {
                    this.RequestStop(StoppedEvent.ReasonValue.Step);
                    continue;
                }
            } while (this.currentLineNum < this.lines.Count);

            // If there are no more lines, end "debugging"
            this.ThreadManager.EndThread(this.defaultThread);

            this.Protocol.SendEvent(new ExitedEvent(exitCode: 0));
            this.Protocol.SendEvent(new TerminatedEvent());
        }

        private void RequestStop(StoppedEvent.ReasonValue reason, int threadId = 0)
        {
            lock (this.syncObject)
            {
                this.stopReason = reason;
                this.stopThreadId = threadId;
                this.runEvent.Reset();
            }
        }

        private void SendOutput(string message)
        {
            string outputText = !String.IsNullOrEmpty(message) ? message.Trim() : String.Empty;

            this.Protocol.SendEvent(new OutputEvent(
                output: Invariant($"{outputText}{Environment.NewLine}"),
                category: OutputEvent.CategoryValue.Stdout));
        }

        #endregion

        #region Breakpoints

        protected override SetBreakpointsResponse HandleSetBreakpointsRequest(SetBreakpointsArguments arguments)
        {
            return this.BreakpointManager.HandleSetBreakpointsRequest(arguments);
        }

        #endregion

        #region Debugger Properties

        internal bool? IsJustMyCodeOn { get; private set; }
        internal bool? IsStepFilteringOn { get; private set; }

        protected override SetDebuggerPropertyResponse HandleSetDebuggerPropertyRequest(SetDebuggerPropertyArguments arguments)
        {
            this.IsJustMyCodeOn = GetValueAsVariantBool(arguments.DebuggerProperties, "JustMyCodeStepping") ?? this.IsJustMyCodeOn;
            this.IsStepFilteringOn = GetValueAsVariantBool(arguments.DebuggerProperties, "EnableStepFiltering") ?? this.IsStepFilteringOn;

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
            if (!this.stopped)
            {
                throw new ProtocolException("Not in break mode!");
            }

            return this.ThreadManager.HandleThreadsRequest(arguments);
        }

        protected override ScopesResponse HandleScopesRequest(ScopesArguments arguments)
        {
            return this.ThreadManager.HandleScopesRequest(arguments);
        }

        protected override StackTraceResponse HandleStackTraceRequest(StackTraceArguments arguments)
        {
            if (!this.stopped)
            {
                throw new ProtocolException("Not in break mode!");
            }

            return this.ThreadManager.HandleStackTraceRequest(arguments);
        }

        protected override VariablesResponse HandleVariablesRequest(VariablesArguments arguments)
        {
            return this.ThreadManager.HandleVariablesRequest(arguments);
        }

        protected override SetVariableResponse HandleSetVariableRequest(SetVariableArguments arguments)
        {
            return this.ThreadManager.HandleSetVariableRequest(arguments);
        }

        protected override EvaluateResponse HandleEvaluateRequest(EvaluateArguments arguments)
        {
            if (this.directiveProcessor.IsDirective(arguments.Expression))
            {
                string value = null;
                int variablesReference = 0;

                StringBuilder outputBuilder = new StringBuilder();
                this.directiveProcessor.ProcessDirective(arguments.Expression, outputBuilder);

                value = outputBuilder.ToString();

                return new EvaluateResponse(result: value, variablesReference: variablesReference);
            }

            return this.ThreadManager.HandleEvaluateRequest(arguments);
        }

        protected override SetExpressionResponse HandleSetExpressionRequest(SetExpressionArguments arguments)
        {
            return this.ThreadManager.HandleSetExpressionRequest(arguments);
        }

        #endregion

        #region Modules

        protected override ModulesResponse HandleModulesRequest(ModulesArguments arguments)
        {
            return this.ModuleManager.HandleModulesRequest(arguments);
        }

        #endregion

        #region Source Code Requests

        protected override SourceResponse HandleSourceRequest(SourceArguments arguments)
        {
            return this.ScriptManager.HandleSourceRequest(arguments);
        }

        #endregion

        #region Exceptions

        protected override ExceptionInfoResponse HandleExceptionInfoRequest(ExceptionInfoArguments arguments)
        {
            return this.ExceptionManager.HandleExceptionInfoRequest(arguments);
        }

        protected override SetExceptionBreakpointsResponse HandleSetExceptionBreakpointsRequest(SetExceptionBreakpointsArguments arguments)
        {
            return this.ExceptionManager.HandleSetExceptionBreakpointsRequest(arguments);
        }

        #endregion

        #region Convert Line Numbering To/From Client

        private int clientsFirstLine = 0;

        internal int LineToClient(int line)
        {
            return line + this.clientsFirstLine;
        }

        internal int LineFromClient(int line)
        {
            return line - this.clientsFirstLine;
        }

        #endregion
    }
}

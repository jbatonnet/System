using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Shell;

namespace Tools.Debugger
{
    public class DebuggerConsole : global::Shell.Shell
    {
        public override IVariableList Variables { get { return null; } }

        private byte[] buffer = new byte[4096];
        private string line = "";

        public DebuggerConsole()
        {
            Log.Resetted += Log_Resetted;
            Log.MessageSent += Log_MessageSent;
        }

        private void Log_Resetted()
        {
            OnClear();
        }
        private void Log_MessageSent(Log.LogMessage message)
        {
            //OnOutput(message.Content.Replace('\n', ' '), message.Color);
        }

        public override bool Run(string command)
        {
            command = command.ToLower();

            try
            {
                /*switch (command)
                {
                    // Global commands
                    case "": break;

                    // VM commands
                    case "quit":
                    case "exit":
                        MainForm.Instance.VirtualMachine.Stop();
                        Application.Exit();
                        return true;

                    case "stop":
                        MainForm.Instance.VirtualMachine.Stop();
                        return true;

                    case "start":
                        MainForm.Instance.VirtualMachine.Start();
                        return true;

                    case "restart":
                    case "reboot":
                        MainForm.Instance.VirtualMachine.Stop();
                        MainForm.Instance.VirtualMachine.Start();
                        return true;

                    // GDB commands
                    case "c":
                    case "continue":
                        MainForm.Instance.Gdb.Continue();
                        break;

                    case "b":
                    case "break":
                        MainForm.Instance.Gdb.Break();
                        OnOutput("EIP: 0x" + MainForm.Instance.Gdb.Eip.ToString("X8"));
                        break;

                    case "s":
                    case "step":
                        MainForm.Instance.Gdb.Step();
                        OnOutput("EIP: 0x" + MainForm.Instance.Gdb.Eip.ToString("X8"));
                        break;

                    case "r":
                    case "reg":
                    case "registers":
                        OnOutput("EIP: 0x" + MainForm.Instance.Gdb.Eip.ToString("X8"));
                        break;

                    // Other
                    default:
                        OnOutput("Unknown command " + command);
                        break;
                }*/
            }
            catch (Exception e)
            {
                OnOutput("Exception: " + e.Message);
            }

            return true;
        }
        public override List<AutoCompletion> GetCompletions(string line)
        {
            return new List<AutoCompletion>();
        }
    }

}

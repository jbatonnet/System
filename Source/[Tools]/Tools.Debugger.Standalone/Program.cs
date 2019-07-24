using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Pipes;
using System.Linq;
using System.Reflection;
using System.Windows.Forms;

namespace Tools.Debugger
{
    public static class Program
    {
        [STAThread]
        static void Main(params string[] args)
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            // Run the debugger
            Application.Run(new MainForm());

            // Force close the program
            Environment.Exit(0);
        }
    }
}
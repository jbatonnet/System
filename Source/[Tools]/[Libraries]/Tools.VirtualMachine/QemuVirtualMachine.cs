using System;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

namespace Tools.VirtualMachine
{
    public class QemuVirtualMachine : VirtualMachine
    {
        private static readonly string[] qemuPaths = new string[]
        {
            @"C:\Program Files\qemu\qemu-system-i386w.exe",
            @"C:\Program Files\qemu\qemu-system-i386.exe",
            @"C:\Program Files (x68)\qemu\qemu-system-i386w.exe",
            @"C:\Program Files (x68)\qemu\qemu-system-i386.exe",
        };

        private static FileInfo qemuExecutable;

        static QemuVirtualMachine()
        {
            string qemuPath = qemuPaths.FirstOrDefault(p => File.Exists(p));
            if (qemuPath == null)
                throw new NotSupportedException("Unable to find QEMU on this computer");

            qemuExecutable = new FileInfo(qemuPath);
        }

        public override bool Running => !process?.HasExited ?? false;

        private Process process;

        public QemuVirtualMachine(string path)
        {
            if (!File.Exists(path))
                throw new IOException("The specified file could not be found");

            Path = System.IO.Path.GetFullPath(path);
        }

        public override void Start()
        {
            ProcessStartInfo processStartInfo = new ProcessStartInfo(qemuExecutable.FullName);

            // Add QEMU arguments
            processStartInfo.Arguments = string.Join(" ", new string[]
            {
                "-name System", // Name: System
                "-m 1G", // Memory: 1 Go
                "-k fr", // Keyboard: French
                "-display gtk", // UI: GTK
                "-vga vmware", // GPU: VMware SVGA-II
                "-soundhw ac97", // Audio: ac97
                "-net nic", // Network: e2000
                //"-serial pipe:System", // Serial: named pipe
                "-usb", // USB
                "-no-reboot", // Exits when shut down
                "-gdb tcp::8832", // Enable GDB stub
                "-S", // Wait for GDB stub connection
                "-snapshot", // Forbid disk modification
                '"' + Path + '"'
            });

            // Start process
            process = Process.Start(processStartInfo);

            // Trigger start event after some delay
            Task.Delay(1).ContinueWith(t => Started(this, EventArgs.Empty));

            // Wait for process to exit
            Task.Run(() =>
            {
                try
                {
                    process.WaitForExit();
                }
                finally
                {
                    Stopped(this, EventArgs.Empty);
                }
            });
        }
        public override void Stop()
        {
            try
            {
                if (process != null && !process.HasExited)
                    process.Kill();
            }
            catch { }
        }

        public override event EventHandler Started;
        public override event EventHandler Stopped;
    }
}
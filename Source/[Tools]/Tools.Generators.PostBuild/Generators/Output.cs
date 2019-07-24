using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;

namespace Tools.Generator
{
    class Output
    {
        public static void Generate()
        {
            string rootPath = Path.Combine(Bootstrap.Root, @"Root");
            string vmdkPath = Path.Combine(Bootstrap.Root, @"VMware\Disk.vmdk");
            string drivePath = @"Z:";

            if (Program.VirtualMachine != null && Program.VirtualMachine.Running)
                Program.VirtualMachine.Stop();

            // Find the first unused drive
            DriveInfo[] drives = DriveInfo.GetDrives();
            while (drives.Any(d => d.Name.ToUpper().StartsWith(drivePath)))
                drivePath = ((char)(drivePath[0] - 1)).ToString() + ":";

            // Mount the virtual disk
            RunCommand(drivePath + " \"" + vmdkPath + "\"");

            // Duplicate directory structure
            foreach (string directory in Directory.GetDirectories(rootPath, "*", SearchOption.AllDirectories))
            {
                string shortPath = Path.Combine(drivePath + "\\", directory.Replace(rootPath, "").TrimStart('\\'));
                Directory.CreateDirectory(shortPath);
            }

            // Copy all files
            foreach (string file in Directory.GetFiles(rootPath, "*", SearchOption.AllDirectories))
            {
                string shortPath = Path.Combine(drivePath + "\\", file.Replace(rootPath, "").TrimStart('\\'));
                File.Copy(file, shortPath, true);
            }

            // Unmount the virtual disk
            RunCommand("/d /f " + drivePath);
        }

        private static List<string> RunCommand(string parameters)
        {
            string path = Path.Combine(Bootstrap.Root, @"Tools\VMware\VDDK\vmware-mount.exe");
            List<string> result = new List<string>();

            ProcessStartInfo processStartInfo = new ProcessStartInfo(path, parameters);
            processStartInfo.RedirectStandardOutput = true;
            processStartInfo.RedirectStandardError = true;
            processStartInfo.UseShellExecute = false;
            processStartInfo.CreateNoWindow = true;

            Process process = Process.Start(processStartInfo);
            while (!process.StandardOutput.EndOfStream)
                result.Add(process.StandardOutput.ReadLine());
            while (!process.StandardError.EndOfStream)
                result.Add(process.StandardOutput.ReadLine());
            process.WaitForExit();

            return result;
        }
    }
}
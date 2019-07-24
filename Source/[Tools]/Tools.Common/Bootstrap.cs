using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Windows.Forms;

internal static class Bootstrap
{
    private static readonly string[] rootDirectories = new string[] { "Root", "Source", "Tools" };

    public static string Root { get; }
    public static string Source => Path.Combine(Root, "Source");

    public static Dictionary<string, string> Parameters { get; }

    static Bootstrap()
    {
        Parameters = string.Join(" ", Environment.GetCommandLineArgs())
            .Split(new char[] { '&', '/', '-' }, StringSplitOptions.RemoveEmptyEntries)
            .Select(p => new { Parameter = p.Trim(), Separator = p.Trim().IndexOfAny(new char[] { ':', '=' }) })
            .ToDictionary(p => p.Separator == -1 ? p.Parameter : p.Parameter.Substring(0, p.Separator), p => p.Separator == -1 ? null : p.Parameter.Substring(p.Separator + 1));

        string path = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);

        while (true)
        {
            if (rootDirectories.All(d => Directory.Exists(Path.Combine(path, "Root"))))
                break;

            if (path.Length == 2)
            {
                MessageBox.Show("Unable to find project root", "System", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            path = Path.GetDirectoryName(path);
        }

        Root = path;
    }
}
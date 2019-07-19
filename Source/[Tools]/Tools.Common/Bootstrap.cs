using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Windows.Forms;

internal static class Bootstrap
{
    private static readonly string[] rootDirectories = new string[] { "Root", "Source", "Tools" };

    private static string root;
    public static string Root
    {
        get
        {
            if (root == null)
            {
                string path = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);

                while (true)
                {
                    if (rootDirectories.All(d => Directory.Exists(Path.Combine(path, "Root"))))
                        break;

                    if (path.Length == 2)
                    {
                        MessageBox.Show("Unable to find project root", "System", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        return null;
                    }

                    path = Path.GetDirectoryName(path);
                }

                root = path;
            }

            return root;
        }
    }
    public static string Source
    {
        get
        {
            return Path.Combine(Root, "Source");
        }
    }

    private static Dictionary<string, string> parameters;
    public static Dictionary<string, string> Parameters
    {
        get
        {
            if (parameters == null)
            {
                parameters = string.Join(" ", Environment.GetCommandLineArgs())
                                    .Split(new char[] { '&', '/', '-' }, StringSplitOptions.RemoveEmptyEntries)
                                    .Select(p => new { Parameter = p.Trim(), Separator = p.Trim().IndexOfAny(new char[] { ':', '=' }) })
                                    .ToDictionary(p => p.Separator == -1 ? p.Parameter : p.Parameter.Substring(0, p.Separator), p => p.Separator == -1 ? null : p.Parameter.Substring(p.Separator + 1));
            }

            return parameters;
        }
    }
}
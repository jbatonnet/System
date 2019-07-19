using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Tools.Parser.Units;

namespace Tools.Parser.Parsers
{
    using File = Units.File;
    using Type = Units.Type;

    public class CppFile : File
    {
        public override string Path
        {
            get
            {
                return path;
            }
        }
        public override IEnumerable<Namespace> Namespaces
        {
            get
            {
                return namespaces;
            }
        }
        public override IEnumerable<Type> Types
        {
            get
            {
                return types;
            }
        }

        internal string path;
        internal List<Namespace> namespaces = new List<Namespace>();
        internal List<Type> types = new List<Type>();

        public CppFile(string path)
        {
            this.path = System.IO.Path.GetFullPath(path);
            Name = System.IO.Path.GetFileName(path);
        }
    }
}
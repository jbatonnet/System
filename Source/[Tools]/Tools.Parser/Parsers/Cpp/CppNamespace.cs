using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

using Tools.Parser.Units;

namespace Tools.Parser.Parsers
{
    using File = Units.File;
    using Type = Units.Type;

    public class CppNamespace : Namespace
    {
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

        internal List<Namespace> namespaces = new List<Namespace>();
        internal List<Type> types = new List<Type>();

        public CppNamespace(Unit parent, string name)
        {
            Parent = parent;
            Name = name;
        }
    }
}
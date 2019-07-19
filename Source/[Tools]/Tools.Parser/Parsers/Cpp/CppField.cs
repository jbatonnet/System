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

    public class CppField : Field
    {
        public override Method GetAccessor
        {
            get
            {
                return getAccessor;
            }
        }
        public override Method SetAccessor
        {
            get
            {
                return setAccessor;
            }
        }
        public override Modifiers Modifiers
        {
            get
            {
                return modifiers;
            }
        }
        public override Type Type
        {
            get
            {
                return type;
            }
        }

        internal Method getAccessor, setAccessor;
        internal Modifiers modifiers;
        internal Type type;

        internal long offset;
        internal List<string> clones = new List<string>();

        public CppField(Unit parent, string name)
        {
            Parent = parent;
            Name = name;
        }
    }
}
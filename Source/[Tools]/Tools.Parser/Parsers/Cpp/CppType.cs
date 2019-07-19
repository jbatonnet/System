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

    public class CppType : Type
    {
        private static Regex TypeDetector = new Regex(@"(const\s*)?([\w:]+)(?:\s*<\s*([\w*& <>:]*)\s*>)?((?:\s*\*)*)(?:\s*(&))?", RegexOptions.Compiled);

        public new Unit Parent
        {
            get
            {
                return base.Parent;
            }
            internal set
            {
                base.Parent = value;
            }
        }
        public new string Name
        {
            get
            {
                return base.Name;
            }
            internal set
            {
                base.Name = value;
            }
        }
        public new string[] Documentation
        {
            get
            {
                return base.Documentation;
            }
            internal set
            {
                base.Documentation = value;
            }
        }

        public override TypeStyle Style
        {
            get
            {
                return style;
            }
        }
        public override Modifiers Modifiers
        {
            get
            {
                return modifiers;
            }
        }
        public override IEnumerable<Type> Bases
        {
            get
            {
                return bases;
            }
        }
        public override IEnumerable<Type> Templates
        {
            get
            {
                return templates;
            }
        }
        public override IEnumerable<Type> Types
        {
            get
            {
                return types;
            }
        }
        public override IEnumerable<Field> Fields
        {
            get
            {
                return fields;
            }
        }
        public override IEnumerable<Method> Methods
        {
            get
            {
                return methods;
            }
        }

        internal TypeStyle style;
        internal Modifiers modifiers;
        internal List<Type> bases = new List<Type>();
        internal List<Type> templates = new List<Type>();
        internal List<Type> types = new List<Type>();
        internal List<Field> fields = new List<Field>();
        internal List<Method> methods = new List<Method>();

        internal Modifiers currentModifier;

        public CppType()
        {
        }
        public CppType(string name)
        {
            style = TypeStyle.Struct;
            Name = name;
        }

        public static Type GetReference(string name, IEnumerable<Type> hintTypes = null)
        {
            Match match = TypeDetector.Match(name.Trim());

            Type type = new Temporary(match.Groups[2].Value.Trim(':'));

            //if (match.Groups[3].Success)
            //    for (int i = 0; i < match.Groups[3].Captures.Count; i++)
            //        type.Templates.Add(GetReference(match.Groups[3].Captures[i].Value));

            if (match.Groups[4].Success)
                for (int i = 0; i < Regex.Replace(match.Groups[4].Value, @"\s*", "").Length; i++)
                    type = new Pointer(type);

            if (match.Groups[5].Success)
                type = new Reference(type);

            //if (name.EndsWith("..."))
            //    type.Name += "...";

            return type;
        }
    }
}
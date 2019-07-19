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

    public class CppMethod : Method
    {        
        public override Modifiers Modifiers
        {
            get
            {
                return modifiers;
            }
        }
        public override Type Result
        {
            get
            {
                return result;
            }
        }
        public override bool Abstract
        {
            get
            {
                return isAbstract;
            }
        }
        public override IEnumerable<KeyValuePair<string, Type>> Parameters
        {
            get
            {
                return parameters;
            }
        }
        public override IEnumerable<Type> Templates
        {
            get
            {
                return templates;
            }
        }

        internal Modifiers modifiers;
        internal Type result;
        internal bool isAbstract;
        internal Dictionary<string, Type> parameters = new Dictionary<string, Type>();
        internal List<Type> templates = new List<Type>();

        internal List<string> instructions = new List<string>();

        public CppMethod(Unit parent, string name)
        {
            Parent = parent;
            Name = name;
        }
    }

    public class CppConstructor : CppMethod
    {
        public CppConstructor(CppType parent) : base(parent, parent.Name) { }
    }

    public class CppDestructor : CppMethod
    {
        public CppDestructor(CppType parent) : base(parent, parent.Name) { }
    }
}
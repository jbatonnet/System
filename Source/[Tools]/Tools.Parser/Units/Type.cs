using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace Tools.Parser.Units
{
    public enum TypeStyle
    {
        Class,
        Struct,
        Enum,
        Union
    }

    public abstract class Type : Unit
    {
        public class BuiltIn : Type
        {
            public override TypeStyle Style
            {
                get
                {
                    return TypeStyle.Struct;
                }
            }
            public override Modifiers Modifiers
            {
                get
                {
                    return Modifiers.Public;
                }
            }
            public override IEnumerable<Type> Bases
            {
                get
                {
                    return Enumerable.Empty<Type>();
                }
            }
            public override IEnumerable<Type> Templates
            {
                get
                {
                    return Enumerable.Empty<Type>();
                }
            }
            public override IEnumerable<Type> Types
            {
                get
                {
                    return Enumerable.Empty<Type>();
                }
            }
            public override IEnumerable<Field> Fields
            {
                get
                {
                    return Enumerable.Empty<Field>();
                }
            }
            public override IEnumerable<Method> Methods
            {
                get
                {
                    return Enumerable.Empty<Method>();
                }
            }

            internal BuiltIn(string name)
            {
                Parent = null;
                Name = name;
            }
        }
        public class Template : Type
        {
            public override Modifiers Modifiers
            {
                get
                {
                    return Modifiers.None;
                }
            }
            public override TypeStyle Style
            {
                get
                {
                    return TypeStyle.Struct;
                }
            }

            public override IEnumerable<Type> Bases
            {
                get
                {
                    return Enumerable.Empty<Type>();
                }
            }
            public override IEnumerable<Field> Fields
            {
                get
                {
                    return Enumerable.Empty<Field>();
                }
            }
            public override IEnumerable<Method> Methods
            {
                get
                {
                    return Enumerable.Empty<Method>();
                }
            }
            public override IEnumerable<Type> Templates
            {
                get
                {
                    return Enumerable.Empty<Type>();
                }
            }
            public override IEnumerable<Type> Types
            {
                get
                {
                    return Enumerable.Empty<Type>();
                }
            }

            public Template(string name)
            {
                Name = name;
            }
        }
        public class Reference : Type
        {
            public Type Type { get; set; }

            public override TypeStyle Style
            {
                get
                {
                    return Type.Style;
                }
            }
            public override Modifiers Modifiers
            {
                get
                {
                    return Type.Modifiers;
                }
            }

            public override IEnumerable<Type> Bases
            {
                get
                {
                    return Type.Bases;
                }
            }
            public override IEnumerable<Type> Templates
            {
                get
                {
                    return Type.Templates;
                }
            }
            public override IEnumerable<Type> Types
            {
                get
                {
                    return Type.Types;
                }
            }
            public override IEnumerable<Field> Fields
            {
                get
                {
                    return Type.Fields;
                }
            }
            public override IEnumerable<Method> Methods
            {
                get
                {
                    return Type.Methods;
                }
            }

            public Reference(Type type)
            {
                Type = type;
            }
        }
        public class Pointer : Type
        {
            public Type Type { get; set; }

            public override TypeStyle Style
            {
                get
                {
                    return Type.Style;
                }
            }
            public override Modifiers Modifiers
            {
                get
                {
                    return Type.Modifiers;
                }
            }

            public override IEnumerable<Type> Bases
            {
                get
                {
                    return Type.Bases;
                }
            }
            public override IEnumerable<Type> Templates
            {
                get
                {
                    return Type.Templates;
                }
            }
            public override IEnumerable<Type> Types
            {
                get
                {
                    return Type.Types;
                }
            }
            public override IEnumerable<Field> Fields
            {
                get
                {
                    return Type.Fields;
                }
            }
            public override IEnumerable<Method> Methods
            {
                get
                {
                    return Type.Methods;
                }
            }

            public Pointer(Type type)
            {
                Type = type;
            }
        }
        public class Alias : Type
        {
            public Type Type { get; set; }

            public override TypeStyle Style
            {
                get
                {
                    return Type.Style;
                }
            }
            public override Modifiers Modifiers
            {
                get
                {
                    return Type.Modifiers;
                }
            }

            public override IEnumerable<Type> Bases
            {
                get
                {
                    return Type.Bases;
                }
            }
            public override IEnumerable<Type> Templates
            {
                get
                {
                    return Type.Templates;
                }
            }
            public override IEnumerable<Type> Types
            {
                get
                {
                    return Type.Types;
                }
            }
            public override IEnumerable<Field> Fields
            {
                get
                {
                    return Type.Fields;
                }
            }
            public override IEnumerable<Method> Methods
            {
                get
                {
                    return Type.Methods;
                }
            }

            public Alias(string name, Type type)
            {
                Name = name;
                Type = type;
            }
        }
        public class Temporary : Type
        {
            public override Modifiers Modifiers
            {
                get
                {
                    return Modifiers.None;
                }
            }
            public override TypeStyle Style
            {
                get
                {
                    return TypeStyle.Struct;
                }
            }

            public override IEnumerable<Type> Bases
            {
                get
                {
                    return Enumerable.Empty<Type>();
                }
            }
            public override IEnumerable<Field> Fields
            {
                get
                {
                    return Enumerable.Empty<Field>();
                }
            }
            public override IEnumerable<Method> Methods
            {
                get
                {
                    return Enumerable.Empty<Method>();
                }
            }
            public override IEnumerable<Type> Templates
            {
                get
                {
                    return Enumerable.Empty<Type>();
                }
            }
            public override IEnumerable<Type> Types
            {
                get
                {
                    return Enumerable.Empty<Type>();
                }
            }

            public Temporary(string name)
            {
                Name = name;
            }
        }

        public abstract TypeStyle Style { get; }
        public abstract Modifiers Modifiers { get; }

        public abstract IEnumerable<Type> Bases { get; }
        public abstract IEnumerable<Type> Templates { get; }

        public abstract IEnumerable<Type> Types { get; }
        public abstract IEnumerable<Field> Fields { get; }
        public abstract IEnumerable<Method> Methods { get; }
    }
}
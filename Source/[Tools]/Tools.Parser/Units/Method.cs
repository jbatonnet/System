using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace Tools.Parser.Units
{
    public abstract class Method : Unit
    {
        public abstract class Temporary : Method
        {
            public Temporary(string name)
            {
                Name = name;
            }
        }

        public abstract Modifiers Modifiers { get; }
        public abstract Type Result { get; }
        public abstract bool Abstract { get; }

        public abstract IEnumerable<KeyValuePair<string, Type>> Parameters { get; }
        public abstract IEnumerable<Type> Templates { get; }

        public override int GetHashCode()
        {
            throw new NotImplementedException();
        }
    }
}
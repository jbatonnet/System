using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace Tools.Parser.Units
{
    public abstract class Field : Unit
    {
        public abstract Method GetAccessor { get; }
        public abstract Method SetAccessor { get; }

        public abstract Modifiers Modifiers { get; }
        public abstract Type Type { get; }

        public int GetGetAccessorHashCode()
        {
            return CRC32.Compute(Encoding.UTF8.GetBytes(this + "::Get()"));
        }
        public int GetSetAccessorHashCode()
        {
            return CRC32.Compute(Encoding.UTF8.GetBytes(this + "::Set(" + Type + " value)"));
        }
    }
}
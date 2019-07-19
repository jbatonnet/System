using System;
using System.Collections.Generic;

using Tools.Parser.Generators;

namespace Tools.Parser.Units
{
    public abstract class Unit : IEquatable<Unit>
    {
        public string Name { get; protected set; }

        public Unit Parent { get; set; }
        public string[] Documentation { get; set; }
        
        public string ToIdentifier<T>() where T : Generator, new()
        {
            return ToIdentifier(new T());
        }
        public string ToIdentifier(Generator generator)
        {
            return generator.GetIdentifier(this);
        }
        public string ToDisplay<T>() where T : Generator, new()
        {
            return ToDisplay(new T());
        }
        public string ToDisplay(Generator generator)
        {
            return generator.GetDisplay(this);
        }

        public bool Equals(Unit other)
        {
            if (Name != other.Name)
                return false;
            if (Parent == null && other.Parent == null)
                return true;

            return Parent.Equals(other.Parent);
        }

        public override string ToString()
        {
            return ToIdentifier<DefaultGenerator>();
        }
    }
}
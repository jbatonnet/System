using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Tools.Parser.Units
{
    public abstract class File : Unit
    {
        public abstract string Path { get; }

        public abstract IEnumerable<Namespace> Namespaces { get; }
        public abstract IEnumerable<Type> Types { get; }
    }
}
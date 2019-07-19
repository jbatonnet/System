using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace Tools.Parser.Units
{
    public abstract class Namespace : Unit
    {
        public abstract IEnumerable<Namespace> Namespaces { get; }
        public abstract IEnumerable<Type> Types { get; }
    }
}
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Tools.Parser.Units;

namespace Tools.Parser
{
    using Type = Units.Type;

    public abstract class Parser
    {
        public abstract IEnumerable<File> Files { get; }

        public abstract void AddFile(string path);
    }
}
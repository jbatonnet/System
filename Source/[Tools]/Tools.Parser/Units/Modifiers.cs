using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Tools.Parser.Units
{
    [Flags]
    public enum Modifiers
    {
        None = 0x0000,
        Public = 0x0001,
        Protected = 0x0002,
        Private = 0x0004,
        Internal = 0x0008,
        Friend = 0x0010,
        Final = 0x0020,
        Abstract = 0x0040,
        Shared = 0x0080,
        Static = 0x0100,
        Virtual = 0x0200,
        Template = 0x0400,
        Linked = 0x0800,
    }
}
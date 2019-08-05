using Tools.Pdb;

namespace Tools.Debugger.Model
{
    internal class InternalFrame
    {
        public PdbSymbol Symbol { get; set; }
        public uint Ebp { get; set; }
    }
}

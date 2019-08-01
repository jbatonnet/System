using System.Collections.Generic;

using Dia2Lib;

namespace Tools.Pdb
{
    public class PdbSession
    {
        public ulong LoadAddress => diaSession.loadAddress;
        public PdbSymbol GlobalScope => PdbSymbol.From(diaSession.globalScope);

        public IEnumerable<PdbSymbol> Symbols
        {
            get
            {
                diaSession.getEnumTables(out IDiaEnumTables diaEnumTables);
                if (diaEnumTables == null)
                    return null;

                uint celt = 0;
                IDiaTable diaTable = null;
                while (true)
                {
                    diaEnumTables.Next(1, ref diaTable, ref celt);
                    if (celt != 1)
                        break;

                    if (diaTable is IDiaEnumSymbols diaEnumSymbols)
                        return PdbSymbol.EnumerateFrom(diaEnumSymbols);
                }

                return null;
            }
        }
        public IEnumerable<PdbSourceFile> SourceFiles
        {
            get
            {
                diaSession.getEnumTables(out IDiaEnumTables diaEnumTables);
                if (diaEnumTables == null)
                    return null;

                uint celt = 0;
                IDiaTable diaTable = null;
                while (true)
                {
                    diaEnumTables.Next(1, ref diaTable, ref celt);
                    if (celt != 1)
                        break;

                    if (diaTable is IDiaEnumSourceFiles diaEnumSourceFiles)
                        return PdbSourceFile.EnumerateFrom(diaEnumSourceFiles);
                }

                return null;
            }
        }

        private IDiaSession diaSession;

        internal PdbSession(IDiaSession diaSession)
        {
            this.diaSession = diaSession;
        }

        public PdbSymbol GetSymbolAtAddress(PdbSymbolTag tag, uint section, uint offset)
        {
            diaSession.findSymbolByAddr(section, offset, (SymTagEnum)tag, out IDiaSymbol diaSymbol);
            return PdbSymbol.From(diaSymbol);
        }
        public PdbSymbol GetSymbolAtVirtualAddress(PdbSymbolTag tag, ulong address)
        {
            diaSession.findSymbolByVA(address, (SymTagEnum)tag, out IDiaSymbol diaSymbol);
            return PdbSymbol.From(diaSymbol);
        }
        public PdbSymbol GetSymbolAtRelativeVirtualAddress(PdbSymbolTag tag, uint address)
        {
            diaSession.findSymbolByRVA(address, (SymTagEnum)tag, out IDiaSymbol diaSymbol);
            return PdbSymbol.From(diaSymbol);
        }

        public (uint Section, uint Offset) GetAddressFromVirtualAddress(ulong address)
        {
            diaSession.addressForVA(address, out uint section, out uint offset);
            return (section, offset);
        }
        public (uint Section, uint Offset) GetAddressFromRelativeVirtualAddress(uint address)
        {
            diaSession.addressForRVA(address, out uint section, out uint offset);
            return (section, offset);
        }

        public IEnumerable<PdbLineNumber> FindLinesByAddress(uint section, uint offset, uint length)
        {
            diaSession.findLinesByAddr(section, offset, length, out IDiaEnumLineNumbers diaEnumLineNumbers);
            return PdbLineNumber.EnumerateFrom(diaEnumLineNumbers);
        }
        public IEnumerable<PdbLineNumber> FindLinesByVirtualAddress(ulong address, uint length)
        {
            diaSession.findLinesByVA(address, length, out IDiaEnumLineNumbers diaEnumLineNumbers);
            return PdbLineNumber.EnumerateFrom(diaEnumLineNumbers);
        }
        public IEnumerable<PdbLineNumber> FindLinesByRelativeVirtualAddress(uint address, uint length)
        {
            diaSession.findLinesByRVA(address, length, out IDiaEnumLineNumbers diaEnumLineNumbers);
            return PdbLineNumber.EnumerateFrom(diaEnumLineNumbers);
        }
    }
}

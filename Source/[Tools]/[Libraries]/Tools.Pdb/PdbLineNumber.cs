using System.Collections.Generic;

using Dia2Lib;

namespace Tools.Pdb
{
    public class PdbLineNumber
    {
        public PdbSymbol Compiland => PdbSymbol.From(diaLineNumber.compiland);
        public PdbSourceFile SourceFile => PdbSourceFile.From(diaLineNumber.sourceFile);
        public uint LineNumber => diaLineNumber.lineNumber;
        public uint LineNumberEnd => diaLineNumber.lineNumberEnd;
        public uint ColumnNumber => diaLineNumber.columnNumber;
        public uint ColumnNumberEnd => diaLineNumber.columnNumberEnd;
        public uint AddressSection => diaLineNumber.addressSection;
        public uint AddressOffset => diaLineNumber.addressOffset;
        public uint RelativeVirtualAddress => diaLineNumber.relativeVirtualAddress;
        public ulong VirtualAddress => diaLineNumber.virtualAddress;
        public uint Length => diaLineNumber.length;
        public uint SourceFileId => diaLineNumber.sourceFileId;
        public int Statement => diaLineNumber.statement;
        public uint CompilandId => diaLineNumber.compilandId;

        internal IDiaLineNumber diaLineNumber;

        private PdbLineNumber(IDiaLineNumber diaLineNumber)
        {
            this.diaLineNumber = diaLineNumber;
        }

        internal static PdbLineNumber From(IDiaLineNumber diaLineNumber)
        {
            if (diaLineNumber == null)
                return null;

            return new PdbLineNumber(diaLineNumber);
        }
        internal static IEnumerable<PdbLineNumber> EnumerateFrom(IDiaEnumLineNumbers diaEnumLineNumbers)
        {
            if (diaEnumLineNumbers == null)
                yield break;

            diaEnumLineNumbers.Reset();

            while (true)
            {
                diaEnumLineNumbers.Next(1, out IDiaLineNumber diaLineNumber, out uint read);
                if (read == 0)
                    break;

                yield return new PdbLineNumber(diaLineNumber);
            }
        }
    }
}

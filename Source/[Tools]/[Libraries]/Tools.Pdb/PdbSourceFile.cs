using System.Collections.Generic;

using Dia2Lib;

namespace Tools.Pdb
{
    public class PdbSourceFile
    {
        public string FileName => diaSourceFile.fileName;
        public uint UniqueId => diaSourceFile.uniqueId;
        public IEnumerable<PdbSymbol> Compilands => PdbSymbol.EnumerateFrom(diaSourceFile.compilands);

        private IDiaSourceFile diaSourceFile;

        private PdbSourceFile(IDiaSourceFile diaSourceFile)
        {
            this.diaSourceFile = diaSourceFile;
        }

        public override string ToString() => FileName;

        internal static PdbSourceFile From(IDiaSourceFile diaSourceFile)
        {
            if (diaSourceFile == null)
                return null;

            return new PdbSourceFile(diaSourceFile);
        }
        internal static IEnumerable<PdbSourceFile> EnumerateFrom(IDiaEnumSourceFiles diaEnumSourceFiles)
        {
            if (diaEnumSourceFiles == null)
                yield break;

            diaEnumSourceFiles.Reset();

            while (true)
            {
                diaEnumSourceFiles.Next(1, out IDiaSourceFile diaSourceFile, out uint read);
                if (read == 0)
                    break;

                yield return new PdbSourceFile(diaSourceFile);
            }
        }
    }
}

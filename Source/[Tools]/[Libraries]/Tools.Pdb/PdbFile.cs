using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Dia2Lib;

namespace Tools.Pdb
{
    public class PdbFile
    {
        private IDiaDataSource diaDataSource;

        public PdbFile(string path)
        {
            if (!File.Exists(path))
                throw new FileNotFoundException(path);

            diaDataSource = new DiaSource();
            diaDataSource.loadDataFromPdb(path);
        }

        public PdbSession OpenSession(ulong address)
        {
            diaDataSource.openSession(out IDiaSession diaSession);
            diaSession.loadAddress = address;
            return new PdbSession(diaSession);
        }
    }
}

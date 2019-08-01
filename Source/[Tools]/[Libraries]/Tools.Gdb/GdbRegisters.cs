using System;

namespace Tools.Gdb
{
    public class GdbRegisters
    {
        private GdbClient gdbClient;

        internal GdbRegisters(GdbClient gdbClient)
        {
            this.gdbClient = gdbClient;
        }

        protected ulong ReadRegister(int index)
        {
            if (gdbClient.Running)
                throw new NotSupportedException("Cannot read register while running");

            string command = "g";
            string response = gdbClient.Query(command);

            response = response.Substring(index * 8, 8);

            //string command = string.Format("p{0:x}", index);
            //string response = gdbStub.Query(command);

            byte[] buffer = new byte[response.Length / 2];
            for (int i = 0; i < buffer.Length; i++)
                buffer[i] = Convert.ToByte(response.Substring(i * 2, 2), 16);

            switch (buffer.Length)
            {
                case 8: return BitConverter.ToUInt64(buffer, 0);
                case 4: return BitConverter.ToUInt32(buffer, 0);
                case 2: return BitConverter.ToUInt16(buffer, 0);
            }

            throw new Exception("Could not find register size");
        }
        protected void WriteRegister(int index, ulong value)
        {
            if (gdbClient.Running)
                throw new NotSupportedException("Cannot read register while running");

            byte[] buffer = BitConverter.GetBytes(value);
            string valueBuffer = "";

            for (int i = 0; i < buffer.Length; i++)
                valueBuffer += buffer[i].ToString("x2");

            string command = string.Format("P{0:x}={1:x}", index, valueBuffer);
            string response = gdbClient.Query(command);

            if (response != "OK")
                throw new Exception("Unable to write regsiter");
        }
    }
}
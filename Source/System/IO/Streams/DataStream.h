#ifndef _SYSTEM_DATASTREAM_H_
#define _SYSTEM_DATASTREAM_H_

#include <System/Common.h>
#include <System/IO/Streams/Stream.h>

namespace System
{
    namespace IO
    {
        /// <summary>
        /// A utility class to ease manipulation of streams
        /// </summary>
        class DataStream : public virtual Stream
        {
        protected:
            Stream* baseStream;
            char* buffer;

        public:
            DataStream(Stream* baseStream);

            u64 GetPosition();
            void SetPosition(u64 value);
            u64 GetLength();

            u32 Read(void* buffer, u32 count);
            void Write(void* buffer, u32 count);

            // Generic methods
            template<typename T> T Read()
            {
                baseStream->Read(buffer, sizeof(T));
                return *(T*)buffer;
            }
            template<typename T> T* Read(u32 count)
            {
                baseStream->Read(buffer, sizeof(T));
                return *(T*)buffer;
            }
            template<typename T> void Read(T* buffer)
            {
                baseStream->Read(buffer, sizeof(T));
            }
            template<typename T> void Write(const T& value)
            {
                baseStream->Write((char*)&value, sizeof(T));
            }

            // Specialized read methods
            byte ReadByte()
            {
                byte result;
                baseStream->Read(&result, sizeof(byte));
                return result;
            }
            u8 ReadU8()
            {
                u8 result;
                baseStream->Read(&result, sizeof(u8));
                return result;
            }
            u16 ReadU16()
            {
                u16 result;
                baseStream->Read(&result, sizeof(u16));
                return result;
            }
            u32 ReadU32()
            {
                u32 result;
                baseStream->Read(&result, sizeof(u32));
                return result;
            }
            u64 ReadU64()
            {
                u64 result;
                baseStream->Read(&result, sizeof(u64));
                return result;
            }
            s8 ReadS8()
            {
                s8 result;
                baseStream->Read(&result, sizeof(s8));
                return result;
            }
            s16 ReadS16()
            {
                s16 result;
                baseStream->Read(&result, sizeof(s16));
                return result;
            }
            s32 ReadS32()
            {
                s32 result;
                baseStream->Read(&result, sizeof(s32));
                return result;
            }
            s64 ReadS64()
            {
                s64 result;
                baseStream->Read(&result, sizeof(s64));
                return result;
            }
            float ReadFloat()
            {
                float result;
                baseStream->Read(&result, sizeof(float));
                return result;
            }
            double ReadDouble()
            {
                double result;
                baseStream->Read(&result, sizeof(double));
                return result;
            }
            char ReadChar()
            {
                char result;
                baseStream->Read(&result, sizeof(char));
                return result;
            }

            // Specialized write methods
            void Write(u8 value)
            {
                baseStream->Write(&value, sizeof(u8));
            }
            void Write(u16 value)
            {
                baseStream->Write(&value, sizeof(u16));
            }
            void Write(u32 value)
            {
                baseStream->Write(&value, sizeof(u32));
            }
            void Write(u64 value)
            {
                baseStream->Write(&value, sizeof(u64));
            }
            void Write(s8 value)
            {
                baseStream->Write(&value, sizeof(s8));
            }
            void Write(s16 value)
            {
                baseStream->Write(&value, sizeof(s16));
            }
            void Write(s32 value)
            {
                baseStream->Write(&value, sizeof(s32));
            }
            void Write(s64 value)
            {
                baseStream->Write(&value, sizeof(s64));
            }
            void Write(float value)
            {
                baseStream->Write(&value, sizeof(float));
            }
            void Write(double value)
            {
                baseStream->Write(&value, sizeof(double));
            }

            template<> string Read()
            {
                char* data = new char[0x1000];
                char* ptr = data;

                char c;
                do
                {
                    baseStream->Read(&c, 1);
                    *ptr++ = c;
                }
                while (c);

                string result(data);
                delete[] data;

                return result;
            }

            string ReadString(u32 length);
            void Write(string& value);
        };
    }
}

#endif
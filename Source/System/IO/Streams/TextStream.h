#ifndef _SYSTEM_TEXTSTREAM_H_
#define _SYSTEM_TEXTSTREAM_H_

#include <System/Common.h>
#include <System/IO/Streams/Stream.h>

namespace System
{
    namespace IO
    {
        class TextStream : public Stream
        {
        protected:
            Stream* baseStream;

        public:
            TextStream(Stream* baseStream);

            virtual u64 GetPosition();
            virtual u64 GetLength();

            virtual u32 Read(void* buffer, u32 count);
            virtual void Write(void* buffer, u32 count);
            virtual void Seek(u64 offset, SeekOrigin origin = SeekOrigin::Begin);

            virtual string Read(u32 length = 0);
            virtual string ReadLine();
            virtual string ReadAll();

            virtual void Write(const string& base)
            {
                baseStream->Write(base.Buffer, base.Length);
            }
            template<typename... Args> void Write(const string& base, Args... parameters)
            {
                Write(String::Format(base, parameters...));
            }
                
            void WriteLine()
            {
                Write("\r\n");
            }
            void WriteLine(const string& base)
            {
                Write(base);
                WriteLine();
            }
            template<typename... Args> void WriteLine(const string& base, Args... parameters)
            {
                WriteLine(String::Format(base, parameters...));
            }
        };
    }
}

#endif
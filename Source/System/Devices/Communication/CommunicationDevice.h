#ifndef _SYSTEM_COMMUNICATIONDEVICE_H_
#define _SYSTEM_COMMUNICATIONDEVICE_H_

#include <System/Common.h>
#include <System/Devices/Device.h>
#include <System/Structures/Collections/List.h>

namespace System
{
    namespace IO
    {
        class Stream;
    }

    namespace Devices
    {
        class CommunicationDevice : public Device
        {
        protected:
            List<IO::Stream*>* streams;

        public:
            CommunicationDevice()
            {
                streams = new List<IO::Stream*>();
            }

            _declspec(property(get = GetStreams)) List<IO::Stream*>* Streams;
            List<IO::Stream*>* GetStreams()
            {
                return streams;
            }
        };
    }
}

#endif
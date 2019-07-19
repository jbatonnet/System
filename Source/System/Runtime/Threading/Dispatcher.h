#ifndef _SYSTEM_DISPATCHER_H_
#define _SYSTEM_DISPATCHER_H_

#include <System/Common.h>
#include <System/Structures/Collections/List.h>
#include <System/Structures/Tuple.h>
#include <System/Runtime/Threading/Spinlock.h>

namespace System
{
    namespace Runtime
    {
        class Dispatcher
        {
			class BaseFrame
			{
			public:
				virtual void Process() = 0;
			};
            template<typename... Args> class Frame : public BaseFrame
            {
                Action<Args...> invokation;
                Tuple<Args...> parameters;

            public:
                Frame(const Action<Args...>& invokation, Args... parameters) : invokation(invokation), parameters(parameters...) { }

                void Process()
                {
                    Processor<Tuple<Args...>>::Process(invokation, parameters);
                }

            private:
                template<typename Tuple, typename... Params> struct Processor
                {
					__forceinline static void Process(const Action<Args...>& invokation, Tuple& remaining, Params... parameters)
                    {
                        Processor<decltype(remaining.Values), Params..., decltype(remaining.Value)>::Process(invokation, remaining.Values, parameters..., remaining.Value);
                    }
                };
                template<typename Arg, typename... Params> struct Processor<Tuple<Arg>, Params...>
                {
					__forceinline static void Process(const Action<Args...>& invokation, Tuple<Arg>& remaining, Params... parameters)
                    {
                        invokation(parameters..., remaining.Value);
                    }
                };
            };

        public:
            bool bufferIndex;
			List<BaseFrame*> frameBuffer1;
			List<BaseFrame*> frameBuffer2;

            Spinlock invokeLock;
            Spinlock flushLock;

            Dispatcher();

            // Methods
			template<typename... Args> void Invoke(const Action<Args...>& invokation, Args... parameters)
			{
				Frame<Args...>* frame = new Frame<Args...>(invokation, parameters...);
                Invoke(frame);
            }
            void Invoke(BaseFrame* frame);
            void Flush();

            // Static
            static Dispatcher* GetCurrent();
        };
    }
}

#endif
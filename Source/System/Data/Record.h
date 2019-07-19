#ifndef _SYSTEM_RECORD_H_
#define _SYSTEM_RECORD_H_

#include <System/Common.h>

namespace System
{
    namespace Data
    {
        class Record : public Object
        {
        public:
            virtual string GetString(u32 index)
            {
                return "VIRTUAL !!";
            }

            virtual bool GetBool(u32 index)
            {
                return false;// GetString(index).To<bool>();
            }
            virtual u8 GetU8(u32 index)
            {
                return 0;// GetString(index).To<u8>();
            }
            virtual u16 GetU16(u32 index)
            {
                return 0;// GetString(index).To<u16>();
            }
            virtual u32 GetU32(u32 index)
            {
                return 0;// GetString(index).To<u32>();
            }
            virtual u64 GetU64(u32 index)
            {
                return 0;// GetString(index).To<u64>();
            }
            virtual s8 GetS8(u32 index)
            {
                return 0;// GetString(index).To<s8>();
            }
            virtual s16 GetS16(u32 index)
            {
                return 0;// GetString(index).To<s16>();
            }
            virtual s32 GetS32(u32 index)
            {
                return 0;// GetString(index).To<s32>();
            }
            virtual s64 GetS64(u32 index)
            {
                return 0;// GetString(index).To<s64>();
            }
            virtual float GetFloat(u32 index)
            {
                return 0;// GetString(index).To<float>();
            }
            virtual double GetDouble(u32 index)
            {
                return 0;// GetString(index).To<double>();
            }

            template<typename T = string> T Get(u32 index)
            {
                return GetString(index).To<T>();
            }
            template<> string Get(u32 index)
            {
                return this->GetString(index);
            }

            template<> bool Get(u32 index)
            {
                return GetBool(index);
            }
            template<> u8 Get(u32 index)
            {
                return GetU8(index);
            }
            template<> u16 Get(u32 index)
            {
                return GetU16(index);
            }
            template<> u32 Get(u32 index)
            {
                return GetU32(index);
            }
            template<> u64 Get(u32 index)
            {
                return GetU64(index);
            }
            template<> s8 Get(u32 index)
            {
                return GetS8(index);
            }
            template<> s16 Get(u32 index)
            {
                return GetS16(index);
            }
            template<> s32 Get(u32 index)
            {
                return GetS32(index);
            }
            template<> s64 Get(u32 index)
            {
                return GetS64(index);
            }
            template<> float Get(u32 index)
            {
                return GetFloat(index);
            }
            template<> double Get(u32 index)
            {
                return GetDouble(index);
            }
        };
    }
}

#endif
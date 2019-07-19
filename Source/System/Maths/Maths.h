#ifndef _SYSTEM_MATHS_H_
#define _SYSTEM_MATHS_H_

#include <System/Common.h>

/*namespace System
{
    //namespace Maths
    {*/
        /// <summary>
        /// A utility class to provides some maths methods
        /// </summary>
        class Maths
        {
        public:
            /// <summary>
            /// Returns the maximum value between two
            /// </summary>
            template<typename T> static constexpr T Max(const T& left, const T& right)
            {
                return left > right ? left : right;
            }
            /// <summary>
            /// Returns the maximum value between three
            /// </summary>
            template<typename T> static constexpr T Max(const T& value1, const T& value2, const T& value3)
            {
                return Max(Max(value1, value2), value3);
            }
            /// <summary>
            /// Returns the minimum value between two
            /// </summary>
            template<typename T> static constexpr T Min(const T& left, const T& right)
            {
                return left < right ? left : right;
            }
            /// <summary>
            /// Returns the minimum value between three
            /// </summary>
            template<typename T> static constexpr T Min(const T& value1, const T& value2, const T& value3)
            {
                return Min(Min(value1, value2), value3);
            }
            /// <summary>
            /// Restricts a value between two bounds
            /// </summary>
            template<typename T> static constexpr T Clamp(const T& value, const T& minimum, const T& maximum)
            {
                return value < minimum ? minimum : value > maximum ? maximum : value;
            }
            /// <summary>
            /// Returns the absolute value
            /// </summary>
            template<typename T> static constexpr T Abs(const T& val)
            {
                return val < 0 ? -val : val;
            }
            /// <summary>
            /// Returns the sign of the specified value
            /// </summary>
            template<typename T> static constexpr T Sign(const T& val)
            {
                return val < 0 ? -1 : 1;
            }
            /// <summary>
            /// Swaps the two specified values
            /// </summary>
            template<typename T> static void Swap(T& value1, T& value2)
            {
                u8 bytes[sizeof(T)];

                Memory::Copy<T>(&value1, bytes);
                Memory::Copy<T>(&value2, &value1);
                Memory::Copy<T>(bytes, &value2);
            }
            /// <summary>
            /// Maps a value from a range to another
            /// </summary>
            template<typename T> static constexpr T Map(const T& value, const T& fromMin, const T& fromMax, const T& toMin, const T& toMax)
            {
                return toMin + (value - fromMin) * (toMax - toMin) / (fromMax - fromMin);
            }

            // Floating point
            static float Round(float value)
            {
                return (float)(s32)value;
            }
            static float Ceil(float value)
            {
                return (float)(s32)(value + 0.5f);
            }
            static float Floor(float value)
            {
                return (float)(s32)value;
            }
            static float Lerp(float start, float end, float value)
            {
                return start + (end - start) * value;
            }

            // Trigonometry
            static float Sqrt(float value);
            static float Pow(float value, float power);
            static float Sin(float value);
            static float Cos(float value);
            static float Tan(float value);
            static float Atan2(float x, float y);
        };
/*    }
}*/

#endif
#include <System/Maths/Maths.h>

float Maths::Sqrt(float value)
{
    return Pow(value, 0.5f);
}
float Maths::Pow(float value, float power)
{
    float control, temp, result;

    _asm
    {
        fstcw [control]
        or [control], 0xC00
        fldcw [control]
   
        fld [power]
        fld [value]
        fyl2x
   
        fist [temp]
   
        fild [temp]
        fsub
        f2xm1
        fld1
        fadd
        fild [temp]
        fxch
        fscale
       
        fst [result]
    }

    return result;
}
float Maths::Sin(float value)
{
    Exception::NotImplemented();
    return 0;
}
float Maths::Cos(float value)
{
    Exception::NotImplemented();
    return 0;
}
float Maths::Tan(float value)
{
    Exception::NotImplemented();
    return 0;
}
float Maths::Atan2(float x, float y)
{
    Exception::NotImplemented();
    return 0;
}
#include <System/System.h>
#include <Kernel/Runtime/Reflection/Reflection.h>

using namespace System::Runtime;

using namespace System;
using namespace Types;
using namespace Values;
using namespace std;
using namespace Colors;

void Reflection::Initialize()
{
    Type* flagType = Reflection::RegisterType<Flag>("Flag"); // Flag
    Type* stringType = Reflection::RegisterType<String>("String"); // String
        Method* stringLoadMethod = Reflection::RegisterAction<String&>(stringType, "Load");
        Reflection::RegisterConstructor<String>(stringType);
        Reflection::RegisterConstructor<String, s8*, u32, bool>(stringType);
        Reflection::RegisterConstructor<String, String&>(stringType);
        Reflection::RegisterConstructor<String, String&, String&>(stringType);
        Reflection::RegisterConstructor<String>(stringType);
        Reflection::RegisterConstructor<String, s8*>(stringType);
        Reflection::RegisterConstructor<String, s8*>(stringType);
        Reflection::RegisterConstructor<String, signed char, u32>(stringType);
        Reflection::RegisterConstructor<String, s32, u8, u8>(stringType);
        Reflection::RegisterConstructor<String, u32, String&>(stringType);
        Reflection::RegisterConstructor<String, u32, u8, u8>(stringType);
        Reflection::RegisterConstructor<String, s64, u8, u8>(stringType);
        Reflection::RegisterConstructor<String, u64, u8, u8>(stringType);
        Reflection::RegisterConstructor<String, bool>(stringType);
        Reflection::RegisterConstructor<String, float, u8, bool>(stringType);
        Reflection::RegisterConstructor<String, double>(stringType);
        Reflection::RegisterConstructor<String, void*>(stringType);
        Reflection::RegisterConstructor<String, void*, String&>(stringType);
        Reflection::RegisterConstructor<String, Object&>(stringType);
        Reflection::RegisterConstructor<String, Object&, String&>(stringType);
        Reflection::RegisterConstructor<String, Object*>(stringType);
        Reflection::RegisterConstructor<String, Object*, String&>(stringType);
        Reflection::RegisterConstructor<String, Month, String&>(stringType);
        Reflection::RegisterConstructor<String, Day, String&>(stringType);
        Method* stringGetLengthMethod = Reflection::RegisterFunction<u32>(stringType, "GetLength");
        Method* stringGetBufferMethod = Reflection::RegisterFunction<s8*>(stringType, "GetBuffer");
        Method* stringAfterMethod = Reflection::RegisterFunction<String, String&>(stringType, "After");
        Method* stringAfterLastMethod = Reflection::RegisterFunction<String, String&>(stringType, "AfterLast");
        Method* stringBeforeMethod = Reflection::RegisterFunction<String, String&>(stringType, "Before");
        Method* stringBeforeLastMethod = Reflection::RegisterFunction<String, String&>(stringType, "BeforeLast");
        Method* stringContainsMethod = Reflection::RegisterFunction<bool, String&>(stringType, "Contains");
        Method* stringIndexOfMethod = Reflection::RegisterFunction<s32, String&, u32>(stringType, "IndexOf");
        Method* stringIndexOfLastMethod = Reflection::RegisterFunction<s32, String&, u32>(stringType, "IndexOfLast");
        Method* stringAfterMethod = Reflection::RegisterFunction<String, signed char>(stringType, "After");
        Method* stringAfterLastMethod = Reflection::RegisterFunction<String, signed char>(stringType, "AfterLast");
        Method* stringBeforeMethod = Reflection::RegisterFunction<String, signed char>(stringType, "Before");
        Method* stringBeforeLastMethod = Reflection::RegisterFunction<String, signed char>(stringType, "BeforeLast");
        Method* stringContainsMethod = Reflection::RegisterFunction<bool, signed char>(stringType, "Contains");
        Method* stringIndexOfMethod = Reflection::RegisterFunction<s32, signed char, u32>(stringType, "IndexOf");
        Method* stringIndexOfLastMethod = Reflection::RegisterFunction<s32, signed char, u32>(stringType, "IndexOfLast");
        Method* stringReplaceMethod = Reflection::RegisterFunction<String, String&, String&, u32>(stringType, "Replace");
        Method* stringSubStringMethod = Reflection::RegisterFunction<String, s32>(stringType, "SubString");
        Method* stringSubStringMethod = Reflection::RegisterFunction<String, s32, s32>(stringType, "SubString");
        Method* stringToLowerMethod = Reflection::RegisterFunction<String>(stringType, "ToLower");
        Method* stringToUpperMethod = Reflection::RegisterFunction<String>(stringType, "ToUpper");
        Method* stringToCasingMethod = Reflection::RegisterFunction<String, Casing>(stringType, "ToCasing");
        Method* stringTrimMethod = Reflection::RegisterFunction<String, String&>(stringType, "Trim");
        Method* stringTrimLeftMethod = Reflection::RegisterFunction<String, String&>(stringType, "TrimLeft");
        Method* stringTrimRightMethod = Reflection::RegisterFunction<String, String&>(stringType, "TrimRight");
        Method* stringToBoolMethod = Reflection::RegisterFunction<bool>(stringType, "ToBool");
        Method* stringToUnsignedMethod = Reflection::RegisterFunction<u32, u32>(stringType, "ToUnsigned");
        Method* stringToSignedMethod = Reflection::RegisterFunction<s32, u32>(stringType, "ToSigned");
        Method* stringToMethod = Reflection::RegisterFunction<String, u32>(stringType, "To");
        Method* stringToMethod = Reflection::RegisterFunction<bool, u32>(stringType, "To");
        Method* stringToMethod = Reflection::RegisterFunction<u8, u32>(stringType, "To");
        Method* stringToMethod = Reflection::RegisterFunction<u16, u32>(stringType, "To");
        Method* stringToMethod = Reflection::RegisterFunction<u32, u32>(stringType, "To");
        Method* stringToMethod = Reflection::RegisterFunction<s8, u32>(stringType, "To");
        Method* stringToMethod = Reflection::RegisterFunction<s16, u32>(stringType, "To");
        Method* stringToMethod = Reflection::RegisterFunction<s32, u32>(stringType, "To");
        Method* stringFormatMethod = Reflection::RegisterFunction<String, String&>(stringType, "Format");
    Type* objectType = Reflection::RegisterType<Object>("Object"); // Object
        Method* objectIsMethod = Reflection::RegisterFunction<bool, type_info&>(objectType, "Is");
        Method* objectAsMethod = Reflection::RegisterFunction<void*, type_info&>(objectType, "As");
        Reflection::RegisterConstructor<Object>(objectType);
        Method* objectToStringMethod = Reflection::RegisterFunction<String>(objectType, "ToString");
        Method* objectHashMethod = Reflection::RegisterFunction<u32>(objectType, "Hash");
        Method* objectGetTypeMethod = Reflection::RegisterFunction<System::Runtime::Type*>(objectType, "GetType");
    Type* monthType = Reflection::RegisterType<Month>("Month"); // Month
    Type* dayType = Reflection::RegisterType<Day>("Day"); // Day
    Type* casingType = Reflection::RegisterType<Casing>("Casing"); // Casing
    Type* memoryTypeType = Reflection::RegisterType<MemoryType>("MemoryType"); // MemoryType
    Type* memoryType = Reflection::RegisterType<Memory>("Memory"); // Memory
        Method* memoryCopyMethod = Reflection::RegisterAction<void*, void*, u32>(memoryType, "Copy");
        Method* memoryClearMethod = Reflection::RegisterAction<void*, u32, u8>(memoryType, "Clear");
        Method* memoryCompareMethod = Reflection::RegisterFunction<bool, void*, void*, u32>(memoryType, "Compare");
        Method* memoryAllocateMethod = Reflection::RegisterFunction<void*, u32, s16>(memoryType, "Allocate");
        Method* memoryAllocateMethod = Reflection::RegisterFunction<void*, u32, MemoryType, s16>(memoryType, "Allocate");
        Method* memoryFreeMethod = Reflection::RegisterAction<void*>(memoryType, "Free");
    Type* unitType = Reflection::RegisterType<Unit>("Unit"); // Unit
        Reflection::RegisterConstructor<Unit>(unitType);
        Reflection::RegisterConstructor<Unit, float>(unitType);
        Reflection::RegisterConstructor<Unit, double>(unitType);
        Reflection::RegisterConstructor<Unit, bool>(unitType);
        Reflection::RegisterConstructor<Unit, s32>(unitType);
    Type* iLockableType = Reflection::RegisterType<ILockable>("ILockable"); // ILockable
        Method* iLockableLockMethod = Reflection::RegisterFunction<bool, u32>(iLockableType, "Lock");
        Method* iLockableUnlockMethod = Reflection::RegisterAction<>(iLockableType, "Unlock");
    Type* lockableLockerType = Reflection::RegisterType<LockableLocker>("LockableLocker"); // LockableLocker
        Reflection::RegisterConstructor<LockableLocker, ILockable*>(lockableLockerType);
        Reflection::RegisterConstructor<LockableLocker, ILockable&>(lockableLockerType);
        Reflection::RegisterConstructor<LockableLocker>(lockableLockerType);
    Type* exceptionType = Reflection::RegisterType<Exception>("Exception"); // Exception
        Reflection::RegisterConstructor<Exception>(exceptionType);
        Reflection::RegisterConstructor<Exception, String>(exceptionType);
        Method* exceptionGetMessageMethod = Reflection::RegisterFunction<String>(exceptionType, "GetMessage");
        Method* exceptionGetFramesMethod = Reflection::RegisterFunction<Collection*>(exceptionType, "GetFrames");
        Method* exceptionExtractFramesMethod = Reflection::RegisterAction<>(exceptionType, "ExtractFrames");
        Method* exceptionExtractFramesMethod = Reflection::RegisterAction<void*>(exceptionType, "ExtractFrames");
        Method* exceptionNotImplementedMethod = Reflection::RegisterAction<>(exceptionType, "NotImplemented");
        Method* exceptionAssertMethod = Reflection::RegisterAction<>(exceptionType, "Assert");
        Method* exceptionAssertMethod = Reflection::RegisterAction<bool>(exceptionType, "Assert");
        Method* exceptionAssertMethod = Reflection::RegisterAction<void*>(exceptionType, "Assert");
        Method* exceptionAssertMethod = Reflection::RegisterAction<s8*>(exceptionType, "Assert");
        Method* exceptionAssertMethod = Reflection::RegisterAction<String&>(exceptionType, "Assert");
        Method* exceptionAssertMethod = Reflection::RegisterAction<bool, s8*>(exceptionType, "Assert");
        Method* exceptionAssertMethod = Reflection::RegisterAction<void*, s8*>(exceptionType, "Assert");
    Type* assertExceptionType = Reflection::RegisterType<AssertException>("AssertException"); // AssertException
        Reflection::RegisterConstructor<AssertException>(assertExceptionType);
    Type* consoleStreamType = Reflection::RegisterType<ConsoleStream>("ConsoleStream"); // ConsoleStream
        Reflection::RegisterConstructor<ConsoleStream>(consoleStreamType);
        Method* consoleStreamGetLengthMethod = Reflection::RegisterFunction<u64>(consoleStreamType, "GetLength");
        Method* consoleStreamReadMethod = Reflection::RegisterFunction<u32, void*, u32>(consoleStreamType, "Read");
        Method* consoleStreamReadMethod = Reflection::RegisterFunction<u32, void*, u32, bool>(consoleStreamType, "Read");
        Method* consoleStreamWriteMethod = Reflection::RegisterAction<void*, u32>(consoleStreamType, "Write");
    Type* mathsType = Reflection::RegisterType<Maths>("Maths"); // Maths
        Method* mathsRoundMethod = Reflection::RegisterFunction<float, float>(mathsType, "Round");
        Method* mathsCeilMethod = Reflection::RegisterFunction<float, float>(mathsType, "Ceil");
        Method* mathsFloorMethod = Reflection::RegisterFunction<float, float>(mathsType, "Floor");
        Method* mathsLerpMethod = Reflection::RegisterFunction<float, float, float, float>(mathsType, "Lerp");
        Method* mathsSqrtMethod = Reflection::RegisterFunction<float, float>(mathsType, "Sqrt");
        Method* mathsPowMethod = Reflection::RegisterFunction<float, float, float>(mathsType, "Pow");
        Method* mathsSinMethod = Reflection::RegisterFunction<float, float>(mathsType, "Sin");
        Method* mathsCosMethod = Reflection::RegisterFunction<float, float>(mathsType, "Cos");
        Method* mathsTanMethod = Reflection::RegisterFunction<float, float>(mathsType, "Tan");
        Method* mathsAtan2Method = Reflection::RegisterFunction<float, float, float>(mathsType, "Atan2");
    Type* matrix3Type = Reflection::RegisterType<Matrix3>("Matrix3"); // Matrix3
        Reflection::RegisterConstructor<Matrix3>(matrix3Type);
        Reflection::RegisterConstructor<Matrix3, Matrix3&>(matrix3Type);
        Reflection::RegisterConstructor<Matrix3, float, float, float, float, float, float, float, float, float>(matrix3Type);
        Method* matrix3DeterminantMethod = Reflection::RegisterFunction<float>(matrix3Type, "Determinant");
        Method* matrix3TransposeMethod = Reflection::RegisterFunction<Matrix3&>(matrix3Type, "Transpose");
        Method* matrix3NormalizeMethod = Reflection::RegisterAction<>(matrix3Type, "Normalize");
        Method* matrix3NormalizeMethod = Reflection::RegisterFunction<Matrix3&, Matrix3&>(matrix3Type, "Normalize");
        Method* matrix3CreateRotationMethod = Reflection::RegisterFunction<Matrix3&, float, float, float>(matrix3Type, "CreateRotation");
        Method* matrix3CreateRotationMethod = Reflection::RegisterFunction<Matrix3&, float, float, float, float>(matrix3Type, "CreateRotation");
        Method* matrix3CreateRotationMethod = Reflection::RegisterFunction<Matrix3&, Vector3&, float>(matrix3Type, "CreateRotation");
        Method* matrix3CreateRotationMethod = Reflection::RegisterFunction<Matrix3&, Quaternion&>(matrix3Type, "CreateRotation");
        Method* matrix3CreateTranslationMethod = Reflection::RegisterFunction<Matrix3&, float, float, float>(matrix3Type, "CreateTranslation");
        Method* matrix3CreateTranslationMethod = Reflection::RegisterFunction<Matrix3&, Vector3&>(matrix3Type, "CreateTranslation");
        Method* matrix3CreateScaleMethod = Reflection::RegisterFunction<Matrix3&, float, float, float>(matrix3Type, "CreateScale");
        Method* matrix3CreateScaleMethod = Reflection::RegisterFunction<Matrix3&, Vector3&>(matrix3Type, "CreateScale");
    Type* point2Type = Reflection::RegisterType<Point2>("Point2"); // Point2
        Reflection::RegisterConstructor<Point2>(point2Type);
        Reflection::RegisterConstructor<Point2, s32>(point2Type);
        Reflection::RegisterConstructor<Point2, s32, s32>(point2Type);
    Type* point3Type = Reflection::RegisterType<Point3>("Point3"); // Point3
        Reflection::RegisterConstructor<Point3>(point3Type);
        Reflection::RegisterConstructor<Point3, s32>(point3Type);
        Reflection::RegisterConstructor<Point3, s32, s32, s32>(point3Type);
    Type* vector2Type = Reflection::RegisterType<Vector2>("Vector2"); // Vector2
        Reflection::RegisterConstructor<Vector2>(vector2Type);
        Reflection::RegisterConstructor<Vector2, Vector2&>(vector2Type);
        Reflection::RegisterConstructor<Vector2, float>(vector2Type);
        Reflection::RegisterConstructor<Vector2, float, float>(vector2Type);
        Reflection::RegisterConstructor<Vector2, Point2&>(vector2Type);
        Method* vector2LengthMethod = Reflection::RegisterFunction<float>(vector2Type, "Length");
        Method* vector2LerpMethod = Reflection::RegisterFunction<Vector2, Vector2&, Vector2&, float>(vector2Type, "Lerp");
        Method* vector2DotMethod = Reflection::RegisterFunction<float, Vector2&, Vector2&>(vector2Type, "Dot");
        Method* vector2NormalizeMethod = Reflection::RegisterFunction<Vector2, Vector2&>(vector2Type, "Normalize");
        Method* vector2AngleMethod = Reflection::RegisterFunction<float, Vector2&, Vector2&>(vector2Type, "Angle");
        Method* vector2DistanceMethod = Reflection::RegisterFunction<float, Vector2&, Vector2&>(vector2Type, "Distance");
    Type* vector3Type = Reflection::RegisterType<Vector3>("Vector3"); // Vector3
        Reflection::RegisterConstructor<Vector3>(vector3Type);
        Reflection::RegisterConstructor<Vector3, Vector3&>(vector3Type);
        Reflection::RegisterConstructor<Vector3, float>(vector3Type);
        Reflection::RegisterConstructor<Vector3, float, float, float>(vector3Type);
        Reflection::RegisterConstructor<Vector3, Vector2&, float>(vector3Type);
        Method* vector3LengthMethod = Reflection::RegisterFunction<float>(vector3Type, "Length");
        Method* vector3LerpMethod = Reflection::RegisterFunction<Vector3, Vector3&, Vector3&, float>(vector3Type, "Lerp");
        Method* vector3CrossMethod = Reflection::RegisterFunction<Vector3, Vector3&, Vector3&>(vector3Type, "Cross");
        Method* vector3DotMethod = Reflection::RegisterFunction<float, Vector3&, Vector3&>(vector3Type, "Dot");
        Method* vector3NormalizeMethod = Reflection::RegisterFunction<Vector3, Vector3&>(vector3Type, "Normalize");
        Method* vector3DistanceMethod = Reflection::RegisterFunction<float, Vector3&, Vector3&>(vector3Type, "Distance");
    Type* quaternionType = Reflection::RegisterType<Quaternion>("Quaternion"); // Quaternion
        Reflection::RegisterConstructor<Quaternion>(quaternionType);
        Reflection::RegisterConstructor<Quaternion, float, float, float, float>(quaternionType);
        Reflection::RegisterConstructor<Quaternion, Vector3, float>(quaternionType);
        Method* quaternionLerpMethod = Reflection::RegisterFunction<Quaternion&, Quaternion&, Quaternion&, float>(quaternionType, "Lerp");
    Type* unitGroupType = Reflection::RegisterType<UnitGroup>("UnitGroup"); // UnitGroup
        Type* unitGroupUnitsType = Reflection::RegisterType<UnitGroup::Units>(unitGroupCppType, "Units"); // UnitGroup::Units
    Type* unitsType = Reflection::RegisterType<Units>("Units"); // Units
        Type* unitsSizeType = Reflection::RegisterType<Units::Size>(unitsCppType, "Size"); // Units::Size
            Type* unitsSizeUnitsType = Reflection::RegisterType<Units::Size::Units>(unitsSizeCppType, "Units"); // Units::Size::Units
        Type* unitsTemperatureType = Reflection::RegisterType<Units::Temperature>(unitsCppType, "Temperature"); // Units::Temperature
            Type* unitsTemperatureUnitsType = Reflection::RegisterType<Units::Temperature::Units>(unitsTemperatureCppType, "Units"); // Units::Temperature::Units
        Type* unitsFileSizeType = Reflection::RegisterType<Units::FileSize>(unitsCppType, "FileSize"); // Units::FileSize
            Type* unitsFileSizeUnitsType = Reflection::RegisterType<Units::FileSize::Units>(unitsFileSizeCppType, "Units"); // Units::FileSize::Units
    Type* consoleColorType = Reflection::RegisterType<ConsoleColor>("ConsoleColor"); // ConsoleColor
    Type* consoleType = Reflection::RegisterType<Console>("Console"); // Console
        Method* consoleClearMethod = Reflection::RegisterAction<>(consoleType, "Clear");
        Method* consoleReadMethod = Reflection::RegisterFunction<signed char, bool>(consoleType, "Read");
        Method* consoleReadKeyMethod = Reflection::RegisterFunction<System::Devices::Buttons>(consoleType, "ReadKey");
        Method* consoleReadLineMethod = Reflection::RegisterFunction<String>(consoleType, "ReadLine");
        Method* consoleWriteMethod = Reflection::RegisterAction<String&>(consoleType, "Write");
        Method* consoleWriteLineMethod = Reflection::RegisterAction<>(consoleType, "WriteLine");
        Method* consoleWriteLineMethod = Reflection::RegisterAction<String&>(consoleType, "WriteLine");
    Type* logType = Reflection::RegisterType<Log>("Log"); // Log
        Method* logWriteLineMethod = Reflection::RegisterAction<System::IO::Stream*>(logType, "WriteLine");
        Method* logWriteLineMethod = Reflection::RegisterAction<System::IO::Stream*, String&>(logType, "WriteLine");
    Type* serialType = Reflection::RegisterType<Serial>("Serial"); // Serial
        Method* serialWriteMethod = Reflection::RegisterAction<String&>(serialType, "Write");
        Method* serialWriteLineMethod = Reflection::RegisterAction<>(serialType, "WriteLine");
        Method* serialWriteLineMethod = Reflection::RegisterAction<String&>(serialType, "WriteLine");
    Type* color24Type = Reflection::RegisterType<Color24>("Color24"); // Color24
        Reflection::RegisterConstructor<Color24>(color24Type);
        Reflection::RegisterConstructor<Color24, u32>(color24Type);
        Reflection::RegisterConstructor<Color24, u8, u8, u8>(color24Type);
    Type* color32Type = Reflection::RegisterType<Color32>("Color32"); // Color32
        Reflection::RegisterConstructor<Color32>(color32Type);
        Reflection::RegisterConstructor<Color32, u32>(color32Type);
        Reflection::RegisterConstructor<Color32, u8, u8, u8>(color32Type);
        Reflection::RegisterConstructor<Color32, u8, u8, u8, u8>(color32Type);
        Reflection::RegisterConstructor<Color32, Color24, u8>(color32Type);
    Type* matrix4Type = Reflection::RegisterType<Matrix4>("Matrix4"); // Matrix4
        Reflection::RegisterConstructor<Matrix4>(matrix4Type);
        Reflection::RegisterConstructor<Matrix4, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float>(matrix4Type);
        Reflection::RegisterConstructor<Matrix4, Matrix3&>(matrix4Type);
        Method* matrix4TransposeMethod = Reflection::RegisterFunction<Matrix4&>(matrix4Type, "Transpose");
        Method* matrix4DeterminantMethod = Reflection::RegisterFunction<float>(matrix4Type, "Determinant");
        Method* matrix4CreateTransformationMethod = Reflection::RegisterFunction<Matrix4&, Vector3&, Matrix3&, Vector3&>(matrix4Type, "CreateTransformation");
        Method* matrix4CreateViewMethod = Reflection::RegisterFunction<Matrix4&, Vector3&, Vector3&, Vector3&>(matrix4Type, "CreateView");
        Method* matrix4CreateProjectionMethod = Reflection::RegisterFunction<Matrix4&, float, float, float, float>(matrix4Type, "CreateProjection");
    Type* applicationType = Reflection::RegisterType<Application>("Application"); // Application
        Method* applicationStartMethod = Reflection::RegisterAction<String>(applicationType, "Start");
    Type* gameType = Reflection::RegisterType<Game>("Game"); // Game
        Method* gameInitializeMethod = Reflection::RegisterAction<>(gameType, "Initialize");
        Method* gameLoadMethod = Reflection::RegisterAction<>(gameType, "Load");
        Method* gameUpdateMethod = Reflection::RegisterAction<u64, u64>(gameType, "Update");
        Method* gameDrawMethod = Reflection::RegisterAction<u64, u64>(gameType, "Draw");
        Method* gameUnloadMethod = Reflection::RegisterAction<>(gameType, "Unload");
        Method* gameStartMethod = Reflection::RegisterAction<String>(gameType, "Start");
    Type* timerType = Reflection::RegisterType<Timer>("Timer"); // Timer
        Method* timerTimeMethod = Reflection::RegisterFunction<u64>(timerType, "Time");
        Method* timerSleepMethod = Reflection::RegisterAction<u64>(timerType, "Sleep");
    Type* randomStreamType = Reflection::RegisterType<RandomStream>("RandomStream"); // RandomStream
        Reflection::RegisterConstructor<RandomStream, u32>(randomStreamType);
        Method* randomStreamReadMethod = Reflection::RegisterFunction<u32, void*, u32>(randomStreamType, "Read");
        Method* randomStreamWriteMethod = Reflection::RegisterAction<void*, u32>(randomStreamType, "Write");
    Type* randomType = Reflection::RegisterType<Random>("Random"); // Random
        Reflection::RegisterConstructor<Random>(randomType);
        Reflection::RegisterConstructor<Random, u32>(randomType);
    Type* timeSpanType = Reflection::RegisterType<TimeSpan>("TimeSpan"); // TimeSpan
        Reflection::RegisterConstructor<TimeSpan, s32>(timeSpanType);
        Reflection::RegisterConstructor<TimeSpan, u16, u16, u16, u16, u16>(timeSpanType);
        Method* timeSpanGetDaysMethod = Reflection::RegisterFunction<u16>(timeSpanType, "GetDays");
        Method* timeSpanGetHoursMethod = Reflection::RegisterFunction<u8>(timeSpanType, "GetHours");
        Method* timeSpanGetMinutesMethod = Reflection::RegisterFunction<u8>(timeSpanType, "GetMinutes");
        Method* timeSpanGetSecondsMethod = Reflection::RegisterFunction<u8>(timeSpanType, "GetSeconds");
        Method* timeSpanGetMillisecondsMethod = Reflection::RegisterFunction<u16>(timeSpanType, "GetMilliseconds");
        Method* timeSpanToStringMethod = Reflection::RegisterFunction<String>(timeSpanType, "ToString");
    Type* dateTimeType = Reflection::RegisterType<DateTime>("DateTime"); // DateTime
        Reflection::RegisterConstructor<DateTime, u8, u8, u8, u16>(dateTimeType);
        Reflection::RegisterConstructor<DateTime, u16, Month, u8>(dateTimeType);
        Reflection::RegisterConstructor<DateTime, u16, Month, u8, u8, u8, u8, u16>(dateTimeType);
        Method* dateTimeGetYearMethod = Reflection::RegisterFunction<u16>(dateTimeType, "GetYear");
        Method* dateTimeSetYearMethod = Reflection::RegisterAction<u16>(dateTimeType, "SetYear");
        Method* dateTimeGetMonthMethod = Reflection::RegisterFunction<Month>(dateTimeType, "GetMonth");
        Method* dateTimeSetMonthMethod = Reflection::RegisterAction<Month>(dateTimeType, "SetMonth");
        Method* dateTimeGetDayMethod = Reflection::RegisterFunction<u8>(dateTimeType, "GetDay");
        Method* dateTimeSetDayMethod = Reflection::RegisterAction<u8>(dateTimeType, "SetDay");
        Method* dateTimeGetHoursMethod = Reflection::RegisterFunction<u8>(dateTimeType, "GetHours");
        Method* dateTimeSetHoursMethod = Reflection::RegisterAction<u8>(dateTimeType, "SetHours");
        Method* dateTimeGetMinutesMethod = Reflection::RegisterFunction<u8>(dateTimeType, "GetMinutes");
        Method* dateTimeSetMinutesMethod = Reflection::RegisterAction<u8>(dateTimeType, "SetMinutes");
        Method* dateTimeGetSecondsMethod = Reflection::RegisterFunction<u8>(dateTimeType, "GetSeconds");
        Method* dateTimeSetSecondsMethod = Reflection::RegisterAction<u8>(dateTimeType, "SetSeconds");
        Method* dateTimeGetMillisecondsMethod = Reflection::RegisterFunction<u16>(dateTimeType, "GetMilliseconds");
        Method* dateTimeSetMillisecondsMethod = Reflection::RegisterAction<u16>(dateTimeType, "SetMilliseconds");
        Method* dateTimeGetDayOfWeekMethod = Reflection::RegisterFunction<Day>(dateTimeType, "GetDayOfWeek");
        Method* dateTimeGetDateMethod = Reflection::RegisterFunction<DateTime>(dateTimeType, "GetDate");
        Method* dateTimeGetTimeMethod = Reflection::RegisterFunction<DateTime>(dateTimeType, "GetTime");
        Method* dateTimeToStringMethod = Reflection::RegisterFunction<String>(dateTimeType, "ToString");
        Method* dateTimeToLongDateMethod = Reflection::RegisterFunction<String>(dateTimeType, "ToLongDate");
}

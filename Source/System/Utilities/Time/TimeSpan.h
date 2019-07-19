#ifndef _SYSTEM_TIMESPAN_H_
#define _SYSTEM_TIMESPAN_H_

#include <System/Common.h>
#include <System/Utilities/Time/Enums.h>

/// <summary>
/// Represents a quanta of time
/// </summary>
class TimeSpan : public Object
{
public:
    bool sign;
    u32 days;
    u32 milliseconds;

public:
    /// <summary>
    /// Constructs a new TimeSpan from the specified milliseconds
    /// </summary>
    /// <param name="milliseconds">The milliseconds of this TimeSpan</param>
    TimeSpan(s32 milliseconds)
    {
        sign = milliseconds >= 0;
        this->milliseconds = sign ? milliseconds : -milliseconds;

        days = this->milliseconds / 86400000;
        this->milliseconds %= 86400000;
    }

    /// <summary>
    /// Constructs a new TimeSpan from the specified DateTime
    /// </summary>
    /// <param name="dateTime">The DateTime used to build this TimeSpan</param>
    /*TimeSpan(const DateTime& dateTime)
    {
        sign = true;
        days = (365 * dateTime.Year + dateTime.Year / 4 - dateTime.Year / 100 + dateTime.Year / 400) + 
               (30 * (u8)dateTime.Month + ((u8)dateTime.Month + 1 + ((u8)dateTime.Month / 7)) / 2 - ((u8)dateTime.Month > 1) * 2) +
               (dateTime.Day - 1);
        milliseconds = dateTime.Hours * 3600000 +
                       dateTime.Minutes * 60000 +
                       dateTime.Seconds * 1000;
    }*/

    /// <summary>
    /// Constructs a new DateTime from the specified hours, minutes, seconds and milliseconds
    /// </summary>
    /// <param name="days">The days of this TimeSpan</param>
    /// <param name="hours">The hours of this TimeSpan</param>
    /// <param name="minutes">The minutes of this TimeSpan</param>
    /// <param name="seconds">The seconds of this TimeSpan</param>
    /// <param name="milliseconds">The milliseconds of this TimeSpan</param>
    TimeSpan(u16 days, u16 hours, u16 minutes, u16 seconds, u16 milliseconds = 0)
    {
        this->milliseconds = milliseconds;
        this->milliseconds += seconds * 1000;
        this->milliseconds += minutes * 60000;
        this->milliseconds += hours * 3600000;

        this->days = days + this->milliseconds / 86400000;
        this->milliseconds %= 86400000;
    }

    /// <summary>
    /// Gets the days of this TimeSpan
    /// </summary>
    _declspec(property(get = GetDays)) u16 Days;
    u16 GetDays() const { return (u16)days; }

    /// <summary>
    /// Gets the hours of this TimeSpan
    /// </summary>
    _declspec(property(get = GetHours)) u8 Hours;
    u8 GetHours() const { return (milliseconds / 3600000) % 24; }

    /// <summary>
    /// Gets the minutes of this TimeSpan
    /// </summary>
    _declspec(property(get = GetMinutes)) u8 Minutes;
    u8 GetMinutes() const { return (milliseconds / 60000) % 60; }

    /// <summary>
    /// Gets the seconds of this TimeSpan
    /// </summary>
    _declspec(property(get = GetSeconds)) u8 Seconds;
    u8 GetSeconds() const { return (milliseconds / 1000) % 60; }

    /// <summary>
    /// Gets the milliseconds of this TimeSpan
    /// </summary>
    _declspec(property(get = GetMilliseconds)) u16 Milliseconds;
    u16 GetMilliseconds() const { return milliseconds % 1000; }

    /// <summary>
    /// Returns a string representation of this TimeSpan
    /// </summary>
    string ToString()
    {
        u16 days = Days;

        if (!days)
            return string::Format("{0}:{1:d2}'{2:d2}\"{3:d3}", Hours, Minutes, Seconds, Milliseconds);
        else
            return string::Format("{0}d {1}:{2:d2}'{3:d2}\"{4:d3}", days, Hours, Minutes, Seconds, Milliseconds);
    }

    TimeSpan operator-(const TimeSpan& other)
    {
        TimeSpan result(0);

        s32 daysDiff = (s32)days - (s32)other.days;
        s32 millisecondsDiff = (s32)milliseconds - (s32)other.milliseconds;

        //result.sign = days >= other.days 

        return result;
    }
};

#endif
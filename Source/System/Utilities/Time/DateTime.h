#ifndef _SYSTEM_DATETIME_H_
#define _SYSTEM_DATETIME_H_

#include <System/Common.h>
#include <System/Utilities/Time/Enums.h>
#include <System/Utilities/Time/TimeSpan.h>

/// <summary>
/// Represents a date and/or a time
/// </summary>
class DateTime : public Object
{
private:
    union
    {
        u64 value;
        struct
        {
            union
            {
                u32 date;
                struct
                {
                    u16 year : 12;
                    Month month : 4;
                    u8 day   : 5;
                };
            };
            union
            {
                u32 time;
                struct
                {
                    u8 hours         : 5;
                    u8 minutes       : 6;
                    u8 seconds       : 6;
                    u16 milliseconds : 10;
                };
            };
        };
    };

public:
    /// <summary>
    /// Constructs a new DateTime from the specified hours, minutes and seconds
    /// </summary>
    /// <param name="hours">The hours of this DateTime</param>
    /// <param name="minutes">The minutes of this DateTime</param>
    /// <param name="seconds">The seconds of this DateTime</param>
    DateTime(u8 hours, u8 minutes, u8 seconds, u16 milliseconds = 0) : date(0), hours(hours), minutes(minutes), seconds(seconds), milliseconds(milliseconds) { }
    
    /// <summary>
    /// Constructs a new DateTime from the specified year, month and day
    /// </summary>
    /// <param name="year">The year of this DateTime</param>
    /// <param name="month">The month of this DateTime</param>
    /// <param name="day">The day of this DateTime</param>
    DateTime(u16 year, Month month, u8 day) : time(0), year(year), month(month), day(day - 1) { }
    
    /// <summary>
    /// Constructs a new DateTime from the specified components
    /// </summary>
    /// <param name="year">The year of this DateTime</param>
    /// <param name="month">The month of this DateTime</param>
    /// <param name="day">The day of this DateTime</param>
    /// <param name="hours">The hours of this DateTime</param>
    /// <param name="minutes">The minutes of this DateTime</param>
    /// <param name="seconds">The seconds of this DateTime</param>
    DateTime(u16 year, Month month, u8 day, u8 hours, u8 minutes, u8 seconds, u16 milliseconds = 0) : year(year), month(month), day(day - 1), hours(hours), minutes(minutes), seconds(seconds), milliseconds(milliseconds) { }

    /// <summary>
    /// Gets or sets the year of this DateTime
    /// </summary>
    _declspec(property(get = GetYear, put = SetYear)) u16 Year;
    u16 GetYear() const { return year; }
    void SetYear(u16 value) { year = value; }

    /// <summary>
    /// Gets or sets the month of this DateTime
    /// </summary>
    _declspec(property(get = GetMonth, put = SetMonth)) Month Month;
    ::Month GetMonth() const { return month; }
    void SetMonth(::Month value) { month = value; }

    /// <summary>
    /// Gets or sets the day of this DateTime
    /// </summary>
    _declspec(property(get = GetDay, put = SetDay)) u8 Day;
    u8 GetDay() const { return (u8)(day + 1); }
    void SetDay(u8 value) { day = value - 1; }

    /// <summary>
    /// Gets or sets the hours of this DateTime
    /// </summary>
    _declspec(property(get = GetHours, put = SetHours)) u8 Hours;
    u8 GetHours() const { return hours; }
    void SetHours(u8 value) { hours = value; }

    /// <summary>
    /// Gets or sets the minutes of this DateTime
    /// </summary>
    _declspec(property(get = GetMinutes, put = SetMinutes)) u8 Minutes;
    u8 GetMinutes() const { return minutes; }
    void SetMinutes(u8 value) { minutes = value; }

    /// <summary>
    /// Gets or sets the seconds of this DateTime
    /// </summary>
    _declspec(property(get = GetSeconds, put = SetSeconds)) u8 Seconds;
    u8 GetSeconds() const { return seconds; }
    void SetSeconds(u8 value) { seconds = value; }

    /// <summary>
    /// Gets or sets the milliseconds of this DateTime
    /// </summary>
    _declspec(property(get = GetMilliseconds, put = SetMilliseconds)) u16 Milliseconds;
    u16 GetMilliseconds() const { return milliseconds; }
    void SetMilliseconds(u16 value) { milliseconds = value; }

    /// <summary>
    /// Gets the day of week of this DateTime
    /// </summary>
    _declspec(property(get = GetDayOfWeek)) ::Day DayOfWeek;
    ::Day GetDayOfWeek() const { return (::Day)((((23 * ((u8)month + 1)) / 9) + day + 4 + year + (year / 4) - (year / 100) + (year / 400) - (((u8)month >= 2) * 2)) % 7); }

    /// <summary>
    /// Gets the date part of this DateTime
    /// </summary>
    _declspec(property(get = GetDate)) DateTime Date;
    DateTime GetDate() const { return DateTime(year, month, (u8)(day + 1)); }

    /// <summary>
    /// Gets the time part of this DateTime
    /// </summary>
    _declspec(property(get = GetTime)) DateTime Time;
    DateTime GetTime() const { return DateTime(hours, minutes, seconds); }

    /// <summary>
    /// Returns a string representation of this DateTime
    /// </summary>
    /// <returns>The string representation</returns>
    string ToString()
    {
        if (!time)
            return string::Format(DateFormat, year, year % 100, (u8)month + 1, day + 1);
        else if (!date)
            return string::Format(TimeFormat, hours, hours % 12, hours > 12 ? "PM" : "AM", minutes, seconds);
        else
            return string::Format(DateTimeFormat, year, year % 100, (u8)month + 1, day + 1, hours, hours % 12, hours > 12 ? "PM" : "AM", minutes, seconds);
    }

    string ToLongDate()
    {
        u8 dayUnit = (u8)(day % 10);
        u8 dayMultiplier = (u8)(day / 10);
        char* daySuffix = dayMultiplier == 1 ? "th" : dayUnit == 0 ? "st" : dayUnit == 1 ? "nd" : dayUnit == 2 ? "rd" : "th";

        return string::Format(LongDateFormat, year, year % 100, (u8)month + 1, month, day + 1, DayOfWeek, daySuffix);
    }

    bool operator>(const DateTime& other) const
    {
        return value > other.value;
    }
    bool operator<(const DateTime& other) const
    {
        return value < other.value;
    }
    bool operator==(const DateTime& other) const
    {
        return value == other.value;
    }
    TimeSpan operator-(const DateTime& other) const
    {
        return TimeSpan(0) - TimeSpan(0);
    }
    DateTime operator+(const TimeSpan& other) const
    {
        return DateTime(0, 0, 0);
    }

    // Formats
    static string DateFormat, TimeFormat, DateTimeFormat,
                  LongDateFormat, LongTimeFormat, LongDateTimeFormat;

    static DateTime Now;
};

#endif
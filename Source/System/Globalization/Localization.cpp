#include <System/Base/String.h>
#include <System/Utilities/Time/DateTime.h>

#define FR

#ifdef FR
    #define French(x) x
#else
    #define French(x)
#endif

#ifdef EN
    #define English(x) x
#else
    #define English(x)
#endif

#define case(value, text, format) case value: Load(String(String(text), format)); return

/*
             Example  Date  Time  DateTime  LongDate  LongTime  LongDateTime
    Year     2014     0           0         0                   0           
    Year     14       1           1         1                   1           
    Month    12       2           2         2                   2           
    Month    June                           3                   3           
    Day      13       3           3         4                   4           
    Day      Monday                         5                   5           
    Day      th                             6                   6           
    Hour/24  23             0     4                   0         7           
    Hour/12  11             1     5                   1         8           
    Hour     PM             2     6                   2         9           
    Minute   54             3     7                   3         10          
    Second   36             4     8                   4         11          
*/

String DateTime::DateFormat =         English("{2:d2}/{3:d2}/{0:d4}")                       French("{3:d2}/{2:d2}/{0:d4}"),
       DateTime::TimeFormat =         English("{1}:{3:d2}:{4:d2} {2}")                      French("{0}:{3:d2}:{4:d2}"),
       DateTime::DateTimeFormat =     English("{2:d2}/{3:d2}/{0:d4} {5}:{7:d2}:{8:d2} {6}") French("{3:d2}/{2:d2}/{0:d4} {4}:{7:d2}:{8:d2}"),
       DateTime::LongDateFormat =     English("{5:w} {4}{6} {3:l} {0}")                     French("{5:w} {4} {3:l} {0}"),
       DateTime::LongTimeFormat =     English("")                                           French(""),
       DateTime::LongDateTimeFormat = English("")                                           French("");

String::String(Month month, const String& format)
{
    switch (month)
    {
        case( Month::January,   English("January")   French("Janvier")   , format);
        case( Month::February,  English("February")  French("Février")   , format);
        case( Month::March,     English("March")     French("Mars")      , format);
        case( Month::April,     English("April")     French("Avril")     , format);
        case( Month::May,       English("May")       French("Mai")       , format);
        case( Month::June,      English("June")      French("Juin")      , format);
        case( Month::July,      English("July")      French("Juillet")   , format);
        case( Month::August,    English("August")    French("Août")      , format);
        case( Month::September, English("September") French("Septembre") , format);
        case( Month::October,   English("October")   French("Octobre")   , format);
        case( Month::November,  English("November")  French("Novembre")  , format);
        case( Month::December,  English("December")  French("Décembre")  , format);
    }
}

String::String(Day day, const String& format)
{
    switch (day)
    {
        case( Day::Monday,    English("Monday")    French("Lundi")    , format);
        case( Day::Tuesday,   English("Tuesday")   French("Mardi")    , format);
        case( Day::Wednesday, English("Wednesday") French("Mercredi") , format);
        case( Day::Thursday,  English("Thursday")  French("Jeudi")    , format);
        case( Day::Friday,    English("Friday")    French("Vendredi") , format);
        case( Day::Saturday,  English("Saturday")  French("Samedi")   , format);
        case( Day::Sunday,    English("Sunday")    French("Dimanche") , format);
    }
}
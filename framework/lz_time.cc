#include <lz_time.h>
#include <ctime>

namespace LZ {

std::ostream& operator<< (std::ostream& stream, const Time&) 
{
    time_t t = time(0);
    struct tm* now = localtime(&t);

    int year = now->tm_year + 1900;
    int mon = now->tm_mon + 1;
    int day = now->tm_mday;
    int hour = now->tm_hour;
    int min = now->tm_min;
    int sec = now->tm_sec;

    stream << year << '/'
	   << mon << '/'
	   << day << '-' 
	   << hour << ':' 
	   << min << ':' 
	   << sec;  
    return stream;
}

int Time::getYear() const
{
    time_t t = time(NULL);
    struct tm* now = localtime(&t);
    return now->tm_year + 1900;
}

int Time::getMon() const
{
    time_t t = time(NULL);
    struct tm* now = localtime(&t);
    return now->tm_mon + 1;
}

int Time::getDay() const
{
    time_t t = time(NULL);
    struct tm* now = localtime(&t);
    return now->tm_mday;
}

int Time::getHour() const
{
    time_t t = time(NULL);
    struct tm* now = localtime(&t);
    return now->tm_hour;
}

int Time::getMin() const
{
    time_t t = time(NULL);
    struct tm* now = localtime(&t);
    return now->tm_min;
}

int Time::getSec() const
{
    time_t t = time(NULL);
    struct tm* now = localtime(&t);
    return now->tm_sec;
}

} // close namespace

#include <log.h>
#include <ctime>
#include <sstream>

const char* Log::s_logPath = "/var/log/lzserver/log";

Log::Log()
{
    time_t t = time(0);
    struct tm* now = localtime(&t);

    int year = now->tm_year + 1900;
    int mon = now->tm_mon + 1;
    int day = now->tm_mday;

    std::stringstream stream;
    stream << s_logPath << '.' 
	   << year << '-'
	   << mon << '-'
	   << day; 

    d_file.open(stream.str().c_str(), std::ifstream::out);
    d_file << "ssdf\n";
}

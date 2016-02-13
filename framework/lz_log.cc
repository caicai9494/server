#include <lz_log.h>
#include <lz_time.h>

#include <ctime>
#include <sstream>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

namespace LZ {

const char* Log::s_logPath = "tool/log/lzserver/";

Log::Log()
{
    // TODO:
    // to use "lz_time"
    // Need to decide how to write the log
    time_t t = time(0);
    struct tm* now = localtime(&t);

    int year = now->tm_year + 1900;
    int mon = now->tm_mon + 1;
    int day = now->tm_mday;
    int hour = now->tm_hour;
    int min = now->tm_min;
    int sec = now->tm_sec;

    std::stringstream stream;
    stream << s_logPath << "log." 
	   << year << '-'
	   << mon << '-'
	   << day << '-' 
	   << hour << ':' 
	   << min << ':' 
	   << sec;  

    if (mkdir(Log::s_logPath, S_IRWXU | S_IRWXG | S_IRWXO) != 0) {
	if (EEXIST != errno) {
	    perror("mkdir");
	    exit(1);
	} 
    }

    d_file.open(stream.str().c_str(), std::ifstream::out);
}


} // close namespace


#ifndef LOG_H 
#define LOG_H

#include <iostream>
#include <fstream>
#include <mutex>
#include <singleton.h>

class Log {

  public:

    Log();

    ~Log()
    {
    }

    template<typename T>
    void writeError(const T& obj);

    template<typename T>
    void writeInfo(const T& obj);

  private:
    static const char* s_logPath;
    std::ofstream d_file;
    std::mutex d_mutex;
};



#define sLog singleton<Log>::instance()



#endif

#ifndef LZ_LOG_H 
#define LZ_LOG_H

#include <iostream>
#include <fstream>
#include <mutex>
#include <lz_singleton.h>
#include <lz_time.h>

namespace LZ {

class Log {

  public:

    Log();

    ~Log() {}

    template<typename T>
    void writeError(const T& obj)
    {
	std::lock_guard<std::mutex> lck(d_mutex);
	d_file << Time() << "-Error: " << obj << '\n';
    }

    template<typename T>
    void writeInfo(const T& obj)
    {
	std::lock_guard<std::mutex> lck(d_mutex);
	d_file << Time() << "-Info: " << obj << '\n';
    }

  private:
    static const char* s_logPath;
    std::ofstream d_file;
    std::mutex d_mutex;
};


} // close namespace

#define sLog ::LZ::Singleton<LZ::Log>::instance()
#define LOG_ERROR(error) sLog.writeError(error)
#define LOG_INFO(info) sLog.writeInfo(info)

#endif

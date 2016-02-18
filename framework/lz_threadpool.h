#ifndef LZ_THREADPOOL_H 
#define LZ_THREADPOOL_H

#include <algorithm>
#include <cassert>
#include <condition_variable>
#include <deque>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>
#include <string>

#include <lz_runnable.h>
#include <lz_singleton.h>

namespace LZ {

template <size_t SIZE = 16>
class Threadpool {
   
  // This class defines a non-resizeable Threadpool object

  public:

    enum class State { STARTED, STOPPED };
    enum class ErrorCode { SUCCESS, ALREADY_STARTED, ALREADY_DESTROYED, NOT_STARTED };

    Threadpool(): d_size(SIZE), d_state(State::STOPPED)
    {
	d_threads.reserve(d_size);
    }	

    ~Threadpool() 
    {
	destroy();
    }

    ErrorCode start();
        // Start all threads.
	// Return 'ErrorCode' correspondingly

    ErrorCode destroy();
        // Shut down all threads.

    void addTask(Runnable* tsk);
        // Not responsible for memory management 
	// of 'tsk'. Undefined behavior if 'tsk' is 'nullptr'
	
    size_t size() const { return d_tasks.size(); }
        // Return number of tasks
    std::string errorCodeToString(ErrorCode code)
    {
	switch (code) {
	    case ErrorCode::SUCCESS:
		return "Success.";
	    case ErrorCode::ALREADY_STARTED:
		return "Threadpool has been started already.";
	    case ErrorCode::ALREADY_DESTROYED:
		return "Threadpool has been destroyed already.";
	    case ErrorCode::NOT_STARTED:
		return "Threadpool has not been started yet.";
	    default:
		return "UNKNOWN ERRORCODE";
	}
    }
	
  private:
    std::vector<std::thread> d_threads;
    std::deque<Runnable*> d_tasks;
    std::condition_variable d_cond;
    std::mutex d_mtx;
    const size_t d_size;
    State d_state;

    Threadpool(const Threadpool&) = delete;
    Threadpool& operator=(const Threadpool&) = delete;

    void execute();
        // Actual function that each thread runs
};

} // close namespace

#define sThreadpool ::LZ::Singleton<LZ::Threadpool<>>::instance()
    // Use default thread pool size of 16

#include <lz_threadpool.tcc>

#endif

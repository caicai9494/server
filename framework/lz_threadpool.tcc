#ifndef LZ_THREADPOOL_TCC 
#define LZ_THREADPOOL_TCC

// This file is for internal implementation only.
// Anyone who uses this class ought to include
// <lz_threadpool.h>

#include <lz_threadpool.h>
#include <lz_log.h>

#include <chrono>
#include <iostream>

namespace LZ {

template <size_t SIZE>
void Threadpool<SIZE>::addTask(Runnable* tsk)
{
    assert(tsk != nullptr);
    {
	std::lock_guard<std::mutex> lck(d_mtx);
	d_tasks.push_back(tsk);
    }
    d_cond.notify_one();
}

template <size_t SIZE>
typename Threadpool<SIZE>::ErrorCode Threadpool<SIZE>::start()
{
    std::lock_guard<std::mutex> lck(d_mtx);

    if (d_state == State::STARTED) {
	return ErrorCode::ALREADY_STARTED;
    }
    d_state = State::STARTED;
    // change the state of the pool

    for (size_t i = 0; i != d_size; ++i) {
	d_threads.push_back(std::thread([this]{
            this->execute();
	}));
    }
    return ErrorCode::SUCCESS;
}

template <size_t SIZE>
void Threadpool<SIZE>::execute()
{
    // exception cannot escape from this function
    while (true) {

	std::unique_lock<std::mutex> lck(d_mtx);
	d_cond.wait(lck, [this] { 
		//std::cout << std::this_thread::get_id() << ": wait for task\n";
	    return !d_tasks.empty() || d_state == State::STOPPED; 
	});	

	// After waked up, if the pool has been destroyed 
	// (i.e, 'destroy' has been called), then break the loop. 
	if (d_state == State::STOPPED) {
		//std::cout << std::this_thread::get_id() << ": break while loop\n";
	    break;
	}

	Runnable* toRun = d_tasks.front();
	d_tasks.pop_front();

	lck.unlock();

	try {
	    toRun->run();
	}
	catch (std::exception& ex) {
	    std::cerr << ex.what() << '\n';
	    sLog.writeError(ex.what());
	}
	catch (...) {
	    std::string err = "Unknown exception from threads.\n";
	    std::cerr << err << '\n';
	    sLog.writeError(err);
	}
    }
}

template <size_t SIZE>
void Threadpool<SIZE>::barrier(unsigned sec)
{
    std::this_thread::sleep_for(std::chrono::seconds(sec));
}

template <size_t SIZE>
typename Threadpool<SIZE>::ErrorCode Threadpool<SIZE>::destroy()
{
    std::unique_lock<std::mutex> lck(d_mtx);
    if (d_state == State::STOPPED) {
	return ErrorCode::ALREADY_DESTROYED; 
	//TODO: redesign error reporting
    }
    d_state = State::STOPPED;
    // change the state of the pool
    
    lck.unlock();
    d_cond.notify_all();

    std::for_each(d_threads.begin(), d_threads.end(), [this](std::thread& th){
	//d_tasks.push_back(nullptr);
	th.join();
    });

    return ErrorCode::SUCCESS;
}

} // close namespace

#endif



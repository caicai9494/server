#include <lz_threadpool.h> 
#include <algorithm>
#include <bitset>
#include <chrono>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <lz_error.h>
#include <lz_time.h>
#include <lz_runnable.h>
#include <lz_threadpool.h>

namespace LZ {

class TimePrinterRunnable : public Runnable {
  public:
    void run() override
    {
	std::cout << Time() << '\n';
    }
};

class IMayThrow : public Runnable {
  public:
    IMayThrow(size_t i) : d_index(i) {}
    void run() override
    {
	if (d_index % 2 == 0) {
	    throw std::runtime_error("Even Number " + std::to_string(d_index));
	}
	else if (d_index == 11) {
	    throw d_index;
	}
    }
  private:
    size_t d_index;
};

class Forever : public Runnable {
  public:
    void run() override
	// this function will occupy a thread forever
    {
	std::cout << std::this_thread::get_id() << '\n';
	while (1) {}
    }
};


}

int main()
{
    //LZ::Threadpool<> threadpool;
    using namespace LZ;

    Threadpool<10> threadpool;

    TimePrinterRunnable t;

    auto ret = threadpool.start();

    /*
    for (size_t i = 0; i != 16; ++i) {
	threadpool.addTask(&t);
	//threadpool.addTask(new TimePrinterRunnable());
    }
    threadpool.barrier(2);
    */

    //std::vector<IMayThrow*> imaythrows;
    std::vector<Forever*> forevers;
    for (size_t i = 0; i != 1; ++i) {
	forevers.push_back(new Forever);
	threadpool.addTask(forevers[i]);
    }

    //threadpool.barrier(2);

    /*
    for (size_t i = 0; i != 16; ++i) {
	delete forevers[i];
    }
    */

    // sleep 10 secs

    //std::this_thread::sleep_for(std::chrono::seconds(10));
    //ASSERT_EQ(1, 1);
    //ASSERT_TRUE("123" == "1231");

    //int A[] = {5, 7, 7, 8, 8, 10};
    //vector<int> num = {4, 5, 6, 7 , 8, 0, 1, 2};
    //cout << s. << endl;
    return 0;
}

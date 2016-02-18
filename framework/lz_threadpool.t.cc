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

}

int main()
{
    //LZ::Threadpool<> threadpool;
    using namespace LZ;

    Threadpool<> threadpool;

    TimePrinterRunnable t;

    for (size_t i = 0; i != 16; ++i) {
	threadpool.addTask(&t);
	//threadpool.addTask(new TimePrinterRunnable());
    }

    ASSERT_EQ(threadpool.size(), 16u);
   
    auto ret = threadpool.start();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    //ASSERT_EQ(1, 1);
    //ASSERT_TRUE("123" == "1231");

    //int A[] = {5, 7, 7, 8, 8, 10};
    //vector<int> num = {4, 5, 6, 7 , 8, 0, 1, 2};
    //cout << s. << endl;
    return 0;
}

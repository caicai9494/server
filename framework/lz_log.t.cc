#include <algorithm>
#include <bitset>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <lz_error.h>

#include <lz_log.h> 
#include <unistd.h> 

int main()
{
    //sLog.writeInfo("first.");
    LOG_ERROR("first.");

    std::vector<std::thread> threads;

    for (size_t i = 0; i != 10; ++i) {
	threads.push_back(std::thread([i](){
	    sleep(i);
	    LOG_INFO(i);
            //sLog.writeInfo(i);
	}));
    }

    for (size_t i = 0; i != 10; ++i) {
        assert(threads[i].joinable());
        threads[i].join();
    }
    //ASSERT_EQ(1, 1);
    //ASSERT_TRUE("123" == "1231");

    //int A[] = {5, 7, 7, 8, 8, 10};
    //vector<int> num = {4, 5, 6, 7 , 8, 0, 1, 2};
    //cout << s. << endl;
    return 0;
}

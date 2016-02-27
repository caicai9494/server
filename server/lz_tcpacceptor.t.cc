#include <algorithm>
#include <bitset>
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
#include <lz_tcpacceptor.h> 
#include <lz_tcpexception.h> 
#include <lz_runnable.h>
#include <lz_threadpool.h>

namespace LZ {

class SessionRunnable : public Runnable {
  public:
    SessionRunnable(TcpAcceptor& acpt) :
	d_acceptor(acpt) {}
    void run() override
	// will occupy a thread forever
	// until the connection is closed
	// by the client
    {
	auto stream = d_acceptor.acceptClient();

	while (1) {
	    std::string output;
	    size_t n = stream->getString(output);
	    if (n != 0) {
		std::cout << output << '\n';
	    }
	    else {
		break;
	    }
	}
    }
  private:
    TcpAcceptor& d_acceptor;
};

} // close namespace LZ

int main()
{
    using namespace LZ;

    const int CLI_MAX = 16;

    Threadpool<CLI_MAX> threadpool;
    auto ret = threadpool.start();

    try {

	TcpAcceptor acceptor(8000);
	std::cout << "Accepting...\n";

	std::vector<SessionRunnable*> sessions;
	for (size_t i = 0; i != CLI_MAX; ++i) {
	    sessions.push_back(new SessionRunnable(acceptor));
	    threadpool.addTask(sessions[i]);
	}
	

	/*

	auto stream = acceptor.acceptClient();

	while (1) {
	    std::string output;
	    size_t n = stream->getString(output);
	    if (n != 0) {
		std::cout << output << '\n';
	    }
	    else {
		std::cout << "Closing...\n";
		break;
	    }
	}
	*/

	
    }

    catch (TcpException& ex) {
	std::cerr << ex.what() << '\n';
    }

    //ASSERT_EQ(1, 1);
    //ASSERT_TRUE("123" == "1231");

    //int A[] = {5, 7, 7, 8, 8, 10};
    //vector<int> num = {4, 5, 6, 7 , 8, 0, 1, 2};
    //cout << s. << endl;
    return 0;
}

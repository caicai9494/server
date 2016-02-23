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

int main()
{
    using namespace LZ;

    try {
	TcpAcceptor acceptor(8000);
	std::cout << "Accepting...\n";

	auto stream = acceptor.acceptClient();

	while (1) {
	    std::string output;
	    stream->readTo(output);
	    std::cout << output << '\n';
	}
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

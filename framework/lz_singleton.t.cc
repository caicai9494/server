#include <algorithm>
#include <bitset>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <lz_error.h>

#include <lz_singleton.h>

struct Foo {
    void foo(std::ostream& out) 
    {
	out << "foo\n";
    }
};

int main()
{
    using namespace LZ;

    std::stringstream sstream;
    Singleton<Foo>::instance().foo(sstream);
    ASSERT_EQ(sstream.str(), "foo\n");
    //ASSERT_TRUE("123" == "1231");

    //int A[] = {5, 7, 7, 8, 8, 10};
    //vector<int> num = {4, 5, 6, 7 , 8, 0, 1, 2};
    //cout << s. << endl;
    return 0;
}

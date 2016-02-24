#include <lz_tcpstream.h>

#include <algorithm>

namespace {

static const int MAX_LINE = 128;

} // close unnamed namespace

namespace LZ {

TcpStream::TcpStream(int connfd, const struct sockaddr_in& addr, socklen_t addr_len) :
    d_connfd(connfd), d_addr(addr), d_addr_len(addr_len)
{}

size_t TcpStream::getString(std::string& str) 
{
    char buf[MAX_LINE + 1];
    size_t n = read(d_connfd, buf, MAX_LINE + 1);
    buf[n + 1] = '\0';
    if (n != 0) {
	str = buf;
    }
    return n;
}

size_t TcpStream::putString(const std::string& str) 
{
    size_t n = write(d_connfd, str.c_str(), std::max((int)str.length(), MAX_LINE));
    return n;
}

} // close namespace



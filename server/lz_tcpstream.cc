#include <lz_tcpstream.h>

#include <algorithm>

namespace {

static const int MAX_LINE = 128;

} // close unnamed namespace

namespace LZ {

TcpStream::TcpStream(int connfd, const struct sockaddr_in& cliaddr, socklen_t cliaddr_len) :
    d_connfd(connfd), d_cliaddr(cliaddr), d_cliaddr_len(cliaddr_len)
{}

size_t TcpStream::readTo(std::string& str) 
{
    char buf[MAX_LINE + 1];
    size_t n = read(d_connfd, buf, MAX_LINE + 1);
    if (n != 0) {
	str = buf;
    }
    return n;
}

size_t TcpStream::writeFrom(const std::string& str) 
{
    size_t n = write(d_connfd, str.c_str(), std::max((int)str.length(), MAX_LINE));
    return n;
}

} // close namespace



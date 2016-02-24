#include <lz_tcpconnector.h>
#include <lz_tcpexception.h>

#include <cerrno>
#include <cstring>

#include <arpa/inet.h>

namespace LZ {

void TcpConnector::initSocket()
{
    d_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (d_sockfd < 0) {
	throw LZ::TcpException(std::strerror(errno));
    }
}

std::unique_ptr<TcpStream> TcpConnector::connectServer()
{
    struct sockaddr_in d_servaddr;

    memset(&d_servaddr, 0, sizeof(d_servaddr));
    d_servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, d_ip.c_str(), &d_servaddr.sin_addr.s_addr);
    d_servaddr.sin_port = htons(d_port);

    if (connect(d_sockfd, (struct sockaddr*)&d_servaddr, sizeof(d_servaddr)) < 0) {
	throw LZ::TcpException(std::strerror(errno));
    }

    return std::unique_ptr<TcpStream>(new TcpStream(d_sockfd, d_servaddr, sizeof(d_servaddr)));
}

TcpConnector::TcpConnector(const std::string& ip, short port) : 
  d_port(port), d_ip(ip)
{
    initSocket();
}

} // close namespace



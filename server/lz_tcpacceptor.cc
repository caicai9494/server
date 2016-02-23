#include <lz_tcpacceptor.h>
#include <lz_tcpexception.h>

#include <cerrno>
#include <cstring>

namespace {

static const int BACK_LOG = 20;

} // close unnamed namespace

namespace LZ {

TcpAcceptor::TcpAcceptor(short port) : d_port(port) 
{
    initSocket();
    bindAddr();
    listenClient();
}


void TcpAcceptor::initSocket()
{
    d_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (d_sockfd < 0) {
	throw LZ::TcpException(std::strerror(errno));
    }
}

void TcpAcceptor::bindAddr()
{
    memset(&d_servaddr, 0, sizeof(d_servaddr));
    d_servaddr.sin_family = AF_INET;
    d_servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    d_servaddr.sin_port = htons(d_port);

    if (bind(d_sockfd, (struct sockaddr*)&d_servaddr, sizeof(d_servaddr)) < 0) {
	throw LZ::TcpException(std::strerror(errno));
    }
}

void TcpAcceptor::listenClient()
{
    if (listen(d_sockfd, BACK_LOG) < 0) {
	throw LZ::TcpException(std::strerror(errno));
    }
}

std::unique_ptr<TcpStream> TcpAcceptor::acceptClient() 
{
    struct sockaddr_in cliaddr;
    socklen_t cliaddr_len = sizeof(cliaddr);
    int connfd = accept(d_sockfd, (struct sockaddr*)&cliaddr, &cliaddr_len);
    if (connfd < 0) {
	throw LZ::TcpException(std::strerror(errno));
    }
    return std::unique_ptr<TcpStream>(new TcpStream(connfd, cliaddr, cliaddr_len));
}

} // close namespace



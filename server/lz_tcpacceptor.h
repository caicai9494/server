#ifndef LZ_TCPACCEPTOR_H 
#define LZ_TCPACCEPTOR_H

#include <memory>

#include <lz_tcpstream.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

namespace LZ {

class TcpAcceptor {

  public:

    TcpAcceptor(short port); 
        // initialize the socket and 
	// start to listen on 'port'.
        // throw 'TcpException' on failure

    ~TcpAcceptor() {}

    std::unique_ptr<TcpStream> acceptClient() const;

  private:

    int d_sockfd;
    short d_port;
    struct sockaddr_in d_servaddr;

    void initSocket();
        // throw 'TcpException' on failure
	
    void bindAddr();
        // throw 'TcpException' on failure
	
    void listenClient();
        // throw 'TcpException' on failure

};

} // close namespace

#endif

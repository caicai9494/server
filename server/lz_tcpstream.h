#ifndef LZ_TCPSTREAM_H 
#define LZ_TCPSTREAM_H

#include <iostream>
#include <string>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

namespace LZ {

class TcpStream {

    friend class TcpAcceptor;
    friend class TcpConnector;

  public:

    ~TcpStream() { close(d_connfd); }

    size_t readTo(std::string& str); 
        // Populate 'str' and return byte of 'str' read
	
    size_t writeFrom(const std::string& str); 
        // Return byte of 'str' 

  private:

    TcpStream(int connfd, const struct sockaddr_in& cliaddr, socklen_t cliaddr_len); 

    int d_connfd;
    struct sockaddr_in d_cliaddr;
    socklen_t d_cliaddr_len;

};

} // close namespace

#endif

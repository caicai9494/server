#ifndef LZ_TCPCONNECTOR_H 
#define LZ_TCPCONNECTOR_H

#include <memory>

#include <lz_tcpstream.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

namespace LZ {

class TcpConnector {

  public:

    TcpConnector(const std::string& ip, short port);
        // throw 'TcpException' on failure

    ~TcpConnector() {}

    std::unique_ptr<TcpStream> connectServer();

  private:

    short d_port;

    std::string d_ip;

    int d_sockfd;

    void initSocket();
        // throw 'TcpException' on failure

};

} // close namespace

#endif

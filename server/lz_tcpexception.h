#ifndef LZ_TCPEXCEPTION_H 
#define LZ_TCPEXCEPTION_H

#include <stdexcept>
#include <string>

namespace LZ {

class TcpException : public std::runtime_error {
  public:
    TcpException(const std::string& what_arg) :
        std::runtime_error(what_arg)  {}

};

} // close namespace

#endif

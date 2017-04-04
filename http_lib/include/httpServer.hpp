#ifndef HTTP_SERVER_HPP
#define HTTP_SERVER_HPP

#include "command.hpp"
#include "socket.hpp"

namespace Server
{

class HttpServer
{
public:
    HttpServer(const size_t& requestPort = 8888, const size_t& responcePort = 8889);
    void start();
    ~HttpServer() = default;

private:
    SocketPtr m_requestSock;
    SocketPtr m_responceSock;
};

}

#endif // HTTP_SERVER_HPP

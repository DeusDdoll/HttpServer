#ifndef HTTP_SERVER_HPP
#define HTTP_SERVER_HPP

#include "http/socket.hpp"
#include "http/connection.hpp"
#include <vector>
#include <mutex>
#include <thread>

namespace Network
{

class HttpServer
{
public:
    HttpServer(const std::string& requestPort = "8888");
    void start();
    ~HttpServer() = default;

private:
    TcpSocket m_requestSock;
    std::vector<std::thread> m_connectionPool;
    std::mutex m_mutex;
};

}

#endif // HTTP_SERVER_HPP

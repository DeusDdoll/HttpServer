#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "http/socket.hpp"

namespace Network
{

class Connection
{
public:
    explicit Connection();
    explicit Connection(int socket);

    void start();
    ~Connection() = default;

private:
    TcpSocket m_socket;
};

}


#endif //CONNECTION_HPP

#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <iostream>
#include <stdexcept>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <cerrno>
#include <memory>

#define MAX_SIZE 1024

namespace Network
{

class ISocket
{
public:
    virtual int fd()const = 0;
    virtual void send(const std::string& buff) = 0;
    virtual std::string recv() = 0;
    virtual ~ISocket() {};
};

class TcpSocket: public ISocket
{
public:
    explicit TcpSocket(const std::string& port = "8888");
    explicit TcpSocket(int socket);

    int fd()const override;
    void send(const std::string& buff) override;
    std::string recv() override;
    void bind ();
    void listen(int backlog);
    int accept();

    ~TcpSocket();
private:
    int m_socket;
    struct addrinfo* m_servInfo;
};

using ISocketPtr = std::shared_ptr<ISocket>;
using TcpSocketPtr = std::shared_ptr<TcpSocket>;
}

#endif //SOCKET_HPP

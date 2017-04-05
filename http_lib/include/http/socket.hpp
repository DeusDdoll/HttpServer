#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <iostream>
#include <stdexcept>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <cerrno>

#define MAX_SIZE 1024

namespace Network
{

class ISocket
{
public:
    virtual int fd()const = 0;
    virtual size_t send(const char* buff) = 0;
    virtual std::string recv() = 0;
    virtual ~ISocket() {};
};

class TcpSocket: public ISocket
{
public:
    TcpSocket()
        : m_socket(-1)
    {
        m_socket = ::socket(AF_INET, SOCK_STREAM, 0);
        if (m_socket < 0)
        {
            std::cerr << "Can not create socket! Errno = " << std::to_string(errno);
            exit(1);
        }
    }

    TcpSocket(int socket)
        : m_socket(socket) {}

    int fd()const override
    {
        return m_socket;
    }

    size_t send(const char* buff) override
    {
        auto bytes_sended = ::send(m_socket, buff, strlen(buff), 0);
        if (bytes_sended < 0)
        {
            throw std::runtime_error("Failed to SEND data from socket "
                    + std::to_string(m_socket) + " with errno = " + std::to_string(errno));
        }

        return bytes_sended;
    }

    std::string recv() override
    {
        char buff[MAX_SIZE];
        auto bytes_read = ::recv(m_socket, buff, MAX_SIZE, 0);
        if (bytes_read < 0)
        {
            throw std::runtime_error("Failed to READ data from socket "
                    + std::to_string(m_socket) + " with errno = " + std::to_string(errno));
        }

        return std::string(buff);
    }

    void bindAndListen()
    {
    }

    ~TcpSocket()
    {
        if (close(m_socket))
        {
            throw std::runtime_error("Failed to close socket "
                    + std::to_string(m_socket) + " with errno = " + std::to_string(errno));
        }
    }

private:
    int m_socket;
};

using ISocketPtr = std::shared_ptr<ISocket>;
using TcpSocketPtr = std::shared_ptr<TcpSocket>;
}

#endif //SOCKET_HPP

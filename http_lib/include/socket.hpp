#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <stdexcept>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

#define MAX_SIZE 1024

namespace Network
{

class ISocket
{
public:
    virtual int fd()const = 0;
    virtual size_t send(const char* buff, const size_t& len) = 0;
    virtual size_t recv(char* buff, const size_t& len) = 0;
    virtual ~ISocket() = default;
};

template<class ProtoFamily, class ProtoType>
class Socket: public ISocket
{
public:
    Socket()
        : m_socket(-1)
    {
        m_socket = ::socket(ProtoFamily, ProtoType, 0);
        if (m_socket < 0)
        {
            std::cerr << "Can not create socket! Errno = " << std::to_string(errno);
            exit(1);
        }
    }

    Socket(int socket)
        : m_socket(socket) {}

    size_t send(const char* buff) override
    {
        auto bytes_sended = send(m_socket, buff, strlen(buff), 0);
        if (bytes_sended < 0)
        {
            throw std::runtime_error("Failed to SEND data from socket "
                    + std::to_string(m_socket) + " with errno = " << std::to_string(errno));
        }

        return bytes_sended;
    }

    size_t recv(char* buff) override
    {
        auto bytes_read = recv(m_socket, buff, MAX_SIZE, 0);
        if (bytes_read < 0)
        {
            throw std::runtime_error("Failed to READ data from socket "
                    + std::to_string(m_socket) + " with errno = " << std::to_string(errno));
        }

        return bytes_read;
    }

    void bindAndListen()
    {
    }

    ~Socket()
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

using TcpSocket = Socket<AF_INET, SOCK_STREAM>;
using TcpSocketPtr = shared_ptr<TcpSocket>;
}

#endif //SOCKET_HPP

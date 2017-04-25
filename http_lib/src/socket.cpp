#include "http/socket.hpp"
#include <array>
#include <sys/socket.h>

namespace Network
{

TcpSocket::TcpSocket(const std::string& port)
{
    struct addrinfo hints;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if (getaddrinfo(NULL, port.c_str(), &hints, &m_servInfo) < 0)
    {
        std::cerr << "getaddrinfo failed!" << std::endl;
        exit(1);
    }

    if ((m_socket = ::socket(m_servInfo->ai_family, m_servInfo->ai_socktype, m_servInfo->ai_protocol)) < 0)
    {
        std::cerr << "Can not create socket! Error = " << std::to_string(errno) << std::endl;
    }
}

TcpSocket::TcpSocket(int socket)
    : m_socket(socket) {}

int TcpSocket::fd()const
{
    return m_socket;
}

void TcpSocket::send(const std::string&  buff)
{
    auto bytes_sended = ::send(m_socket, buff.c_str(), buff.size(), 0);
    if (bytes_sended < 0)
    {
        throw std::runtime_error("Failed to SEND data from socket " + 
               std::to_string(m_socket) + " with errno = " + std::to_string(errno));
    }
}

std::string TcpSocket::recv()
{
    char buff[MAX_SIZE];
    auto bytes_read = ::recv(m_socket, buff, sizeof(buff), 0);
    if (bytes_read < 0)
    {
        throw std::runtime_error("Failed to RECV data from socket " + 
               std::to_string(m_socket) + " with errno = " + std::to_string(errno));
    }

    return std::string(buff);
}

void TcpSocket::bind()
{
    if (::bind(m_socket, m_servInfo->ai_addr, m_servInfo->ai_addrlen) < 0)
    {
        throw std::runtime_error("Failed to bind socket " +
                std::to_string(m_socket));
    }
}

void TcpSocket::listen(int backlog)
{
    if (::listen(m_socket, backlog) < 0)
    {
        throw std::runtime_error("Failed to start listen, socket: " + std::to_string(m_socket));
    }
}

int TcpSocket::accept()
{
    struct sockaddr_in peer;
    socklen_t addr_size = sizeof(peer);
    int new_fd;
    if((new_fd = ::accept(m_socket, (struct sockaddr*)&peer, &addr_size)) < 0)
    {
       throw std::runtime_error("Failed to accept new connection!"); 
    }
    std::cout << "Connection from peer!" << std::endl;

    return new_fd;
}

TcpSocket::~TcpSocket()
{
    if (close(m_socket))
    {
        throw std::runtime_error("Failed to close socket " +
                std::to_string(m_socket) + " with errno = " + std::to_string(errno));
    }
    //freeaddrinfo(m_servInfo);
}

} //namespace Network


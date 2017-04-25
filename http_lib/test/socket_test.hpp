#include "http/socket.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <sys/types.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <chrono>
#include <thread>
#include <stdexcept>
#include <iostream>

using namespace Network;
using namespace Utils;

class TcpSocketMock : public TcpSocket
{
public:
    MOCK_METHOD0(recv, std::string());
    MOCK_METHOD0(bind, void());
    MOCK_METHOD0(accept, TcpSocket());
    MOCK_METHOD1(listen, void(int));
    MOCK_METHOD1(send, void(const std::string&));
};

TEST(SocketTest, CreateSocketMustReturtValidFD)
{
    TcpSocket sock("9999");
    EXPECT_GT(sock.fd(), -1);
}

//Ya, I know that this is not UNIT-test.
TEST(SocketTest, SockReciveExpectedStr)
{
    TcpSocket sock("9998");
    EXPECT_GT(sock.fd(), -1);
    EXPECT_NO_THROW(sock.bind());
    EXPECT_NO_THROW(sock.listen(1));

    std::thread client(
            []
            {
            struct sockaddr_in addr;
            addr.sin_family = AF_INET;
            addr.sin_addr.s_addr = inet_addr("127.0.0.1");
            addr.sin_port = htons(9998);

            std::this_thread::sleep_for(std::chrono::seconds(1));

            int socket = ::socket(AF_INET, SOCK_STREAM, 0);
            if(connect(socket, (struct sockaddr*)&addr, sizeof(addr)) < 0)
            std::cout << "Connection error\n " << errno << std::endl;

            if (::send(socket, "hello\n\0", sizeof("hello\n\0"), 0) < 0)
            std::cout << "Can not send" << errno << std::endl;

            close(socket);
            });

    client.detach();

    std::string request;
    auto a = TcpSocket(sock.accept());
    request = a.recv();

    EXPECT_EQ(request, "hello\n");
}

TEST(SocketTest, SockSendExpectedStr)
{
    TcpSocket sock("9997");
    EXPECT_GT(sock.fd(), -1);

    EXPECT_NO_THROW(sock.bind());
    EXPECT_NO_THROW(sock.listen(1));

    std::thread client(
            []
            {
            struct sockaddr_in addr;
            addr.sin_family = AF_INET;
            addr.sin_addr.s_addr = inet_addr("127.0.0.1");
            addr.sin_port = htons(9997);

            std::this_thread::sleep_for(std::chrono::seconds(1));

            int socket = ::socket(AF_INET, SOCK_STREAM, 0);
            if(connect(socket, (struct sockaddr*)&addr, sizeof(addr)) < 0)
                std::cout << "Connection error\n " << errno << std::endl;

            char buff[1024];

            if (::recv(socket, buff, sizeof(buff), 0) < 0)
                std::cout << "Can not send" << errno << std::endl;

            EXPECT_EQ(std::string(buff), "hello\n");

            close(socket);
            });

    client.detach();

    std::string request = "hello\n";
    auto a = TcpSocket(sock.accept());
    a.send(request);
}


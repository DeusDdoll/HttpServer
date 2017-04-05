#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <memory>
#include <http/socket.hpp>

namespace utils
{

// Command will be used by ThreadPool, that will call exec method
// Thread pool is implementing now..

class Command
{
public:

    virtual void exec() = 0;
    virtual ~Command() = default;
};

class HttpCommand: public Command
{
public:
    HttpCommand() = default;
    HttpCommand(Network::TcpSocket&& socket, std::string&& request);
    void exec();
    void sendResponce();
    ~HttpCommand() = default;
private:
    std::string m_request;
    Network::TcpSocket m_socket;
};

}

#endif //COMMAND_HPP

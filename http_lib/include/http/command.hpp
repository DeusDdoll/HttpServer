#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <memory>


namespace utils
{

// Command will be used by ThreadPool, that will call exec method
// Thread pool is implementing now..

class Command
{
public:

    virtual auto exec() = 0;
    virtual ~Command() = default;
};

class HttpCommand: public Command
{
public:
    HttpCommand() = default;
    HttpCommand(TcpSocket&& socket, std::string&& request);
    void exec() override;
    void sendResponce();
    ~HttpCommand() = default;
private:
    std::string m_request;
    TcpSocket m_socket;
};

}

#endif //COMMAND_HPP

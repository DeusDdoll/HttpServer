#include "command.hpp"
#include "request.hpp"

namespace utils
{

HttpCommand::HttpCommand(TcpSocket&& socket, std::string&& request)
    : m_socket(std::move(socket))
    , m_request(std::move(request)) {}

void HttpCommand::exec() override
{
    sendResponce();
}

void HttpCommand::sendResponce()
{
    try
    {
        while(!shouldStop())
        {
            auto request(parseRequest(std::move(m_request)));

            switch(request.m_type)
            {
                case network::Type::GET:
                    //TODO: implement befawior for GET request
                    break;
                case network::Type::POST:
                    //TODO: implement befawior for POST request
                    break;
                case network::Type::ERROR:
                    break;
                default:
                    break;
            }

            m_request = m_socket->read();
        }
    }
    catch (const std::exception& err)
    {
        std::cerr << "Exception! " << err.what() << std::endl;
    }
}

}

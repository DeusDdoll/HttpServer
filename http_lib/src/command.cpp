#include <utility>

#include "http/command.hpp"
#include "http/request.hpp"

namespace utils
{

HttpCommand::HttpCommand(Network::TcpSocket&& socket, std::string&& request)
    : m_socket(std::move(socket))
    , m_request(std::move(request)) {}

void HttpCommand::exec()
{
    sendResponce();
}

void HttpCommand::sendResponce()
{
    try
    {
        //TODO: implement exit for this loop
        while(true)
        {
            //TODO: implement parser for HTTP command
            auto request(Network::parseRequest(std::move(m_request)));

            switch(request.m_type)
            {
                case Network::Type::GET:
                    //TODO: implement befawior for GET request
                    break;
                case Network::Type::POST:
                    //TODO: implement befawior for POST request
                    break;
                case Network::Type::ERROR:
                    break;
                default:
                    break;
            }

            m_request = m_socket.recv();

        }
    }
    catch (const std::exception& err)
    {
        std::cerr << "Exception! " << err.what() << std::endl;
    }
}

}

#include "http/connection.hpp"
#include "http/request.hpp"
#include "http/worker.hpp"

namespace Network
{

Connection::Connection()
    : m_socket() {}

Connection::Connection(TcpSocket&& socket)
    : m_socket(std::move(socket)) {}

void Connection::start()
{
    try
    {
        while (true) //TODO: add flag to socket, if connection closed by peer
        {
            std::string rawRequest = m_socket.recv();

            HttpRequest httpRequest = Network::parseRequest(std::move(rawRequest));

            Utils::Worker http_worker(std::move(httpRequest));

            m_socket.send(http_worker.request());
        }
    }
    catch (const std::exception& err)
    {
        std::cerr << "Exception during connection with peer\n"
            << "Connection refused!" << std::endl;
    }
}

}

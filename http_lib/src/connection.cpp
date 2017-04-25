#include "http/connection.hpp"
#include "http/request.hpp"
#include "http/worker.hpp"

namespace Network
{

Connection::Connection()
    : m_socket() {}

Connection::Connection(int socket)
    : m_socket(socket) {}

void Connection::start()
{
    std::cout << "Start connection" << std::endl;
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
            << err.what()
            << "\nConnection refused!" << std::endl;
    }
}

}

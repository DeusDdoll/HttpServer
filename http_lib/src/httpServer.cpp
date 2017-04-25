#include "http/httpServer.hpp"
#define MAX_PEERS 15
namespace Network
{

HttpServer::HttpServer(const std::string& requestPort)
    : m_requestSock(requestPort) {}

void HttpServer::start()
{
    while(true)
    {
        try
        {
            m_requestSock.bind();
            m_requestSock.listen(MAX_PEERS);
            while(true)
            {
                auto conn_socket = m_requestSock.accept();

                std::thread t([&]
                        {
                            Connection conn(conn_socket);
                            conn.start();
                        });
                {
                    std::lock_guard<std::mutex> lock(m_mutex);
                    m_connectionPool.emplace_back(std::move(t));
                }
            }
        }
        catch(const std::exception& err)
        {
            std::cerr << "EXCEPTION: " << err.what() << std::endl;
        }
    }
}

}

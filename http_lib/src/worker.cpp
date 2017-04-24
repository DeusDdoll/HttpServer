#include "http/worker.hpp"

#include <stdio.h>
#include <sstream>
#include <stdexcept>
#include <fstream>

namespace Utils
{

Worker::Worker(Network::HttpRequest&& request)
{
    using namespace Network;


    switch(request.m_method)
    {

    case Method::GET:
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        std::ifstream fin(request.m_page);
        std::string content;
        fin >> content;
        m_responce = "HTTP/1.1 200 OK\r\n" + content;
        fin.close();
        break;
    }
    case Method::POST:
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        std::ofstream fout(request.m_page);
        fout << request.m_content;
        m_responce = "HTTP/1.1 200 OK\r\n";
        fout.close();
        break;
    }
    case Method::ERROR:
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        std::ifstream fin(request.m_page);
        fin >> m_responce;
        fin.close();
        break;
    }

    case Method::NOTHING:
    {
        break;
    }

    }
}

std::string Worker::request()const
{
    return m_responce;
}

}

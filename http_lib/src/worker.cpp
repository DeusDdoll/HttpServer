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

        if (!fin.is_open())
        {
            throw std::runtime_error("Failed to find page " + request.m_page);
        }

        std::string tmp;
        std::string content;

        while(std::getline(fin, tmp))
        {
            content += tmp + "\n";
        }

        m_responce = "HTTP/1.1 200 OK\n\n" + content;
        fin.close();
        break;
    }
    case Method::POST:
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        std::ofstream fout(request.m_page);

        if (!fout.is_open())
        {
            throw std::runtime_error("Failed to open page " + request.m_page);
        }

        fout << request.m_content;
        m_responce = "HTTP/1.1 200 OK\n\n";
        fout.close();
        break;
    }
    case Method::ERROR:
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        std::ifstream fin(request.m_page);

        if (!fin.is_open())
        {
            throw std::runtime_error("Failed to find page " + request.m_page);
        }

        std::string tmp;
        std::string content;
        while(std::getline(fin, tmp))
        {
            content += tmp + "\n";
        }

        m_responce = content;
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

#ifndef WORKER_HPP
#define WORKER_HPP

#include <mutex>
#include <string>
#include "http/request.hpp"

namespace Utils
{

class Worker
{
public:
    explicit Worker(Network::HttpRequest&& request);
    std::string request()const;
    ~Worker() = default;
private:
    std::mutex m_mutex;
    std::string m_responce;
};

}

#endif //WORKER_HPP

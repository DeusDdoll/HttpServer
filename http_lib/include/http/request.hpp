#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <string>
#include <regex>

namespace Network
{

enum class Method
{
    GET,
    POST,
    ERROR,
    NOTHING
};

struct HttpRequest
{
    HttpRequest();
    HttpRequest(const Method& type, const std::string& page, const std::string& body = "");
    HttpRequest(const HttpRequest&) = default;

    Method m_method;
    std::string m_page;
    std::string m_content;

    ~HttpRequest() = default;
};

HttpRequest parseRequest(std::string&& request);

}

#endif //REQUEST_HPP


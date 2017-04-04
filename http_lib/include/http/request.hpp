#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <string>
#include <regex>

namespace Network
{

enum class Type
{
    GET,
    POST,
    ERROR,
    NOTHING
};

struct HttpRequest
{
    HttpRequest()
        : m_type(Type::NOTHING)
        , m_body() {}

    HttpRequest(const Type& type, const std::string& body)
        : m_type(type)
        , m_body(body) {}

    HttpRequest(const HttpRequest&) = default

    Type m_type;
    std::string m_body;

    ~HttpRequest() = default;
};

HttpRequest parseRequest(std::string&& request);

}

#endif //REQUEST_HPP


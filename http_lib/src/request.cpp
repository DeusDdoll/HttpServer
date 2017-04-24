#include "http/request.hpp"

#include <regex> 
#include <iostream>
namespace Network
{

HttpRequest::HttpRequest()
    : m_method(Method::NOTHING)
    , m_page()
    , m_content() {}

HttpRequest::HttpRequest(const Method& type, const std::string& file, const std::string& body)
    : m_method(type)
    , m_page(file)
    , m_content(body) {}

HttpRequest parseRequest(std::string&& request)
{
    std::regex methodMatch("([A-Z]+) \\/([a-z]+.*) ([A-Z]+\\/\\d\\.\\d)(\n|\n.*\n\n(.*))");
    std::smatch regexp;
    if(std::regex_match(request, regexp, methodMatch))
    {
        if (regexp[1] == "GET")
        {
            if (regexp[2] == "index.html")
            {
                return HttpRequest(Method::GET, regexp[2]);
            }

            if (regexp[2] == "memo")
            {
                return HttpRequest(Method::GET, regexp[2]);
            }

            return HttpRequest(Method::ERROR, "404.html");
        }

        if (regexp[1] == "POST")
        {
            if (regexp[2] == "memo")
            {
                return HttpRequest(Method::POST, "memo", regexp[5]);
            }
            if (regexp[2] == "index.html")
            {
                return HttpRequest(Method::ERROR, "403.html");
            }

            return HttpRequest(Method::ERROR, "404.html");
        }
    }

    return HttpRequest(Method::ERROR, "400.html");
}

}

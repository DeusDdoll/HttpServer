#include <iostream>
#include "gtest/gtest.h"
#include "http/request.hpp"

using namespace Utils;
using namespace Network;

TEST(ParserTest, ParseEmptyString)
{
    HttpRequest badHttp(Method::ERROR, "400.html"); //incorect HTTP
    EXPECT_EQ(parseRequest("").m_page, badHttp.m_page);
    EXPECT_EQ(parseRequest("").m_method, badHttp.m_method);
    EXPECT_EQ(parseRequest("").m_content, badHttp.m_content);
}

TEST(ParserTest, ParseWrongHTTP)
{
    HttpRequest requestLine(Method::ERROR, "400.html");
    EXPECT_EQ(parseRequest("GET /index.html HTTP1\n").m_page, requestLine.m_page);
    EXPECT_EQ(parseRequest("GET /index.html HTTP1\n").m_method, requestLine.m_method);
    EXPECT_EQ(parseRequest("GET /index.html HTTP1\n").m_content, requestLine.m_content);
}

TEST(ParserTest, ParseGetRequestWithIndex)
{
    HttpRequest requestLine(Method::GET, "index.html");
    EXPECT_EQ(parseRequest("GET /index.html HTTP/1.1\n").m_page, requestLine.m_page);
    EXPECT_EQ(parseRequest("GET /index.html HTTP/1.1\n").m_method, requestLine.m_method);
    EXPECT_EQ(parseRequest("GET /index.html HTTP/1.1\n").m_content, requestLine.m_content);
}

TEST(ParserTest, ParseGetRequestWithMemo)
{
    HttpRequest requestLine(Method::GET, "memo");
    EXPECT_EQ(parseRequest("GET /memo HTTP/1.1\n").m_page, requestLine.m_page);
    EXPECT_EQ(parseRequest("GET /memo HTTP/1.1\n").m_method, requestLine.m_method);
    EXPECT_EQ(parseRequest("GET /memo HTTP/1.1\n").m_content, requestLine.m_content);
}

TEST(ParserTest, ParseGetRequestWithError)
{
    HttpRequest requestLine(Method::ERROR, "404.html");
    EXPECT_EQ(parseRequest("GET /dsadw HTTP/1.1\n").m_page, requestLine.m_page);
    EXPECT_EQ(parseRequest("GET /dsadw HTTP/1.1\n").m_method, requestLine.m_method);
    EXPECT_EQ(parseRequest("GET /dsadw HTTP/1.1\n").m_content, requestLine.m_content);
}

TEST(ParseTest, ParsePostRequestWithMemo)
{
    HttpRequest requestLine(Method::POST, "memo", "hello");
    EXPECT_EQ(parseRequest("POST /memo HTTP/1.1\n\n\nhello").m_page, requestLine.m_page);
    EXPECT_EQ(parseRequest("POST /memo HTTP/1.1\n\n\nhello").m_method, requestLine.m_method);
    EXPECT_EQ(parseRequest("POST /memo HTTP/1.1\n\n\nhello").m_content, requestLine.m_content);
}

TEST(ParseTest, ParsePostRequestWithIndex)
{
    HttpRequest requestLine(Method::ERROR, "403.html");
    EXPECT_EQ(parseRequest("POST /index.html HTTP/1.1\n").m_page, requestLine.m_page);
    EXPECT_EQ(parseRequest("POST /index.html HTTP/1.1\n").m_method, requestLine.m_method);
    EXPECT_EQ(parseRequest("POST /index.html HTTP/1.1\n").m_content, requestLine.m_content);
}

TEST(ParseTest, ParsePostRequestWithError)
{
    HttpRequest requestLine(Method::ERROR, "404.html");
    EXPECT_EQ(parseRequest("POST /dsadw HTTP/1.1\n").m_page, requestLine.m_page);
    EXPECT_EQ(parseRequest("POST /dsadw HTTP/1.1\n").m_method, requestLine.m_method);
    EXPECT_EQ(parseRequest("POST /dsadw HTTP/1.1\n").m_content, requestLine.m_content);
}

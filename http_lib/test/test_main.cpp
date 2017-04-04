#include <iostream>
#include "gtest/gtest.h"

TEST(ParserTest, ParseEmptyString)
{
    EmptyCommand empty;
    EXPECT_EQ(empty, parse_http(empty.c_str()));
}

TEST(ParserTest, ParseHttpHeader)
{
    EmptyCommand empty;
    EXPECT_EQ(empty, parse_http(
        "Host: net.tutsplus.com" \
        "Accept-Language: en-us,en;q=0.5" \
        "Accept-Encoding: gzip,deflate"));
}

TEST(ParserTest, ParseHttpRequest)
{
    GetCommand get;
    EXPECT_EQ(get, parse_http(
        "GET /hello.htm HTTP/1.1"));
}

GTEST_API_ int main(int argc, char** argv)
{
    std::cout << "Google tests for the http_lib" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

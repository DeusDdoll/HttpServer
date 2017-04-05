#include <iostream>
#include "gtest/gtest.h"

TEST(ParserTest, ParseEmptyString)
{
}

TEST(ParserTest, ParseHttpHeader)
{
}

TEST(ParserTest, ParseHttpRequest)
{
}

GTEST_API_ int main(int argc, char** argv)
{
    std::cout << "Google tests for the http_lib" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

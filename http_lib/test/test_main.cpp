#include <iostream>
#include "gtest/gtest.h"
#include "http/request.hpp"
#include "http/socket.hpp"
#include "http/connection.hpp"
#include "http/worker.hpp"

#include "parser_test.hpp"
#include "worker_test.hpp"

GTEST_API_ int main(int argc, char** argv)
{
    std::cout << "Google tests for the http_lib" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

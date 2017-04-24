#include "http/worker.hpp"

#include <stdexcept>
#include <fstream>
#include <stdio.h>

#include "gtest/gtest.h"

using namespace Network;
using namespace Utils;

TEST(WorkerTest, WorkerWrongPage)
{
    EXPECT_THROW(Worker work(HttpRequest(Method::GET, "sadwasd")), std::exception);
    EXPECT_THROW(Worker work(HttpRequest(Method::ERROR, "sadwasd")), std::exception);
}

TEST(WorkerTest, WorkerGetIndexRequest)
{
    Worker work(HttpRequest(Method::GET, "test_data/index.html"));
    EXPECT_EQ(work.request(), "HTTP/1.1 200 OK\n\nhello\n");
}

TEST(WorkerTest, WorkerGetMemoRequest)
{
    Worker work(HttpRequest(Method::GET, "test_data/memo"));
    EXPECT_EQ(work.request(), "HTTP/1.1 200 OK\n\nmemo\n");
}

TEST(WorkerTest, WorkerPostMemoRequest)
{
    Worker work(HttpRequest(Method::POST, "test_data/memooo", "A lot of text\n"));
    ASSERT_EQ(work.request(), "HTTP/1.1 200 OK\n\n");
    std::ifstream fin("test_data/memooo");

    EXPECT_TRUE(fin.is_open());

    std::string content = "";
    std::string tmp = "";
    while(std::getline(fin, tmp))
    {
        content += tmp + "\n";
    }

    fin.close();

    EXPECT_EQ(content, "A lot of text\n");

    ::remove("test_data/memooo");
}

TEST(WorkerTest, WorkerErrorRequest)
{
    Worker work1(HttpRequest(Method::ERROR, "test_data/400.html"));
    EXPECT_EQ(work1.request(), "Bad HTTP 400\n\n");

    Worker work2(HttpRequest(Method::ERROR, "test_data/403.html"));
    EXPECT_EQ(work2.request(), "HTTP 403 Forbidden\n\n");

    Worker work3(HttpRequest(Method::ERROR, "test_data/404.html"));
    EXPECT_EQ(work3.request(), "HTTP 404 Failed to find page\n\n");
}

#include "http/httpServer.hpp"

int main()
{
    Network::HttpServer serv("8888");
    serv.start();
    return 0;
}

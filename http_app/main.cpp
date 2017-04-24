#include "http/httpServer.hpp"

int main()
{
    HttpServer serv("8888");
    serv.start();
    return 0;
}

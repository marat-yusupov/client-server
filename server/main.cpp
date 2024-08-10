#include <network/server.h>

#include <boost/asio.hpp>
#include <iostream>

int main() {
    network::Server::Instance().Run();
    return 0;
}
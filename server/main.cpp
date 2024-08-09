#include <server.h>

#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

int main() {
    Server::Instance().Run();
    return 0;
}
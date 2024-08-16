#include <iostream>

#include <boost/asio.hpp>

#include <network/server.h>

int main() {
    try {
        boost::asio::io_context io_context;
        network::Server server{io_context};
        io_context.run();
    } catch (std::exception& exception) {
        std::cerr << "[SERVER::ERROR] " << exception.what() << std::endl;
    }
    return 0;
}
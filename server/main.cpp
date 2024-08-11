#include <network/server.h>

#include <boost/asio.hpp>
#include <iostream>

int main() {
    try {
        boost::asio::io_context io_context;
        network::Server server{io_context};
        io_context.run();
    } catch (std::exception& exception) {
        std::cerr << "[ERROR] " << exception.what() << std::endl;
    }
    return 0;
}
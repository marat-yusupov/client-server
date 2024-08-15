#include <iostream>

#include <boost/asio.hpp>

#include <data/config.h>
#include <network/server.h>

int main() {
    try {
        data::Config config("config.txt");
        boost::asio::io_context io_context;
        network::Server server{io_context};
        io_context.run();
    } catch (std::exception& exception) {
        std::cerr << "[SERVER::ERROR] " << exception.what() << std::endl;
    }
    return 0;
}
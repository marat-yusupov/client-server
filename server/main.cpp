#include <iostream>

#include <boost/asio.hpp>

#include <generic/log_utils.h>

#include <network/server.h>

int main() {
    try {
        boost::asio::io_context io_context;
        network::Server server{io_context};
        io_context.run();
    } catch (std::exception& exception) {
        generic::LogErr(__func__, exception.what());
    }
    return 0;
}
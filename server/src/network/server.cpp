#include <iostream>
#include <thread>

#include <boost/asio.hpp>

#include <network/connection.h>
#include <network/server.h>

namespace network {

Server::Server(boost::asio::io_context& io_context)
    : mContext{io_context}, mAcceptor{mContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8080)} {
    StartAccept();
}

void Server::StartAccept() {
    std::cout << "[SERVER] Start listen on " << mAcceptor.local_endpoint() << std::endl;
    for (;;) {
        auto new_connection = Connection::Create(mContext);
        mAcceptor.accept(new_connection->Socket());
        std::thread accept_handler{[this, new_connection]() { new_connection->Start(); }};
        accept_handler.detach();
    }
    std::cout << "[SERVER] Stop listen on " << mAcceptor.local_endpoint() << std::endl;
}

}  // namespace network

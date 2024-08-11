#include <ctime>
#include <iostream>
#include <thread>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <network/connection.h>
#include <network/server.h>

namespace network {

Server::Server(boost::asio::io_context& io_context)
    : mContext{io_context}, mAcceptor{mContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8080)} {
    StartAccept();
}

void Server::StartAccept() {
    for (;;) {
        auto new_connection = Connection::Create(mContext);

        mAcceptor.accept(new_connection->Socket());
        std::thread accept_handler{[this, new_connection]() { HandleAccept(new_connection); }};
        accept_handler.detach();
    }
}

void Server::HandleAccept(std::shared_ptr<Connection> connection) {
    connection->Start();
}

}  // namespace network

#include <iostream>
#include <thread>

#include <boost/asio.hpp>

#include <generic/log_utils.h>
#include <generic/thread_pool.h>

#include <network/connection.h>
#include <network/server.h>

namespace network {

Server::Server(boost::asio::io_context& io_context)
    : mContext{io_context}, mAcceptor{mContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8080)} {
    StartAccept();
}

void Server::StartAccept() {
    generic::Log(__func__, "Start listen on " + mAcceptor.local_endpoint().address().to_string());
    generic::ThreadPool thread_pool;
    for (;;) {
        auto new_connection = Connection::Create(mContext);
        mAcceptor.accept(new_connection->Socket());
        thread_pool.Enqueue([new_connection] { new_connection->Start(); });
    }

    generic::Log(__func__, "Stop listen on" + mAcceptor.local_endpoint().address().to_string());
}

}  // namespace network

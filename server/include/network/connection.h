#pragma once

#include <request/manager.h>

#include <boost/asio.hpp>

namespace network {

class Connection {
public:
    static std::shared_ptr<Connection> Create(boost::asio::io_context& io_context);
    ~Connection();

    boost::asio::ip::tcp::socket& Socket();

    void Start();

private:
    Connection(boost::asio::io_context& io_context);

    boost::asio::ip::tcp::socket mSocket;
    request::Manager mManager;
};

}  // namespace network

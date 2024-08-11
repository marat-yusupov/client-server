#include <iostream>
#include <string>

#include <boost/asio.hpp>

#include <network/connection.h>

namespace network {

std::shared_ptr<Connection> Connection::Create(boost::asio::io_context& io_context) {
    return std::shared_ptr<Connection>(new Connection(io_context));
}

Connection::Connection(boost::asio::io_context& io_context) : mSocket{io_context} {}

Connection::~Connection() {
    if (mSocket.is_open())
        mSocket.close();
}

boost::asio::ip::tcp::socket& Connection::Socket() {
    return mSocket;
}

void Connection::Start() {
    char temp_buffer[1024];
    boost::system::error_code error_code;

    auto len = mSocket.read_some(boost::asio::buffer(temp_buffer), error_code);
    if (error_code) {
        std::cout << "[SERVER::WARNING::GetRequestData] Failed read request (ERROR_CODE: " << error_code << ")"
                  << std::endl;
        return;
    }

    std::string request{};
    request.append(temp_buffer, len);
    std::cout << "[SERVER::GetRequestData] " << request << std::endl;
}

}  // namespace network

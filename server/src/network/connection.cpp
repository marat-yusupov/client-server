#include <iostream>
#include <thread>

#include <boost/asio.hpp>

#include <network/connection.h>
#include <request/manager.h>

namespace network {

std::shared_ptr<Connection> Connection::Create(boost::asio::io_context& io_context) {
    return std::shared_ptr<Connection>(new Connection(io_context));
}

Connection::Connection(boost::asio::io_context& io_context) : mSocket{io_context}, mManager{mSocket} {}

Connection::~Connection() {
    if (mSocket.is_open())
        mSocket.close();
}

boost::asio::ip::tcp::socket& Connection::Socket() {
    return mSocket;
}

// TODO: Подумать, как реализовать таймер, чтобы отключаться от клиента, если запросов нет более N-секунд
// TODO: Подумать, как разбить метод на разные методы
void Connection::Start() {
    std::cout << "[SERVER] Сonnection established" << std::endl;

    // TODO: Переделать на while(mSocket.is_open()) когда будет реализован таймер
    for (;;) {
        char temp_buffer[1024];
        boost::system::error_code error_code;

        auto len = mSocket.read_some(boost::asio::buffer(temp_buffer), error_code);
        if (error_code) {
            if (error_code != boost::asio::error::eof) {
                std::cout << "[SERVER::WARNING] Failed read request (ERROR_CODE: " << error_code << ")" << std::endl;
                continue;
            }

            std::cout << "[SERVER] Connection reset by peer" << std::endl;
            mSocket.close();
            return;
        }

        std::string request{};
        request.append(temp_buffer, len);
        std::cout << "[SERVER] Request received:\n" << request << std::endl;

        mManager.Process(request);
    }
}

}  // namespace network

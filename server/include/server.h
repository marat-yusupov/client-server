#include <boost/asio.hpp>

class Server {
public:
    static Server& Instance();
    void Run();

private:
    Server() = default;

    void ListenSocket(boost::asio::ip::tcp::endpoint& endpoint,
                      boost::asio::io_service& io_service,
                      boost::asio::ip::tcp::acceptor& acceptor);

    std::string ReadRequest(boost::asio::ip::tcp::socket& socket);
};

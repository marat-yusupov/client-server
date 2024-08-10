#include <boost/asio.hpp>

namespace network {

class Server {
public:
    static Server& Instance();
    void Run();

private:
    Server() = default;

    void ListenSocket(boost::asio::ip::tcp::endpoint& endpoint,
                      boost::asio::io_service& io_service,
                      boost::asio::ip::tcp::acceptor& acceptor);

    void HandleConnection(boost::asio::ip::tcp::socket& socket);

    std::string GetRequestData(boost::asio::ip::tcp::socket& socket);
};

}  // namespace network

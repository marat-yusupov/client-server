#include <boost/asio.hpp>

namespace network {

class Connection;

class Server {
public:
    Server(boost::asio::io_context& io_context);

private:
    void StartAccept();

    boost::asio::io_context& mContext;
    boost::asio::ip::tcp::acceptor mAcceptor;
};

}  // namespace network

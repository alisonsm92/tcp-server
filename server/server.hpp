#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class server
{
public:
  server(boost::asio::io_context &io_context, short port);

private:
  void accept();

tcp::acceptor acceptor_;
};
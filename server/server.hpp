#include <boost/asio.hpp>
#include "config_loader.hpp"

using boost::asio::ip::tcp;

class server
{
public:
  server(boost::asio::io_context &io_context, const common::ServerConfig& config);

private:
  void accept();

  tcp::acceptor acceptor;
  common::ServerConfig config;
  short session_count;
};
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class server
{
public:
  server(boost::asio::io_context &io_context, short port, std::size_t max_file_size, int timeout, std::string file_prefix);

private:
  void accept();

  tcp::acceptor acceptor;
  std::size_t max_file_size;
  int timeout;
  std::string file_prefix;
};
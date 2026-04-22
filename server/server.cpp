#include <boost/asio.hpp>
#include "session.hpp"
#include "server.hpp"

using boost::asio::ip::tcp;

server::server(boost::asio::io_context &io_context, const common::ServerConfig& config)
    : acceptor(io_context, tcp::endpoint(tcp::v4(), config.port)),
      config(config),
      session_count(0)
{
  accept();
}

void server::accept()
{
  acceptor.async_accept(
      [this](boost::system::error_code ec, tcp::socket socket)
      {
        if (!ec)
        {
          std::make_shared<session>(std::move(socket), config, ++session_count)->start();
        }

        accept();
      });
}
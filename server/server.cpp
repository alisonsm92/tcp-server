#include <iostream>
#include <boost/asio.hpp>
#include "session.hpp"
#include "server.hpp"

using boost::asio::ip::tcp;

server::server(boost::asio::io_context &io_context, short port, std::size_t max_file_size, int timeout)
    : acceptor(io_context, tcp::endpoint(tcp::v4(), port)),
      max_file_size(max_file_size),
      timeout(timeout)
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
          std::make_shared<session>(std::move(socket), max_file_size, timeout)->start();
        }

        accept();
      });
}
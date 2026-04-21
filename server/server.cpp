// Based on the Boost.Asio C++ library example: 
// https://www.boost.org/doc/libs/1_81_0/doc/html/boost_asio/example/cpp11_examples.html#boost_asio.example.cpp11_examples.async_tcp_echo_server
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2025 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <iostream>
#include <boost/asio.hpp>
#include "session.hpp"
#include "server.hpp"

using boost::asio::ip::tcp;

server::server(boost::asio::io_context &io_context, short port)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
{
  accept();
}

void server::accept()
{
  acceptor_.async_accept(
      [this](boost::system::error_code ec, tcp::socket socket)
      {
        if (!ec)
        {
          std::make_shared<session>(std::move(socket))->start();
        }

        accept();
      });
}
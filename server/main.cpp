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
#include <fstream>
#include <boost/asio.hpp>
#include "server.hpp"

using boost::asio::ip::tcp;

int main() {
    short port = 8080;
    boost::asio::io_context io_context;
    server s(io_context, port);
    std::cout << "Server running on port " << port << "..." << std::endl;
    io_context.run();
    return 0;
}
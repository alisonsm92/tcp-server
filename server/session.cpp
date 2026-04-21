// Based on the Boost.Asio C++ library example: 
// https://www.boost.org/doc/libs/1_81_0/doc/html/boost_asio/example/cpp11_examples.html#boost_asio.example.cpp11_examples.async_tcp_echo_server
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2025 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <utility>
#include <iostream>
#include <fstream>
#include "session.hpp"

session::session(tcp::socket socket) 
    : socket_(std::move(socket)) {
}

void session::start() {
    auto remote_endpoint = socket_.remote_endpoint();
    std::string filename = "data/session_" + 
      remote_endpoint.address().to_string() + "_" + 
      std::to_string(remote_endpoint.port()) + ".bin";
    
    output_file_.open(filename, std::ios::binary);
    std::cout << "Starting session. Saving to: " << filename << std::endl;
    
    read();
}

void session::write_to_file(const char* data, std::size_t length) {
    if (output_file_.is_open()) {
        output_file_.write(data, length);
        output_file_.flush();
        std::cout << "Saved " << length << " bytes." << std::endl;
    }
}

void session::read() {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                write_to_file(data_, length);
                read();
            }
        });
}
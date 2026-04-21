#include <utility>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>
#include <chrono>
#include "session.hpp"

session::session(tcp::socket socket, std::size_t max_file_size, int timeout_seconds) 
    : socket(std::move(socket)), 
      max_file_size(max_file_size), 
      bytes_written(0),
      timeout_seconds(timeout_seconds),
      timer(this->socket.get_executor())
{
}

void session::start() {
    auto remote_endpoint = socket.remote_endpoint();
    std::time_t timestamp = std::time(nullptr);

    std::string session_name = std::to_string(timestamp) + "_" +
      remote_endpoint.address().to_string() + "_" + 
      std::to_string(remote_endpoint.port());

    std::string filename = "data/session_" + session_name + ".bin";
    
    output_file.open(filename, std::ios::binary);
    std::cout << "Starting session. Saving to: " << filename << std::endl;
    
    timer.expires_after(std::chrono::seconds(timeout_seconds));
    check_timeout(session_name);
    read();
}

void session::write_to_file(const char* data, std::size_t length) {
    if (bytes_written >= max_file_size) {
        std::cerr << "ERROR: File size limit already reached (" << max_file_size << " bytes)." << std::endl;
        return;
    }

    std::size_t space_left = max_file_size - bytes_written;
    std::size_t bytes_to_write = space_left > length ? length : space_left;

    if (output_file.is_open()) {
        output_file.write(data, bytes_to_write);
        output_file.flush();
        bytes_written += bytes_to_write;
        
        if (bytes_to_write < length) {
            std::cerr << "WARNING: Only " << bytes_to_write << " of " << length 
                      << " bytes were saved. File size limit reached!" << std::endl;
        } else {
          std::cout << "Saved " << bytes_to_write << " bytes." << std::endl;
        }
    }
}

void session::read() {
    auto self(shared_from_this());
    socket.async_read_some(boost::asio::buffer(data, max_length),
        [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                timer.expires_after(std::chrono::seconds(timeout_seconds));
                write_to_file(data, length);
                read();
            }
        });
}

void session::check_timeout(std::string session_name) {
    auto self(shared_from_this());
    timer.async_wait([this, self, session_name](const boost::system::error_code& ec) {
        if (ec == boost::asio::error::operation_aborted) {
            check_timeout(session_name);
        } else if (!ec) {
            std::cout << "Session timeout (" << session_name << "). Closing connection." << std::endl;
            socket.close();
        }
    });
}
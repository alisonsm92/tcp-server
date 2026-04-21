#include <utility>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>
#include "session.hpp"

session::session(tcp::socket socket, std::size_t max_file_size) 
    : socket(std::move(socket)), max_file_size(max_file_size), bytes_written(0) {
}

void session::start() {
    auto remote_endpoint = socket.remote_endpoint();
    std::time_t timestamp = std::time(nullptr);

    std::string filename = "data/session_" + 
      std::to_string(timestamp) + "_" +
      remote_endpoint.address().to_string() + "_" + 
      std::to_string(remote_endpoint.port()) + ".bin";
    
    output_file.open(filename, std::ios::binary | std::ios::app);
    std::cout << "Starting session. Saving to: " << filename << std::endl;
    
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
                write_to_file(data, length);
                read();
            }
        });
}
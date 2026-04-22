#include <utility>
#include <iostream>
#include <ctime>
#include <chrono>
#include "session.hpp"

session::session(tcp::socket socket, const common::ServerConfig& config) 
    : socket(std::move(socket)), 
      config(config),
      session_id(std::to_string(std::time(nullptr))),
      bytes_written(0),
      file_name("data.bin"),
      file_index(0),
      timer(this->socket.get_executor())
{
}

void session::start() {
    timer.expires_after(std::chrono::seconds(config.timeout));
    check_timeout();
    read();
}

void session::write_to_file(const char* data, std::size_t length) {
    std::size_t remaining = length;
    const char* current_pointer = data;

    while (remaining > 0) {
        if (!output_file.is_open() || bytes_written >= config.max_file_size) {
            if (output_file.is_open()) {
              output_file.close();
            }
            
            file_name = "data/" + config.file_prefix + '_' + session_id + "_" + std::to_string(++file_index) + ".bin";
            
            output_file.open(file_name, std::ios::binary);
            bytes_written = 0;
            std::cout << "Opening new file: " << file_name << std::endl;
        }

        std::size_t space_left = config.max_file_size - bytes_written;
        std::size_t bytes_to_write = (remaining < space_left) ? remaining : space_left;

        output_file.write(current_pointer, bytes_to_write);
        output_file.flush();

        bytes_written += bytes_to_write;
        remaining -= bytes_to_write;
        current_pointer += bytes_to_write;

        std::cout << "Saved " << bytes_to_write << " bytes to file: " << file_name << std::endl;
    }
}

void session::read() {
    auto self(shared_from_this());
    socket.async_read_some(boost::asio::buffer(data, max_length),
        [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                timer.expires_after(std::chrono::seconds(config.timeout));
                write_to_file(data, length);
                read();
            }
        });
}

void session::check_timeout() {
    auto self(shared_from_this());
    timer.async_wait([this, self](const boost::system::error_code& ec) {
        if (ec == boost::asio::error::operation_aborted) {
            check_timeout();
        } else if (!ec) {
            std::cout << "Session timeout (" << session_id << "). Closing connection." << std::endl;
            socket.close();
        }
    });
}
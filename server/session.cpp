#include <utility>
#include <iostream>
#include <ctime>
#include <chrono>
#include "session.hpp"

session::session(tcp::socket socket, const common::ServerConfig& config, short session_id) 
    : socket(std::move(socket)), 
      config(config),
      session_id(session_id),
      bytes_written(0),
      file_name("data.bin"),
      timer(this->socket.get_executor())
{
}

void session::start() {
    std::cout << "[ session: " << session_id << "] " << "New session started." << std::endl;
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

            std::time_t timestamp = std::time(nullptr);
            
            file_name = "data/" + config.file_prefix + '_' + std::to_string(timestamp) + ".bin";
            
            output_file.open(file_name, std::ios::binary);
            bytes_written = 0;
            std::cout << "[ session: " << session_id << "] " << "Opening new file: " << file_name << std::endl;
        }

        std::size_t space_left = config.max_file_size - bytes_written;
        std::size_t bytes_to_write = (remaining < space_left) ? remaining : space_left;

        output_file.write(current_pointer, bytes_to_write);
        output_file.flush();

        bytes_written += bytes_to_write;
        remaining -= bytes_to_write;
        current_pointer += bytes_to_write;

        std::cout << "[ session: " << session_id << "] " << "Saved " << bytes_to_write << " bytes to file: " << file_name << std::endl;
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
            std::cout << "[ session: " << session_id << "] " << "Timeout! Closing connection." << std::endl;
            
            auto send_buffer = std::make_shared<std::string>("TIMEOUT");
            boost::asio::async_write(socket, boost::asio::buffer(*send_buffer),
                [this, self, send_buffer](boost::system::error_code /*ec*/, std::size_t /*length*/) {
                    socket.close();
                });
        }
    });
}
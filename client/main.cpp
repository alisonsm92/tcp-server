#include <iostream>
#include <boost/asio.hpp>
#include "config_loader.hpp"

using boost::asio::ip::tcp;

int main() {
    try {
        std::string host = "server";
        short port_val = common::load_port_config("client/client.conf");
        std::string port = std::to_string(port_val);

        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve(host, port);

        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        std::cout << "Connected to server at " << host << ":" << port << std::endl;
        std::cout << "Type your messages:" << std::endl;
        std::string line;

        while (std::getline(std::cin, line)) {
            if (line.empty()) continue;

            boost::system::error_code wec;
            boost::asio::write(socket, boost::asio::buffer(line), wec);

            std::cout << "\033[A"; // Move cursor up to overwrite the input line
            std::cout << "\r" << line << " ";

            socket.non_blocking(true);
            char buffer[1024];
            boost::system::error_code rec;
            size_t bytes = socket.read_some(boost::asio::buffer(buffer), rec);
            std::string response(buffer, bytes);

            if (response.find("TIMEOUT") != std::string::npos) {
                std::cout << "✘" << std::endl;  
                std::cout << "Server disconnected. Closing client." << std::endl;
                break;
            }

            if (!wec) {
                std::cout << "✓" << std::endl;
            } else {
                std::cout << "✘" << std::endl;
                std::cout << "Failed to send message: " << wec.message() << std::endl;
                continue;
            }
        }
    } catch (std::exception& e) {
      std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}

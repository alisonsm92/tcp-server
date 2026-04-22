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
            boost::asio::write(socket, boost::asio::buffer(line));
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}

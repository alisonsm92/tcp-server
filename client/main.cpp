#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main() {
    try {
        std::string host = "server";

        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve(host, "8080");

        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        std::cout << "Connected to server at " << host << ":8080" << std::endl;
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

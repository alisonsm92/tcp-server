#include <iostream>
#include <fstream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main() {
    const int port = 8080;
    boost::asio::io_context io_context;
    tcp::acceptor(io_context, tcp::endpoint(tcp::v4(), port));
    std::cout << "Server running on port " << port << "..." << std::endl;
    return 0;
}
#include <iostream>
#include <boost/asio.hpp>
#include "server.hpp"
#include "config_loader.hpp"

int main() {
    config_loader::ServerConfig config = config_loader::parse_config("server.conf");
    boost::asio::io_context io_context;
    server s(io_context, config);
    
    std::cout << "Server running on port " << config.port << "..." << std::endl;
    io_context.run();

    return 0;
}
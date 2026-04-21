#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <boost/asio.hpp>
#include "server.hpp"

using boost::asio::ip::tcp;

std::map<std::string, std::string> load_config(const std::string& filename) {
    std::map<std::string, std::string> config;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        size_t delimiter_pos = line.find('=');
        config[line.substr(0, delimiter_pos)] = line.substr(delimiter_pos + 1);
    }
    return config;
}

int main() {
    auto config = load_config("server.conf");
    short port = config.count("PORT") ? std::stoi(config["PORT"]) : 8080;
    std::size_t max_file_size = config.count("MAX_FILE_SIZE") 
      ? std::stoul(config["MAX_FILE_SIZE"]) 
      : 1024;

    boost::asio::io_context io_context;
    server s(io_context, port, max_file_size);
    std::cout << "Server running on port " << port << "..." << std::endl;
    io_context.run();

    return 0;
}
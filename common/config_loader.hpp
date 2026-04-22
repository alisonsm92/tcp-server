#ifndef COMMON_CONFIG_LOADER_HPP
#define COMMON_CONFIG_LOADER_HPP

#include <string>
#include <map>

namespace common {

struct ServerConfig {
    short port;
    std::size_t max_file_size;
    int timeout;
    std::string file_prefix;
};


int validate_numeric(const std::string& key, std::string value);

std::map<std::string, std::string> load_config_map(const std::string& filename);

ServerConfig parse_server_config(const std::string& filename);

short load_port_config(const std::string& filename);

}

#endif
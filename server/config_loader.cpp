#include "config_loader.hpp"
#include <iostream>
#include <fstream>
#include <regex>
#include <type_traits>

namespace config_loader {

static const std::regex numeric_regex("^[0-9]+$");

template <typename T>
T validate_numeric(const std::string& key, std::string value) {
    if (value.back() == '\r') {
        value.pop_back();
    }
    
    if (!std::regex_match(value, numeric_regex)) {
        std::cerr << "Error: The " << key << " configuration must be a valid integer. Value found: " << value << std::endl;
        std::exit(1);
    }
    
    return std::stoi(value);
}

std::map<std::string, std::string> load_config_map(const std::string& filename) {
    std::map<std::string, std::string> config;
    std::ifstream file(filename);
    
    std::string line;
    while (std::getline(file, line)) {
        size_t delimiter_pos = line.find('=');
        if (delimiter_pos != std::string::npos) {
            config[line.substr(0, delimiter_pos)] = line.substr(delimiter_pos + 1);
        }
    }
    return config;
}

ServerConfig parse_config(const std::string& filename) {
    auto config_map = load_config_map(filename);
    ServerConfig sc;

    sc.port = config_map.count("PORT") 
        ? validate_numeric<short>("PORT", config_map.at("PORT")) 
        : 8080;

    sc.max_file_size = config_map.count("MAX_FILE_SIZE") 
        ? validate_numeric<std::size_t>("MAX_FILE_SIZE", config_map.at("MAX_FILE_SIZE")) 
        : 1024;

    sc.timeout = config_map.count("TIMEOUT_IN_SECONDS") 
        ? validate_numeric<int>("TIMEOUT_IN_SECONDS", config_map.at("TIMEOUT_IN_SECONDS")) 
        : 10;

    sc.file_prefix = config_map.count("FILE_NAME_PREFIX") 
      ? config_map.at("FILE_NAME_PREFIX") 
      : "session";

    return sc;
}

}

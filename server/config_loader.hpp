#include <string>
#include <map>

namespace config_loader {

struct ServerConfig {
    short port;
    std::size_t max_file_size;
    int timeout;
    std::string file_prefix;
};

ServerConfig parse_config(const std::string& filename);

}
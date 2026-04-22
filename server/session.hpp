#include <memory>
#include <boost/asio.hpp>
#include <fstream>
#include "config_loader.hpp"

using boost::asio::ip::tcp;

class session : public std::enable_shared_from_this<session> {
public:
    session(tcp::socket socket, const common::ServerConfig& config, short session_id);
    void start();

private:
    void read();
    void write_to_file(const char* data, std::size_t length);
    void check_timeout();

    tcp::socket socket;
    common::ServerConfig config;
    short session_id;
    boost::asio::steady_timer timer;
    std::size_t bytes_written;
    std::string file_name;
    std::ofstream output_file;
    static constexpr std::size_t max_length = 1024;
    char data[max_length];
};
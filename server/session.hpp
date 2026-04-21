#include <memory>
#include <boost/asio.hpp>
#include <fstream>

using boost::asio::ip::tcp;

class session : public std::enable_shared_from_this<session> {
public:
    session(tcp::socket socket, std::size_t max_file_size, int timeout_seconds);
    void start();

private:
    void read();
    void write_to_file(const char* data, std::size_t length);
    void check_timeout(std::string filename);

    tcp::socket socket;
    std::size_t max_file_size;
    int timeout_seconds;
    boost::asio::steady_timer timer;
    std::size_t bytes_written;
    std::ofstream output_file;
    static constexpr std::size_t max_length = 1024;
    char data[max_length];
};
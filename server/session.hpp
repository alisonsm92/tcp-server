#include <memory>
#include <boost/asio.hpp>
#include <fstream>

using boost::asio::ip::tcp;

class session : public std::enable_shared_from_this<session> {
public:
    explicit session(tcp::socket socket);
    void start();

private:
    void read();
    void write_to_file(const char* data, std::size_t length);

    tcp::socket socket_;
    std::ofstream output_file_;
    static constexpr std::size_t max_length = 1024;
    char data_[max_length];
};
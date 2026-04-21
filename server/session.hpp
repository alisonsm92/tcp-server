#include <memory>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class session : public std::enable_shared_from_this<session> {
public:
    explicit session(tcp::socket socket);
    void start();

private:
    void read();
    
tcp::socket socket_;
static constexpr std::size_t max_length = 1024;
char data_[max_length];
};
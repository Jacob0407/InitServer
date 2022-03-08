#include <iostream>
#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "boost/enable_shared_from_this.hpp"

using namespace std;
using namespace boost::asio;

typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;

io_service service;

class InitClient : public boost::enable_shared_from_this<InitClient>
{
public:
	InitClient() {}
	~InitClient() {}

	void start();
	void stop();

	void send_message(void* data) {}
	void recv_message() {}

private:
	void async_connect(std::string ip, unsigned short port);
	void handle_connect(const boost::system::error_code& e);

private:
	socket_ptr socket_;
};

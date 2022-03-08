#include "InitClient.h"

void InitClient::start()
{
	socket_.reset(new ip::tcp::socket(service));
	async_connect("127.0.0.1", 1225);
}

void InitClient::stop()
{

}

void InitClient::async_connect(std::string ip, unsigned short port)
{
	cout << __FUNCTION__ << " async connect  ip: " << ip << " port: " << port << endl;

	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(ip), port);

	socket_->async_connect(ep, [=, _ = shared_from_this()](const boost::system::error_code& e) {
		handle_connect(e);
	});
}

void InitClient::handle_connect(const boost::system::error_code& e)
{
	cout << __FUNCTION__ << " handle data" << endl;
}

int main()
{
	boost::shared_ptr<InitClient> client(new InitClient);
	client->start();
	service.run();
	return 0;
}
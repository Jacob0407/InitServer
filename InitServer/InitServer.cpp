#include "InitServer.h"

using namespace std;


bool InitSever::bind(std::string ip, unsigned short port)
{
	cout << __FUNCTION__ << " [bind]. ip: " << ip << " port: " << port << endl;

	boost::system::error_code ec;
	if (acceptor_.is_open())
	{
		acceptor_.close(ec);
		if (ec)
		{
			cout << __FUNCTION__ << " [bind] acceptor close failed. error: " << ec.value() << " " << ec.message() << endl;
			return false;
		}
	}

	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(ip), port);
	acceptor_.open(ep.protocol(), ec);
	if (ec)
	{
		cout << __FUNCTION__ << " [bind] acceptor open failed. error: " << ec.value() << " " << ec.message() << endl;
		return false;
	}

	acceptor_.bind(ep, ec);
	if (ec)
	{
		cout << __FUNCTION__ << " [bind] acceptor bind failed. error: " << ec.value() << " " << ec.message() << endl;
		return false;
	}

	return true;
}

void InitSever::listen()
{
	boost::system::error_code ec;
	acceptor_.listen((int)backlog_, ec);
	if (ec)
	{
		cout << __FUNCTION__ << " listen failed. error: " << ec.value() << " " << ec.message() << endl;
		return;
	}

	cout << __FUNCTION__ << " listen success." << endl;
}

void InitSever::async_accept()
{
	cout << __FUNCTION__ << " wait connect" << endl;

	acceptor_.async_accept(*socket_, [=, _=shared_from_this()](const boost::system::error_code& e)
	{
		handle_accept(e);
	});
}

void InitSever::handle_accept(const boost::system::error_code& e)
{
	if (e)
	{
		cout << __FUNCTION__ << " [handle] failed. error: " << e.value() << " " << e.message() << endl;
		return;
	}

	cout << __FUNCTION__ << " ready handle connect" << endl;

	// 读取数据等操作
	recv_message();
	socket_.reset(new ip::tcp::socket(service));
	// 再次发起accept等待
	async_accept();
}

void InitSever::start()
{
	socket_.reset(new ip::tcp::socket(service));
	bind("127.0.0.1", 1225);
	listen();
	async_accept();
}

void InitSever::stop()
{

}

void InitSever::send_message(void* data)
{

}

void InitSever::recv_message()
{
	cout << __FUNCTION__ << " ready to read data from socket." << endl;
}


int main()
{
	boost::shared_ptr<InitSever> server(new InitSever);
	server->start();
	service.run();
	return 0;
}

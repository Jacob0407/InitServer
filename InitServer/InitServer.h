// InitServer.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

#include <iostream>
#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "boost/enable_shared_from_this.hpp"

using namespace boost::asio;

typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;

io_service service;

class InitSever : public boost::enable_shared_from_this<InitSever>
{
public:
	InitSever() : acceptor_(service) {}
	~InitSever() {}

	void start();
	void stop();

	void send_message(void* data);
	void recv_message();

private:
	bool bind(std::string ip, unsigned short point);
	void listen();
	void async_accept();
	void handle_accept(const boost::system::error_code& e);

private:
	socket_ptr socket_;
	ip::tcp::acceptor acceptor_;
	std::size_t backlog_;
};

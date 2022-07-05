// InitServer.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

#include "Connection.h"

io_service service;

class InitSever : public boost::enable_shared_from_this<InitSever>
{
public:
	InitSever()
	{
		acceptor_.reset(new ip::tcp::acceptor(service, ip::tcp::endpoint(ip::address::from_string("127.0.0.1"), 1225)));
	}
	~InitSever()
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	void start();
	void stop();

	void async_accept();
	void handle_accept(connection_ptr conn, const boost::system::error_code& e);

private:
	acceptor_ptr acceptor_;
	std::vector<connection_ptr> connections_;
};

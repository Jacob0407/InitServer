#pragma once

#include <iostream>
#include <queue>
#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "boost/enable_shared_from_this.hpp"

using namespace boost::asio;

typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;
typedef boost::shared_ptr<ip::tcp::acceptor> acceptor_ptr;
typedef boost::shared_ptr<io_service> io_service_ptr;

class Connection : public boost::enable_shared_from_this<Connection>
{
public:
	Connection(io_service_ptr s): service_(s) 
	{
		socket_.reset(new ip::tcp::socket(*service_));
	}
	inline ip::tcp::socket& get_socket_ref() { return *(socket_.get()); }

	void connect(const std::string& ip, short port);

	void push_msg(const std::string& msg);

	void receive_msg();
	void send_msg();

private:
	void on_connected(const boost::system::error_code& e);
	void on_send(const boost::system::error_code& e, size_t bytes);
	void on_receive(const boost::system::error_code& e, size_t bytes);
	size_t receive_complete(const boost::system::error_code& e, size_t bytes);

private:
	io_service_ptr service_;
	socket_ptr socket_;
	char read_buff_[1024];
	std::vector<char> write_buff_;
	std::vector<char> message_;
};

typedef boost::shared_ptr<Connection> connection_ptr;
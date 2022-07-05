#include "Connection.h"

void Connection::connect(const std::string& ip, short port)
{
	std::cout << __FUNCTION__ << " ip: " << ip << " port: " << port << std::endl;

	ip::tcp::endpoint ep(ip::address::from_string(ip), port);
	socket_->async_connect(ep, boost::bind(&Connection::on_connected, shared_from_this(), _1));
}

void Connection::on_connected(const boost::system::error_code& e)
{
	if (e)
	{
		std::cout << __FUNCTION__ << " connect failed. e: " << e << std::endl;
		return;
	}

	std::cout << __FUNCTION__ << std::endl;
	send_msg();
}

void Connection::receive_msg()
{
	std::cout << __FUNCTION__ << std::endl;

	async_read(
		*socket_, 
		buffer(read_buff_), 
		boost::bind(&Connection::receive_complete, shared_from_this(), _1, _2),
		boost::bind(&Connection::on_receive, shared_from_this(), _1, _2));
}

void Connection::send_msg()
{
	std::cout << __FUNCTION__ << " size: " << write_buff_.size() << std::endl;
	if (write_buff_.empty())
	{
		socket_->close();
		return;
	}
	
	socket_->async_write_some(
		buffer(write_buff_, write_buff_.size()),
		boost::bind(&Connection::on_send, shared_from_this(), _1, _2));
}

void Connection::on_send(const boost::system::error_code& e, size_t bytes)
{
	std::cout << __FUNCTION__ << " bytes: " << bytes << std::endl;
	write_buff_.clear();
	receive_msg();
}

void Connection::on_receive(const boost::system::error_code& e, size_t bytes)
{
	read_buff_[bytes] = '\0';
	std::cout << __FUNCTION__ << " bytes: " << bytes << " info: " << read_buff_ << std::endl;
	send_msg();
}

size_t Connection::receive_complete(const boost::system::error_code& e, size_t bytes)
{
	if (e)
	{
		std::cout << __FUNCTION__ << " error_code: " << e << " bytes: " << bytes << std::endl;
		socket_->close();
		return 0;
	}

	bool found = std::find(read_buff_, read_buff_ + bytes, '>') < read_buff_ + bytes;
	// std::cout << __FUNCTION__ << " bytes: " << bytes << " found:" << found << std::endl;
	return found ? 0 : 1;
}

void Connection::push_msg(const std::string& msg)
{
	std::cout << __FUNCTION__ << " msg: " << msg << std::endl;
	write_buff_.clear();
	write_buff_.assign(msg.begin(), msg.end());
}
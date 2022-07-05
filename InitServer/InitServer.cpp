#include "InitServer.h"

using namespace std;

void InitSever::start()
{
	async_accept();
}

void InitSever::stop()
{

}

void InitSever::async_accept()
{
	std::cout << __FUNCTION__ << std::endl;

	connection_ptr conn = connection_ptr(new Connection(io_service_ptr(&service)));
	acceptor_->async_accept(conn->get_socket_ref(), boost::bind(&InitSever::handle_accept, shared_from_this(), conn, _1));
}

void InitSever::handle_accept(connection_ptr conn, const boost::system::error_code& e)
{
	if (e)
	{
		std::cout << __FUNCTION__ << " handle accept failed. e: " << e << std::endl;
		return;
	}

	std::cout << __FUNCTION__ << std::endl;
	connections_.push_back(conn);	// important!!!
	conn->receive_msg();

	async_accept();
}



int main()
{
	boost::shared_ptr<InitSever> server = boost::shared_ptr<InitSever>(new InitSever);
	server->start();
	service.run();

	system("pause");

	return 0;
}

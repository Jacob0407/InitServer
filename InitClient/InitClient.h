#include <iostream>
#include "Connection.h"

io_service service;

class InitClient : public boost::enable_shared_from_this<InitClient>
{
public:
	InitClient()
	{
		connection_.reset(new Connection(boost::shared_ptr<io_service>(&service)));
	}
	~InitClient()
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	void start();
	void stop();

private:
	connection_ptr connection_;
};

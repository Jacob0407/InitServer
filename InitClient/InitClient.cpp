#include "InitClient.h"

void InitClient::start()
{
	connection_->push_msg("hello>");
	connection_->connect("127.0.0.1", 1225);
}

void InitClient::stop()
{

}

int main()
{
	InitClient client;
	client.start();
	service.run();

	system("pause");

	return 0;
}
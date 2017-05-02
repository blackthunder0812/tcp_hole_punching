#include <iostream>
#include "client/client.hpp"

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
	boost::asio::io_service _io_service;
    client _client(_io_service, "localhost", "34568");
	_client.start();
	_io_service.run();
	return 0;
}

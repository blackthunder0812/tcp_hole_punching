#include "client/client.hpp"

client::client(boost::asio::io_service& io_service, std::string host, std::string port) :
_socket(io_service),
_host(std::move(host)),
_port(std::move(port)),
_resolver(io_service) {

}

void client::start() {
	std::cout << "Resolving " << _host << ":" << _port << std::endl;
	boost::asio::ip::tcp::resolver::query query(_host, _port);
	_resolver.async_resolve(
	query,
	boost::bind(&client::handle_resolve, this,
	boost::asio::placeholders::error,
	boost::asio::placeholders::iterator));
}

void client::stop() {

}

void client::handle_resolve(const boost::system::error_code& err, boost::asio::ip::tcp::resolver::iterator endpoint_iterator) {
	if(!err) {
		std::cout << "Endpoint list: " << std::endl;
		do {
			std::cout << endpoint_iterator->endpoint() << std::endl;
			endpoint_iterator++;
		} while (endpoint_iterator != boost::asio::ip::tcp::resolver::iterator());
	} else {
		std::cerr << "Error code: " << err.message() << std::endl;
	}
}

void client::do_connect() {

}

void client::do_read() {

}

void client::do_write() {

}

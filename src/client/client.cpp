#include "client/client.hpp"

client::client(boost::asio::io_service& io_service, std::string host, std::string port) :
_socket(io_service),
_host(std::move(host)),
_port(std::move(port)),
_resolver(io_service),
_resolver_result() {

}

void client::start() {
	boost::asio::spawn(_socket.get_io_service(), boost::bind(&client::do_resolve, this, _1));
}

void client::stop() {

}

void client::do_resolve(boost::asio::yield_context yield) {
	std::cout << "Resolving " << _host << ":" << _port << std::endl;
	_resolver.async_resolve(boost::asio::ip::tcp::resolver::query(_host, _port),
	boost::bind(&client::handle_resolve, this,
	boost::asio::placeholders::error,
	boost::asio::placeholders::iterator));
}

void client::handle_resolve(const boost::system::error_code& err, boost::asio::ip::tcp::resolver::iterator endpoint_iterator) {
	if(!err) {
		// save resolver's result
		_resolver_result = endpoint_iterator;

		// connect using resolver's result
		boost::asio::spawn(_socket.get_io_service(), boost::bind(&client::do_connect, this, _1));
	} else {
		std::cerr << "Error code: " << err.message() << std::endl;
	}
}

void client::do_connect(boost::asio::yield_context yield) {
	boost::asio::async_connect(_socket, _resolver_result, boost::asio::ip::tcp::resolver::iterator(),
	boost::bind(&client::handle_connect, this,
	boost::asio::placeholders::error,
	boost::asio::placeholders::iterator));
}

void client::handle_connect(const boost::system::error_code& err, boost::asio::ip::tcp::resolver::iterator endpoint_iterator) {
	if(!err) {
		// print out resolver's result
		std::cout << "Connected endpoint: " << endpoint_iterator->endpoint() << std::endl;
	} else {
		std::cerr << "Error code: " << err.message() << std::endl;
	}
}

void client::do_read() {

}

void client::do_write() {

}

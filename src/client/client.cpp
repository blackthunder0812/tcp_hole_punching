#include "client/client.hpp"

client::client(boost::asio::io_service& io_service, std::string host, short port) :
_socket(io_service),
_host(std::move(host)),
_port(port) {

}

void client::start() {
//	boost::asio::spawn(_socket.get_io_service(), [this] (boost::asio::yield_context yield) {
//		do_resolve(yield);
//	});

	boost::asio::spawn(_socket.get_io_service(), boost::bind(do_resolve, this, _1));
}

void client::stop() {

}

void client::do_resolve(boost::asio::yield_context& yield) {
//	boost::asio::ip::tcp::resolver::async_resolve({boost::asio::ip::tcp::v4(), _host, _port}, yield);
//	boost::asio::spawn(_io_service, [this] (boost::asio::yield_context yield) {
//		do_connect();
//	});
}

void client::do_connect() {

}

void client::do_read() {

}

void client::do_write() {

}

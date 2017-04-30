#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_

#include <iostream>
#include <string>
#include <memory>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>

class client {
	private:
		boost::asio::ip::tcp::socket _socket;
		std::string _host;
		std::string _port;
		boost::asio::ip::tcp::resolver _resolver;

		void handle_resolve(const boost::system::error_code& err, boost::asio::ip::tcp::resolver::iterator endpoint_iterator);
		void do_connect();
		void do_read();
		void do_write();
	public:
		client(boost::asio::io_service& io_service, std::string host, std::string port);
		void start();
		void stop();
};

#endif

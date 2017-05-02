#include "client/client.hpp"

client::client(boost::asio::io_service &io_service,
               std::string host,
               std::string port) :
    _socket(io_service),
    _host(std::move(host)),
    _port(std::move(port)),
    _resolver(io_service),
    _resolver_result()
{
}

void client::start()
{
    boost::asio::spawn(_socket.get_io_service(),
                       std::bind(&client::do_resolve,
                                 this,
                                 std::placeholders::_1));
}

void client::stop()
{
    _socket.close();
}

void client::do_resolve(boost::asio::yield_context yield)
{
	(void)yield;
    std::cout << "Resolving " << _host << ":" << _port << std::endl;
    _resolver.async_resolve(boost::asio::ip::tcp::resolver::query(_host, _port),
                            std::bind(&client::handle_resolve,
                                      this,
                                      std::placeholders::_1,
                                      std::placeholders::_2));
}

void client::handle_resolve(const boost::system::error_code &err,
                            boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
{
	if(!err) {
		// save resolver's result
		_resolver_result = endpoint_iterator;
		// connect using resolver's result
        boost::asio::spawn(_socket.get_io_service(),
                           std::bind(&client::do_connect,
                                     this,
                                     std::placeholders::_1));
	} else {
		std::cerr << "Error code: " << err.message() << std::endl;
	}
}

void client::do_connect(boost::asio::yield_context yield)
{
	(void)yield;
    boost::asio::async_connect(_socket,
                               _resolver_result,
                               boost::asio::ip::tcp::resolver::iterator(),
                               std::bind(&client::handle_connect,
                                         this,
                                         std::placeholders::_1,
                                         std::placeholders::_2));
}

void client::handle_connect(const boost::system::error_code &err,
                            boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
{
	if(!err) {
		// print out resolver's result
		std::cout << "Connected endpoint: " << endpoint_iterator->endpoint() << std::endl;
        // logic handling
        boost::asio::spawn(_socket.get_io_service(),
                           std::bind(&client::do_logic,
                                     this,
                                     std::placeholders::_1));
	} else {
		std::cerr << "Error code: " << err.message() << std::endl;
	}
}

void client::do_logic(boost::asio::yield_context yield)
{
    std::size_t n;
    boost::system::error_code ec;
    char data[128] = "test echo client\n";

    for (;;) {
        n = boost::asio::async_write(_socket, boost::asio::buffer(data, 17), yield[ec]);

        if(!ec) {
            std::cout << "written " << n << " bytes" << std::endl;
        } else if (ec == boost::asio::error::eof) {
            std::cout << "Endpoint closed connection cleanly" << std::endl;
            break;
        } else {
            std::cerr << ec.message() << std::endl;
        }

        n = boost::asio::async_read(_socket, boost::asio::buffer(data, 17), yield[ec]);

        if(!ec) {
            std::cout << "read " << n << " bytes:" << std::endl;
            std::cout.write(data, n);
            std::cout << std::endl;
        } else if (ec == boost::asio::error::eof) {
            std::cout << "Endpoint closed connection cleanly" << std::endl;
            break;
        } else {
            std::cerr << ec.message() << std::endl;
        }

        // wait 5 seconds before continue sending package
        sleep(5);
    }
}

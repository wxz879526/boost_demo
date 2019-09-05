// BoostDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <ctime>
#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/enable_shared_from_this.hpp"

std::string make_daytime_string()
{
	time_t now = time(0);

	char szBuffer[100] = { 0 };
	ctime_s(szBuffer, 100, &now);
	return szBuffer;
}

class tcp_connection : public boost::enable_shared_from_this<tcp_connection>
{
public:
	typedef boost::shared_ptr<tcp_connection> pointer;

	static pointer create(boost::asio::io_context &io_ctx)
	{
		return pointer(new tcp_connection(io_ctx));
	}

	boost::asio::ip::tcp::socket& socket()
	{
		return socket_;
	}

	void start()
	{
		message_ = make_daytime_string();

		boost::asio::async_write(socket_,
			boost::asio::buffer(message_),
			boost::bind(&tcp_connection::handle_write, shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}

private:
	tcp_connection(boost::asio::io_context &io_ctx)
		: socket_(io_ctx)
	{

	}

	void handle_write(const boost::system::error_code &code, size_t size)
	{

	}

private:
	boost::asio::ip::tcp::socket socket_;
	std::string message_;
};

class tcp_server
{
public:
	tcp_server(boost::asio::io_context &c)
		: io_ctx(c)
		, acceptor_(c, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 13))
	{
		start_accept();
	}

private:

	void start_accept()
	{
		tcp_connection::pointer new_connection = tcp_connection::create(io_ctx);

		acceptor_.async_accept(new_connection->socket(),
			boost::bind(&tcp_server::handle_accept, this, new_connection,
				boost::asio::placeholders::error));
	}

	void handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code &error)
	{
		if (!error)
		{
			new_connection->start();
		}

		start_accept();
	}

	boost::asio::io_context &io_ctx;
	boost::asio::ip::tcp::acceptor acceptor_;
};

int main()
{
	try
	{
		boost::asio::io_context io_ctx;

		tcp_server server(io_ctx);
		io_ctx.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	

	return 0;
}
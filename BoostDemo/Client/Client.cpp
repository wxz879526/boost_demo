// Client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "boost/array.hpp"
#include "boost/asio.hpp"

int main()
{
	try
	{
		boost::asio::io_context io_ctx;
		boost::asio::ip::tcp::resolver resolver(io_ctx);
		boost::asio::ip::tcp::resolver::results_type endPoints = resolver.resolve("127.0.0.1"
			, "daytime");
		boost::asio::ip::tcp::socket socket(io_ctx);
		boost::asio::connect(socket, endPoints);

		for (;;)
		{
			boost::array<char, 128> buf;
			boost::system::error_code error;

			size_t len = socket.read_some(boost::asio::buffer(buf), error);

			if (error == boost::asio::error::eof)
				break;
			else if (error)
			{
				throw boost::system::system_error(error);
			}

			std::cout.write(buf.data(), len);
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	
	return 0;
}

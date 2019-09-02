// BoostDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include "boost/smart_ptr/make_shared_object.hpp"

#include "boost/log/sinks/text_ostream_backend.hpp"
#include "boost/log/sources/logger.hpp"

#include "boost/thread.hpp"
#include "boost/chrono.hpp"

#include "boost/filesystem.hpp"

// 设置过滤级别
void init()
{
	typedef boost::log::sinks::synchronous_sink<boost::log::sinks::text_ostream_backend> text_sinks;
	boost::shared_ptr<text_sinks> sink = boost::make_shared<text_sinks>();

	sink->locked_backend()->add_stream(boost::make_shared<std::ofstream>("sample.log"));

	boost::log::core::get()->add_sink(sink);
}

void wait(int seconds)
{
	boost::this_thread::sleep_for(boost::chrono::seconds{ seconds });
}

void thread()
{
	for (auto i = 0; i < 5; ++i)
	{
		wait(1);
		std::cout << i << std::endl;
	}
}

int main()
{
	try
	{
		boost::filesystem::path pat("D:\\1\\1.txt");
		boost::filesystem::path pat2("D:\\1\\2\\1.txt");

		boost::filesystem::copy_file(pat, pat2, boost::filesystem::copy_option::overwrite_if_exists);
		int j = 0;
	}
	catch (const boost::filesystem::filesystem_error& e)
	{
		auto jj = e.what();
		int j = 0;
	}


	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

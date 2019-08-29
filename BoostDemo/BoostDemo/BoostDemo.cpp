// BoostDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

// 设置过滤级别
void init()
{
	boost::log::add_file_log(boost::log::keywords::file_name="sample_%N.log",
		boost::log::keywords::rotation_size = 10 * 1024 * 1024,
		boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0,0,0),
		boost::log::keywords::format = "[%TimeStamp%]: %Message%");

	boost::log::core::get()->set_filter(
		boost::log::trivial::severity >= boost::log::trivial::error
	);
}

int main()
{
	init();

	// 调用这接口 [%TimeStamp%]: %Message% 才有效
	boost::log::add_common_attributes();

	BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
	BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
	BOOST_LOG_TRIVIAL(info) << "An informational severity message";
	BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
	BOOST_LOG_TRIVIAL(error) << "An error severity message";
	BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";

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

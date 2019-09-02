// BoostDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#define BOOST_THREAD_VERSION 5
#define BOOST_THREAD_USES_LOG
#define BOOST_THREAD_USES_LOG_THREAD_ID
#define BOOST_THREAD_QUEUE_DEPRECATE_OLD

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

#include "boost/thread/thread.hpp"
#include "boost/chrono/chrono.hpp"
#include "boost/thread/scoped_thread.hpp"

#include "boost/thread/detail/log.hpp"
#include "boost/thread/executors/basic_thread_pool.hpp"


void p1()
{
	BOOST_THREAD_LOG << boost::this_thread::get_id() << " P1" << BOOST_THREAD_END_LOG;
}

void p2()
{
	BOOST_THREAD_LOG << boost::this_thread::get_id() << " P2" << BOOST_THREAD_END_LOG;
}

void submit_some(boost::basic_thread_pool &tp)
{
	tp.submit(&p1);
	tp.submit(&p2);
	tp.submit(&p1);
	tp.submit(&p2);
	tp.submit(&p1);
	tp.submit(&p2);
	tp.submit(&p1);
	tp.submit(&p2);
	tp.submit(&p1);
	tp.submit(&p2);
	tp.submit(&p1);
	tp.submit(&p2);
	tp.submit(&p1);
	tp.submit(&p2);
	tp.submit(&p1);
	tp.submit(&p2);
	tp.submit(&p1);
	tp.submit(&p2);
	tp.submit(&p1);
	tp.submit(&p2);
	tp.submit(&p1);
	tp.submit(&p2);
	tp.submit(&p1);
	tp.submit(&p2);
	tp.submit(&p1);
	tp.submit(&p2);
	tp.submit(&p1);
	tp.submit(&p2);
	tp.submit([]() {
		BOOST_THREAD_LOG << "Hello World From Closure" << BOOST_THREAD_END_LOG;
	});
}

int main()
{
	BOOST_THREAD_LOG << boost::this_thread::get_id() << " <MAIN" << BOOST_THREAD_END_LOG;
	{
		try
		{
			boost::basic_thread_pool tp;
			submit_some(tp);
		}
		catch (const std::exception& e)
		{
			BOOST_THREAD_LOG << "ERROR " << e.what() << "" << BOOST_THREAD_END_LOG;
			return 1;
		}
		catch (...)
		{
			BOOST_THREAD_LOG << "ERROR " << "" << BOOST_THREAD_END_LOG;
			return 2;
		}
	}

	BOOST_THREAD_LOG << boost::this_thread::get_id() << " MAIN>" << BOOST_THREAD_END_LOG;

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

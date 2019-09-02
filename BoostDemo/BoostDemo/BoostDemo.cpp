// BoostDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <cmath>

#include "boost/variant2/variant.hpp"


class Rect
{
private:
	double width_, height_;

public:
	Rect(double width, double height)
		: width_(width)
		, height_(height)
	{

	}

	double Area() const
	{
		return width_ * height_;
	}
};

class Circle
{
private:
	double radius_;

public:
	Circle(double r)
		: radius_(r)
	{

	}

	double Area() const
	{
		return M_PI * radius_ * radius_;
	}
};

double total_area(const std::vector<boost::variant2::variant<Rect, Circle>> &v)
{
	double s = 0.0;
	for (const auto &p : v)
	{
		auto p1 = boost::variant2::get_if<0>(&p);
		s += boost::variant2::visit([](auto const &y) {return y.Area(); }, p);
	}

	return s;
}

int main()
{
	boost::variant2::variant<double, char, std::string> v1;
	v1 = "123";
	
	try
	{
		auto c = boost::variant2::get<2>(v1);
	}
	catch (const boost::variant2::bad_variant_access& e)
	{
		std::cout << e.what() << std::endl;
	}

	std::vector<boost::variant2::variant<Rect, Circle>> v;
	v.push_back(Circle(1.0));
	v.push_back(Rect(2.0, 3.0));

	std::cout << "Total area: " << total_area(v) << std::endl;

	return 0;
}
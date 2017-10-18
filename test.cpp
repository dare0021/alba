#include <iostream>
#include <math.h>
#include <list>
#include <cassert>
#include <limits>
#include <sstream>
#define PRINT(a) std::cout<< a <<"\n"

class Slicer
{
public:
	Slicer(uint from, uint to)
	{
		this->from = from;
		this->to = to;
	}

	list<T> slice(list<T> lst)
	{
		auto retval = {};
		auto fromIter = lst.begin();
		auto toIter = lst.begin();
		std::advance(fromIter, from);
		std::advance(toIter, to);
		std::copy(fromIter, toIter, retval.begin());
		return retval;
	}

private:
	uint from, to;
};

void test(double *t)
{
	*t = 3;
}

/// returns the exponent
double strip_mentissa(double val)
{
	val = val<0 ? -1 * val : val;
	int retval;
	frexp(val, &retval);
	return retval;
}

std::list<double> quantize(std::list<double> ary, int bits, double *scale)
{
	assert(std::numeric_limits<double>::is_iec559);
	double maxval = -1 * std::numeric_limits<double>::infinity();
	for (double v : ary)
	{
		double d = v<0 ? -1 * v : v;
		maxval = d>maxval ? d : maxval;
	}
	*scale = strip_mentissa(maxval) / float(1 << (bits - 2));
	std::list<double> retval = {};
	for (double v : ary)
	{
		retval.push_back(round(v / *scale));
	}
	return retval;
}

int main()
{
	std::list<double> iv = {1,-2,3.42};
	double x = 0;
	auto lst = quantize(iv, 8, &x);
	PRINT (x);
	for (auto i : lst)
	{
		PRINT(i);
	}
	auto s = Slicer(1,-2);
	PRINT (s.toString());
}


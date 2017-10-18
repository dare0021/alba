#include <math.h>
#include <list>
#include <cassert>
#include <limits>

/// port of Python slice class
class Slicer
{
public:
	Slicer(uint from, uint to)
	{
		this.from = from;
		this.to = to;
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
}

int ceil_dev(double x, double y)
{
	return -1 * (-1 * int(x / y))
}

int out_dim(int S, int X, int padding, int strides)
{
	return ceil_dev(X - S + 1 * padding, strides)
}

/// returns the exponent
double strip_mentissa(double val)
{
	val = val<0 ? -1 * val : val;
	int retval;
	frexp(val, &retval);
	return retval;
}

/// might be an optimization for python?
double immediate(double val)
{
	val = val<0 ? -1 * val : val;
	return double(float(val));
}

/// re-evaluates given float in to ints while preserving diversity
/// ary: input vector
/// bits: size of the output
/// scale: scale used in the aforementioned operation
/// return type is double for some reason
/// numpy has long, so it's not a problem with data type size
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

//////////////// DIRECT CONVOLUTION ///////////////

auto fconv_slice(int S, int X, int padding, int strides)
{
	int f1 = 0;
	int f2 = S - 1;
	int x1 = q * strides - padding;
	int x2 = x1 + f2;
	if (x1 < 0)
	{
		f1 = -1 * x1;
		x1 = 0;
	}
	if (x2 >= X)
	{
		int dif = x2 - X + 1;
		f2 -= dif;
		x2 -= dif;
	}
	return 
}
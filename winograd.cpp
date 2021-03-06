// NOT DONE

#include <math.h>
#include <vector>
#include <cassert>
#include <limits>
#include <tuple>

#include "FourD.h"

/// port of Python slice class
template <class T> class Slicer
{
public:
	Slicer(uint from, uint to)
	{
		this->from = from;
		this->to = to;
	}

	std::vector<T> slice(std::vector<T> lst)
	{
		auto retval = {};
		auto fromIter = lst.begin();
		auto toIter = lst.begin();
		std::advance(fromIter, from);
		std::advance(toIter, to);
		std::copy(fromIter, toIter, std::back_inserter(retval));
		return retval;
	}

	std::vector<T> destructiveSlice(std::vector<T> *lst)
	{
		auto fromIter = lst->begin();
		auto toIter = lst->begin();
		std::advance(fromIter, from);
		std::advance(toIter, to);
		lst->erase(lst->begin(), fromIter);
		lst->erase(toIter, lst->end());
		return *lst;
	}

private:
	uint from, to;
};

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
std::vector<double> quantize(std::vector<double> ary, int bits, double *scale)
{
	assert(std::numeric_limits<double>::is_iec559);
	double maxval = -1 * std::numeric_limits<double>::infinity();
	for (double v : ary)
	{
		double d = v<0 ? -1 * v : v;
		maxval = d>maxval ? d : maxval;
	}
	*scale = strip_mentissa(maxval) / float(1 << (bits - 2));
	std::vector<double> retval = {};
	for (double v : ary)
	{
		retval.push_back(round(v / *scale));
	}
	return retval;
}

//////////////// DIRECT CONVOLUTION ///////////////

std::tuple<Slicer<double>, Slicer<double>, int> fconv_slice(int S, int X, int padding, int strides)
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
	return std::make_tuple(Slicer(f1, f2 + 1), Slicer(x1, x2 + 1), f2 - f1 + 1);
}

auto xprop_winograd(FourD<double> I, FourD<double> F, FourD<double> O, FourD<double> padding, bool minimal = false, bool backward = false)
{
	if (backward)
	{
		F = FourD<double>(F);
		F.reverse(1);
		F.reverse(2);
		F.transpose();
		auto data = padding.exposeInnards();
		for (int i=0; i<data->size(); i++)
		{
			(*data)[i] = 2 - (*data)[i];
		}
	}

	auto Ishape = I.dims();
	auto Oshape = O.dims();
	int C = Ishape[0];
	int Y = Ishape[1];
	int X = Ishape[2];
	int N = Ishape[3];
	int K = Oshape[0];
	int P = Oshape[1];
	int Q = Oshape[2];
	assert(N == Oshape[3]);

	int B = 2;
	int D = B + 2;
	int Yw = ceil_dev(P, B);
	int Xw = ceil_dev(Q, B);

	auto Fw = FourD<double>(D, D, C, K);
	auto Iw = SixD<double>(D, D, C, Yw, Xw, N);	??
	auto Mw = SixD<double>(D, D, K, Yw, Xw, N);	??

	for (int c=0; c < C; c++)
	{
		for (int k=0; k < K; k++)
		{
			auto Fwi = Fw[:, :, c, k];	??
			auto Fi = F[c, :, :, k];	??
			trans_F_2x2_3x3(Fwi, Fi, minimal);	??
		}
	}
}
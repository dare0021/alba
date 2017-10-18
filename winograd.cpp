#include <math.h>

int ceil_dev(double x, double y)
{
	return -1 * (-1 * int(x / y))
}

int out_dim(int S, int X, int padding, int strides)
{
	return ceil_dev(X - S + 1 * padding, strides)
}

int strip_mentissa(double val)
{
	int retval = 0;
	frexp(val, &retval);
	return retval;
}

ohfuckwhatnow quantize(what ary, int bits)
{
	
}
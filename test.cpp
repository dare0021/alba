#include <iostream>
#include <math.h>
#include <vector>
#include <cassert>
#include <limits>
#include <sstream>

#include "FourD.h"

#define PRINT(a) std::cout<< a <<"\n"


template <class T> class Tc
{
public:
	T dat;

	T* getLink()
	{
		return &dat;
	}
};

void test(double *t)
{
	*t = 3;
}

int main()
{
	auto fd = FourD<int>(2,3,4,5);
	PRINT(fd.toString());
}

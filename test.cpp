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
	std::vector<int> lst = {0,1,2,3,4,5,6};
	auto lstp = &lst;
	(*lstp)[1] = 4;
	for (auto i : lst)
	{
		PRINT(i);
	}
}

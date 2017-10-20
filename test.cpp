#include <iostream>
#include <math.h>
#include <vector>
#include <cassert>
#include <limits>
#include <sstream>

#define PRINT(a) std::cout<< a <<"\n"
#include "FourD.h"



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
	fd.put(1,1,1,0, 24);
	for (int i=0; i<5; i++)
	{
		fd.put(0,0,0,i, i+1);
		fd.put(1,0,1,4-i, i+1);
	}
	PRINT(fd.toString());
	fd.reverse(2);
	PRINT(fd.toString());
}

#include <iostream>
#include <math.h>
#include <vector>
#include <cassert>
#include <limits>
#include <sstream>
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
	std::vector<int*> a = {&lst[0], &lst[1]};
	std::vector<int*> b = {&lst[5], &lst[6]};
	std::swap(*a[0], *b[0]);
	std::swap(*a[1], *b[1]);
	for (auto i : lst)
	{
		PRINT(i);
	}
}

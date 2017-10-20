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
	auto lstp = &lst;
	auto lst2 = std::vector<int>(*lstp);
	lst2.push_back(7);
	lst2[6] = 8;
	for (auto i : lst)
	{
		PRINT(i);
	}
}

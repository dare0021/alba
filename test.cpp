#include <iostream>
#include <math.h>
#include <vector>
#include <cassert>
#include <limits>
#include <sstream>
#define PRINT(a) std::cout<< a <<"\n"

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
		std::vector<T> retval = {};
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

void test(double *t)
{
	*t = 3;
}

int main()
{
	std::vector<double> iv = {1,-2,3.42};
	auto s = Slicer<double>(0,2);
	s.destructiveSlice(&iv);
	for (auto i : iv)
		PRINT(i);
}


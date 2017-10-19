#include <iostream>
#include <math.h>
#include <vector>
#include <cassert>
#include <limits>
#include <sstream>
#define PRINT(a) std::cout<< a <<"\n"

template <class T> class FourD
{
public:
	FourD(int x, int y, int z, int t)
	{
		data.resize(x * y* z * t);
		zStride = t;
		yStride = t * z;
		xStride = t * z * y;
		this->x = x;
		this->y = y;
		this->z = z;
		this->t = t;
	}

	T get(int x, int y, int z, int t)
	{
		assert(validateIterators(x, y, z, t));
		return data[x * xStride + y * yStride + z * zStride + t];
	}

	void put(int x, int y, int z, int t, T val)
	{
		assert(validateIterators(x, y, z, t));
		data[x * xStride + y * yStride + z * zStride + t] = val;
	}

	FourD<T> &operator+=(T rhs)
	{
		for (int i=0; i<data.size(); i++)
			data[i] += rhs;
		return *this;
	}

	FourD<T> &operator+(T rhs)
	{
		*this += rhs;
		return *this;
	}

	FourD<T> &operator-=(T rhs)
	{
		for (int i=0; i<data.size(); i++)
			data[i] -= rhs;
		return *this;
	}

	FourD<T> &operator-(T rhs)
	{
		*this -= rhs;
		return *this;
	}

	FourD transpose()
	{

	}

	bool validateIterators(int x, int y, int z, int t)
	{
		if(x < 0)
			return false;
		if(y < 0)
			return false;
		if(z < 0)
			return false;
		if(t < 0)
			return false;
		if(x >= this->x)
			return false;
		if(y >= this->y)
			return false;
		if(z >= this->z)
			return false;
		if(t >= this->t)
			return false;
		return true;
	}

	// on one hand, this is a clusterfuck
	// on the other hand, why not?
	std::string toString()
	{
		std::string retval = "[";
		for (int xi=0; xi < x; xi++)
		{
			retval += "[";
			for (int yi=0; yi < y; yi++)
			{
				retval += "[";
				for (int zi=0; zi < z; zi++)
				{
					retval += "[";
					for (int ti=0; ti < t-1; ti++)
					{
						retval += "'" + std::to_string(get(xi, yi, zi, ti)) + "', ";
					}
					retval += "'" + std::to_string(get(xi, yi, zi, t-1));
					retval += "]";
				}
				retval += "]";
			}
			retval += "]";
		}
		retval += "]";
		return retval;
	}

private:
	std::vector<T> data = {};
	int x, y, z, t;
	int xStride, yStride, zStride;
};

void test(double *t)
{
	*t = 3;
}

int main()
{
	auto fd = FourD<double>(2,2,2,2);
	fd.put(0,0,1,1, 2.9);
	fd = fd + 1;
	PRINT(fd.toString());
}

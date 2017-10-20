#include <cassert>
#include <algorithm>

template<typename T>
FourD<T>::FourD(int x, int y, int z, int t)
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

template<typename T>
FourD<T>::FourD(const FourD<T> &fd)
{
	auto size = fd.size();
	int x = std::get<0>(size);
	int y = std::get<1>(size);
	int z = std::get<2>(size);
	int t = std::get<3>(size);
	data = std::vector<T>(*fd.exposeInnards());
	zStride = t;
	yStride = t * z;
	xStride = t * z * y;
	this->x = x;
	this->y = y;
	this->z = z;
	this->t = t;	
}

template<typename T>
T FourD<T>::get(int x, int y, int z, int t) const
{
	assert(validateIterators(x, y, z, t));
	return data[x * xStride + y * yStride + z * zStride + t];
}

template<typename T>
void FourD<T>::put(int x, int y, int z, int t, T val)
{
	assert(validateIterators(x, y, z, t));
	data[x * xStride + y * yStride + z * zStride + t] = val;
}

template<typename T>
FourD<T> &FourD<T>::operator+=(T rhs)
{
	for (int i=0; i<data.size(); i++)
		data[i] += rhs;
	return *this;
}

template<typename T>
FourD<T> &FourD<T>::operator+(T rhs)
{
	*this += rhs;
	return *this;
}

template<typename T>
FourD<T> &FourD<T>::operator-=(T rhs)
{
	for (int i=0; i<data.size(); i++)
		data[i] -= rhs;
	return *this;
}

template<typename T>
FourD<T> &FourD<T>::operator-(T rhs)
{
	*this -= rhs;
	return *this;
}

// template<typename T>
// FourD<T> &FourD<T>::operator*(FourD<T> rhs)
// {
// 	assert(validateMatmul(this->size(), rhs.size()));
// 	??
// }

// template<typename T>
// FourD<T> FourD<T>::transpose()
// {
// 	??
// }

// returns by reference elements in [from * stride, to * stride)
template<typename T>
std::vector<T*> FourD<T>::getSubset(int from, int to, int stride)
{		
	std::vector<T*> retval = {};
	from *= stride;
	to *= stride;
	for (int i=from; i < to; i++)
	{
		retval.push_back(&(data[i]));
	}
	return retval;
}

template<typename T>
void FourD<T>::massSwap(std::vector<T*> a, std::vector<T*> b)
{
	assert(a.size() == b.size());
	for (int i=0; i<a.size(); i++)
	{
		std::swap(*a[i], *b[i]);
	}
}

template<typename T>
std::vector<T*> FourD<T>::getX(int from, int to)
{
	return getSubset(from, to, xStride);
}

template<typename T>
std::vector<T*> FourD<T>::getY(int from, int to)
{
	return getSubset(from, to, yStride);
}

template<typename T>
std::vector<T*> FourD<T>::getZ(int from, int to)
{
	return getSubset(from, to, zStride);
}

/// 0is x axis, etc
template<typename T>
void FourD<T>::reverse(int axis)
{
	assert(0 <= axis && axis < 4);
	if (axis == 3)
	{
		auto fromIter = data.begin();
		auto toIter = data.begin();
		for (std::advance(toIter, zStride);
			 std::distance(toIter, data.end()) >= 0;
			 std::advance(fromIter, zStride), std::advance(toIter, zStride))
		{
			std::reverse(fromIter, toIter);
		}
	}
	else
	{
		int strides[3] = {xStride, yStride, zStride};
		int stride = strides[axis];
		int sizes[4] = {x, y, z, t};
		int size = sizes[axis];
		int numReversals = size / 2;
		for (int i=0, j=size; i<numReversals; i++, j--)
		{
			massSwap(getSubset(i, i+1, stride), getSubset(j-1, j, stride));
		}
	}
}

template<typename T>
bool FourD<T>::validateMatmul(std::tuple<int, int, int, int> asize, std::tuple<int, int, int, int>  bsize) const
{
	int a0 = std::get<0>(asize);
	int a1 = std::get<1>(asize);
	int a2 = std::get<2>(asize);
	int a3 = std::get<3>(asize);
	int b0 = std::get<0>(bsize);
	int b1 = std::get<1>(bsize);
	int b2 = std::get<2>(bsize);
	int b3 = std::get<3>(bsize);

	return true;
	// return ??
}

template<typename T>
bool FourD<T>::validateIterators(int x, int y, int z, int t) const
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
template<typename T>
std::string FourD<T>::toString() const
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

template<typename T>
const std::vector<T>* FourD<T>::exposeInnards() const
{
	return &data;
}

template<typename T>
std::tuple<int, int, int, int> FourD<T>::size() const
{
	return std::make_tuple(x,y,z,t);
}
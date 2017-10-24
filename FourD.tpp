#include <cassert>
#include <algorithm>

template<typename T>
FourD<T>::FourD(int x, int y, int z, int t)
{
	data.resize(x * y * z * t);
	strides = {t*z*y, t*z, t};
	dims = {x, y, z, t};
}

FourD<T>::FourD(int x, int y, int z, int t, int u, int v)
{
	data.resize(x * y * z * t * u * v);
	strides = {y*z*t*u*v, z*t*u*v, t*u*v, u*v, v};
	dims = {x, y, z, t, u, v};
}

template<typename T>
FourD<T>::FourD(const FourD<T> &fd)
{
	dims = fd.getDims();
	strides = fd.getStrides();
	data = std::vector<T>(*fd.exposeInnards());
}

template<typename T>
T FourD<T>::get(std::vector<int> loc) const
{
	assert(validateIterators(loc));
	return data[getPosition(loc)];
}

template<typename T>
void FourD<T>::put(std::vector<int> loc, T val)
{
	assert(validateIterators(loc));
	data[getPosition(loc)] = val;
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
// 	assert(validateMatmul(this->shape(), rhs.shape()));
// 	??
// }

/// puts items from (a,b,c,d) to (d,c,b,a)
template<typename T>
void FourD<T>::transpose()
{
	RETROFIT TO RUN FOR 6D

	std::vector<bool> alreadySwapped = {};
	alreadySwapped.resize(x * y * z * t);
	int newX = t;
	int newY = z;
	int newZ = y;
	int newT = x;
	int newstrides[0] = newT * newZ * newY;
	int newstrides[1] = newT * newZ;
	int newstrides[2] = newT;
	for (int xi=0; xi < x; xi++)
	{
		for (int yi=0; yi < y; yi++)
		{
			for (int zi=0; zi < z; zi++)
			{
				for (int ti=0; ti < t-1; ti++)
				{
					if (alreadySwapped[xi * strides[0] + yi * strides[1] + zi * strides[2] + ti])
					{
						continue;
					}
					std::swap(data[xi * strides[0] + yi * strides[1] + zi * strides[2] + ti],
							  data[ti * newstrides[0] + zi * newstrides[1] + yi * newstrides[2] + xi]);
				}
			}
		}
	}
	std::swap(x, t);
	std::swap(y, z);
	strides[2] = newstrides[2];
	strides[1] = newstrides[1];
	strides[0] = newstrides[0];
}

/// returns by reference elements in [from * stride, to * stride)
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

/// 0 is x axis, etc
template<typename T>
void FourD<T>::reverse(int axis)
{
	RETROFIT TO RUN FOR 6D

	assert(0 <= axis && axis < 4);
	if (axis == 3)
	{
		auto fromIter = data.begin();
		auto toIter = data.begin();
		for (std::advance(toIter, strides[2]);
			 std::distance(toIter, data.end()) >= 0;
			 std::advance(fromIter, strides[2]), std::advance(toIter, strides[2]))
		{
			std::reverse(fromIter, toIter);
		}
		return;
	}
	int strides[3] = {strides[0], strides[1], strides[2]};
	int stride = strides[axis];
	int sizes[3] = {x, y, z};
	int size = sizes[axis];
	int numReversals = size / 2;
	int offsetTarget = 1;
	for (int axisCopy=axis; axisCopy > 0; axisCopy--)
	{
		offsetTarget *= sizes[axisCopy-1];
	}
	offsetTarget = offsetTarget<1 ? 1 : offsetTarget;
	for (int offset=0; offset < offsetTarget; offset++)
	{
		int offsetAmt = offset * size;
		for (int i=offsetAmt, j=size+offsetAmt; i<numReversals+offsetAmt; i++, j--)
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
bool FourD<T>::validateIterators(std::vector<int> loc) const
{
	for (int i=0; i<loc.size(); i++)
	{
		if (loc[i] < 0)
			return false;
		if (loc[i] >= dims[i])
			return false;
	}
	return true;
}

// on one hand, this is a clusterfuck
// on the other hand, why not?
template<typename T>
std::string FourD<T>::quadToString(std::vector<int> locPrefix) const
{
	int DMinus4 = dims.size() - 4;
	int x = dims[DMinus4];
	int y = dims[DMinus4 + 1];
	int z = dims[DMinus4 + 2];
	int t = dims[DMinus4 + 3];
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
				retval += "'" + std::to_string(get(xi, yi, zi, t-1)) + "'";
				retval += "]";
			}
			retval += "]\t";
		}
		retval += "]\n";
	}
	retval += "]";
	return retval;
}

template<typename T>
const std::vector<T>* FourD<T>::exposeInnards() const
{
	return &data;
}

/// return copy to prevent skullduggery
template<typename T>
std::vector<int> FourD<T>::getDims() const
{
	return std::vector<int>(dims);
}

/// return copy to prevent skullduggery
template<typename T>
std::vector<int> FourD<T>::getStrides() const
{
	return std::vector<int>(strides);
}

template<typename T>
int FourD<T>::getPosition(std::vector<int> loc) const
{
	assert(validateIterators(loc));
	int pos = loc[-1];
	for (int i=0; i<strides.size(); i++)
	{
		pos += loc[i] * strides[i];
	}
}
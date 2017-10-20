#include <vector>
#include <cassert>

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

	FourD(FourD fd)
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

	FourD<T> &operator*(FourD<T> rhs)
	{
		assert(validateMatmul(this->size(), rhs.size()));
		??
	}

	FourD<T> transpose()
	{
		??
	}

	// returns by reference elements in [from * stride, to * stride)
	std::vector<T*> getSubset(int from, int to, int stride)
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

	void massSwap(std::vector<T*> a, std::vector<T*> b)
	{
		assert(a.size() == b.size());
		for (int i=0; i<a.size(); i++)
		{
			std::swap(*a[i], *b[i]);
		}
	}

	std::vector<T*> getX(int from, int to)
	{
		return getSubset(from, to, xStride);
	}

	std::vector<T*> getY(int from, int to)
	{
		return getSubset(from, to, yStride);
	}

	std::vector<T*> getZ(int from, int to)
	{
		return getSubset(from, to, zStride);
	}

	/// 0 is x axis, etc
	void reverse(int axis)
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
			int stride = selectionBuffer[axis];
			int sizes[4] = {x, y, z, t};
			int size = sizes[axis];
			int numReversals = size / 2;
			for (int i=0, j=size; i<numReversals; i++, j--)
			{
				massSwap(getSubset(i, i+1, stride), getSubset(j-1, j, stride));
			}
		}
	}

	bool validateMatmul(std::tuple<int, int, int, int> asize, std::tuple<int, int, int, int>  bsize)
	{
		a0 = std::get<0>(asize);
		a1 = std::get<1>(asize);
		a2 = std::get<2>(asize);
		a3 = std::get<3>(asize);
		b0 = std::get<0>(bsize);
		b1 = std::get<1>(bsize);
		b2 = std::get<2>(bsize);
		b3 = std::get<3>(bsize);

		return ??
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

	&std::vector<T> exposeInnards()
	{
		return &data;
	}

	std::tuple<int, int, int, int> size()
	{
		return std::make_tuple(x,y,z,t);
	}

private:
	std::vector<T> data = {};
	int x, y, z, t;
	int xStride, yStride, zStride;
};
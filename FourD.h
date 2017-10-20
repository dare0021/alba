#include <vector>
#include <string>
#include <tuple>

template <class T> class FourD
{
public:
	FourD<T>(int x, int y, int z, int t);

	FourD<T>(const FourD<T> &fd);

	T get(int x, int y, int z, int t) const;

	void put(int x, int y, int z, int t, T val);

	FourD<T> &operator+=(T rhs);

	FourD<T> &operator+(T rhs);

	FourD<T> &operator-=(T rhs);

	FourD<T> &operator-(T rhs);

	// FourD<T> &operator*(FourD<T> rhs);

	void transpose();

	std::vector<T*> getSubset(int from, int to, int stride);

	void massSwap(std::vector<T*> a, std::vector<T*> b);

	std::vector<T*> getX(int from, int to);

	std::vector<T*> getY(int from, int to);

	std::vector<T*> getZ(int from, int to);

	void reverse(int axis);

	bool validateMatmul(std::tuple<int, int, int, int> asize, std::tuple<int, int, int, int>  bsize) const;

	bool validateIterators(int x, int y, int z, int t) const;

	std::string toString() const;

	const std::vector<T>* exposeInnards() const;

	std::tuple<int, int, int, int> shape() const;

private:
	std::vector<T> data = {};
	int x, y, z, t;
	int xStride, yStride, zStride;
};

// template classes are weird
#include "FourD.tpp"
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

	void reverse(int axis);

	bool validateMatmul(std::tuple<int, int, int, int> asize, std::tuple<int, int, int, int>  bsize) const;

	bool validateIterators(int x, int y, int z, int t) const;

	std::string toString() const;

	const std::vector<T>* exposeInnards() const;

	std::vector<int> getDims() const;

	std::vector<int> getStrides() const;

private:
	std::vector<T> data = {};
	std::vector<int> dims;
	std::vector<int> strides;
};

// template classes are weird
#include "FourD.tpp"
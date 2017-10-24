#include <vector>
#include <string>
#include <tuple>

template <class T> class FourD
{
public:
	FourD<T>(int x, int y, int z, int t);

	FourD<T>(const FourD<T> &fd);

	T get(std::vector<int> loc) const;

	void put(std::vector<int> loc, T val);

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

	bool validateIterators(std::vector<int> loc) const;

	std::string toString() const;

	const std::vector<T>* exposeInnards() const;

	std::vector<int> getDims() const;

	std::vector<int> getStrides() const;

private:
	std::string quadToString(std::vector<T>::iterator fromIter, std::vector<T>::iterator toIter) const;

	int getPosition(std::vector<T> loc) const;

	std::vector<T> data = {};
	std::vector<int> dims;
	std::vector<int> strides;
};

// template classes are weird
#include "FourD.tpp"
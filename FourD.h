#include <vector>
#include <string>
#include <tuple>

template <class T> class FourD
{
public:
	FourD(int x, int y, int z, int t);

	FourD(const FourD<T> &fd);

	T get(int x, int y, int z, int t);

	void put(int x, int y, int z, int t, T val);

	FourD<T> &operator+=(T rhs);

	FourD<T> &operator+(T rhs);

	FourD<T> &operator-=(T rhs);

	FourD<T> &operator-(T rhs);

	// FourD<T> &operator*(FourD<T> rhs);

	// FourD<T> transpose();

	std::vector<T*> getSubset(int from, int to, int stride);

	void massSwap(std::vector<T*> a, std::vector<T*> b);

	std::vector<T*> getX(int from, int to);

	std::vector<T*> getY(int from, int to);

	std::vector<T*> getZ(int from, int to);

	void reverse(int axis);

	bool validateMatmul(std::tuple<int, int, int, int> asize, std::tuple<int, int, int, int>  bsize);

	bool validateIterators(int x, int y, int z, int t);

	std::string toString();

	std::vector<T>* exposeInnards();

	std::tuple<int, int, int, int> size();

private:
	std::vector<T> data = {};
	int x, y, z, t;
	int xStride, yStride, zStride;
};
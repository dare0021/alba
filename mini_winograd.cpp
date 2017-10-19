#include <vector>
#include <cassert>

template <class T> class FourD
{
public:
	FourD(uint x, uint y, uint z, uint t)
	{
		data.resize(x * y* z * t);
	}

private:
	std::vector<T> data = {};
}

void xprop_winograd(vector<int> I, vector<int> F, vector<int> O, vector<int> padding, bool minimal = false, bool backward = false)
{
	if (backward)
	{
		for (int i=0; i<padding.size(); i++)
		{
			padding[i] = 2 - padding[i];
		}
	}
}
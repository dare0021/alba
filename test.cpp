#include <iostream>
#include <math.h>
#define PRINT(a) std::cout<< a <<"\n"


int test(double val)
{
	int retval = 0;
	frexp(val, &retval);
	return retval;
}

int main()
{
	PRINT (test(349.34873));
}


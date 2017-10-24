#include <iostream>
#include <math.h>
#include <vector>
#include <cassert>
#include <limits>
#include <sstream>
#include <cblas.h>

#define PRINT(a) std::cout<< a <<"\n"
// #include "FourD.h"



template <class T> class Tc
{
public:
	T dat;

	T* getLink()
	{
		return &dat;
	}
};

void test(double *t)
{
	*t = 3;
}

int main()
{
	double A[6] = {1.0,2.0,1.0,-3.0,4.0,-1.0};         
	double B[6] = {1.0,2.0,1.0,-3.0,4.0,-1.0};  
	double C[9] = {.5,.5,.5,.5,.5,.5,.5,.5,.5}; 
	cblas_dgemm(CblasColMajor, CblasNoTrans, CblasTrans,3,3,2,1,A, 3, B, 3,2,C,3);

	for (int i=0; i<9; i++)
	{
		PRINT(C[i]);
	}

	// auto fd = FourD<int>(2,3,4,5);
	// fd.put(1,1,1,0, 24);
	// for (int i=0; i<5; i++)
	// {
	// 	fd.put(0,0,0,i, i+1);
	// 	fd.put(1,0,1,4-i, i+1);
	// }
	// PRINT(fd.toString());
	// fd.transpose();
	// PRINT(fd.toString());
}

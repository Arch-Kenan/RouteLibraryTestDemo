#pragma once
#include <math.h>
#include <iostream>




double newtonSqrt(double x)
{
	if (x <0)
	{
		return 0;
	}
	double res;
	double lastRes = x /10;
	do 
	{
		res = lastRes;
		lastRes = (res + x / res) / 2;
	} while (abs(res - lastRes) > FLT_MIN);
	return lastRes;
}

//DWORD t1 = clock();
//for (size_t i = 0; i < 10000; i++)
//{
//	newtonSqrt(999999);
//}
//DWORD t2 = clock();
//std::cout << t2 - t1 << "\n";
//
//t1 = clock();
//for (int j = 0; j < 10000; j++)
//{
//	bisectionSqrt(999999);
//}
//t2 = clock();
//std::cout << t2 - t1 << std::endl;


//double bisectionSqrt(double x)
//{
//	if ( x<0)
//	{
//		return 0;
//	}
//	double last;
//	double low = 0, up = x;
//	double mid = (low + up) / 2;
//	do 
//	{
//		if (mid*mid >x)
//		{
//			up = mid;
//		}
//		else
//		{
//			low = mid;
//		}
//		last = mid;
//		mid = (up + low) / 2;
//
//	} while ( abs(mid - last)> FLT_MIN );
//	return mid;
//}

double bisectionSqrt(double x)
{
	if (x < 0)
	{
		return 0;
	}
	double low = 0, hi = x;
	double mid = (low + hi) / 2;
	double res;
	do
	{
		if (mid*mid > x)
		{
			hi = mid;
		}
		else
		{
			low = mid;
		}
		res = mid;
		mid = (low + hi) / 2;
	} while (abs(res - mid) > FLT_MIN);
	return mid;
}
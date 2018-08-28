#pragma once
#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

int count1= 0;


int  fib1(int n)
{
	if (n == 0 || n == 1)
	{
		return 1;
	}
	else
	{
		return fib1(n - 1) + fib1(n - 2);
	}
}


int fib2(vector<int>& arr, int n)
{
	++count1;
	std::cout << count1 << endl;
	if (n == 0 || n == 1)
	{
		return 1;
	}
	if (arr[n] == -1)
	{
		arr[n] = fib2(arr, n - 1) + fib2(arr, n - 2);
	}
	return arr[n];

}
//int n = 20;
//std::vector<int>   memo = std::vector<int>(n + 1, -1);
//DWORD t1 = clock();
//int res = fib(memo, n);
//DWORD  t2 = clock();
//std::cout << (t2 - t1) / CLOCKS_PER_SEC << "   " << res << endl;


void hanoiMove(int n, int num, char source, char buffer, char target)
{
	++count1;
	std::cout << count1 << endl;
	if (n == 1)
	{
		std::cout <<"hanNumber:"<< num<<"    form:" << source << "   move:  " << target << std::endl;
		return;
	}
	else
	{
		hanoiMove(n - 1,num-1, source, target, buffer);
		hanoiMove(1, num, source, buffer, target);
		hanoiMove(n - 1,num-1, buffer, source, target);
	}
}


int fib3(int n)
{
	std::vector<int>  memo(n + 1, -1);
	memo[0] = 1;
	memo[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		memo[i] = memo[i - 1] + memo[i - 2];
	}
	return memo[n];
}






int calcWays1(vector<int>& arr, int n)
{
	if (n ==1 || n == 0 )
	{
		return 1;
	}
	if (n == 2)
	{
		return 2;
	}
	if (arr[n] == -1)
	{
		arr[n] = calcWays1(arr, n - 1) + calcWays1(arr, n - 2);
	}
	return arr[n];
}


int calcWays2(vector<int>& arr, int n)
{
	if (n< 0)
	{
		return 0;
	}
	arr[0] = 0;
	arr[1] = 1;
	arr[2] = 2;
	for (int i = 3; i <=  n; i++)
	{
		arr[i] = arr[i - 1] + arr[i - 2];
	}
	return arr[n];
}




int max3(int a, int b, int c) {
	return max(a, max(b, c));
}


//int breakInteger(int n) {
//
//	if (n == 1)
//		return 1;
//
//	int res = -1;
//	for (int i = 1; i <= n - 1; i++)
//		res = max3(res, i*(n - i), i * breakInteger(n - i));
//	return res;
//}

int breakInteger1(int n)
{
	if (n == 1)
	{
		return 1;
	}
	int res = -1;
	for (int i = 1; i < n; i++)
	{
		res = max3(res, i*(n - i), i*breakInteger1(n - i));
	}
	return res;
}


int breakInteger2(int n)
{
	if (n == 1)
	{
		return 1;
	}
	int res = -1;
	for (int i = 1; i < n; i++)
	{
		res = max( i * (n - i), i * breakInteger2(n - i));
	}
	return res;
}

int breakInteger3(int n)
{
	if (n == 1)
	{
		return 1;
	}
	int res = -1;
	for (int i = 1; i < n; i++)
	{
		res = max(res, i*breakInteger3(n - i));
	}
	return res;
}


int breakInteger4(std::vector<int>& arr, int n)
{
	if (n == 1)
	{
		return 1;
	}
	int res = 0;
	//arr[1] = 1;
	if (arr[n] == -1)
	{
		for (int i = 1; i < n; i++)
		{
			if (i == 1)
			{
				res = n;
			}
			res = max(res, i * breakInteger4(arr, n - i));
		}
		arr[n] = res;
	}
	return arr[n];
}



int breakInteger5(std::vector<int>& memo, int n) {

	if (n == 1)
		return 1;

	if (memo[n] != -1)
		return memo[n];

	int res = -1;
	for (int i = 1; i < n; i++)
		res = max3(res, i*(n - i), i * breakInteger5(memo, n - i));
	memo[n] = res;
	return res;
}


int breakInteger6(std::vector<int>& memo, int n) {

	if (n == 1)
		return 1;

	if (memo[n] != -1)
		return memo[n];

	int res = -1;
	for (int i = 1; i < n; i++)
	{
		if (i == 1)
		{
			res = n;
		}
		res = max(res, i * breakInteger6(memo, n - i));
	}
	memo[n] = res;
	return res;
}



int countNum1 = 0;
int breakInteger7(std::vector<int>& arr, int n)
{
	if (n == 1)
	{
		return 1;
	}
	if (arr[n] != -1)
	{
		return arr[n];
	}
	int res = 0;
	int b = 0;
	int devideNum = 0;
	for (int i = 0; i < n; i++)
	{
		if (i != 0)
		{
			b = i * breakInteger7(arr, n - i);
		}
		else
		{
			b = n;
		}
		if (res < b)
		{
			res = b;
			devideNum = i;
		}
		/*res = max(res, breakInteger7(arr, n - i));*/
	}
	countNum1++;
	printf("NO%d = %d \n", countNum1, devideNum);
	arr[n] = res;
	return res;
}


int breakInteger8(std::vector<int>& arr, int n)
{
	int i = 0;
	arr[1] = 1;
	int res = 0;
	//int a = 0;
	for (int i = 2; i <= n; i++)
	{
		for (int j = 1; j <i; j++)
		{
			if (j == 1)
			{
				res = i;
			}
			/*a = j * arr[i - j];*/
			res = max(res, j*arr[i - j]);
		}
		arr[i] = res;
	}
	return arr[n];
}
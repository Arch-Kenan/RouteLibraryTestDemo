#pragma once
#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

int count1= 0;
;
int fib(vector<int>& arr, int n)
{
	++count1;
	std::cout << count1 << endl;
	if (n == 0 || n == 1)
	{
		return 1;
	}
	if (arr[n] == -1)
	{
		arr[n] = fib(arr,n - 1) + fib(arr,n - 2);
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

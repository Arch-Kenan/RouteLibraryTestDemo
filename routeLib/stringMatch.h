#pragma once
#include "stdafx.h"
#include <iostream>

int testKMP(const char* source, const char* target);
void makeNext(const char* arr, const int size, int result[]);

//test file
//std::ifstream   file("../testList.txt");
//std::istreambuf_iterator<char> beg(file), end;
//if (file)
//{
//	std::string   fileStr(beg, end);
//	
//	const char* arr = "HorizontalCurveRouteData";

//	std::cout << fileStr.substr(fileStr.find(arr), 22);
//}

//file.close();

void bbstest(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		int flag = true;
		for (int j = 1; j < size - i; j++)
		{
			if (arr[j - 1] > arr[j])
			{
				int temp = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = temp;
				flag = false;
			}
		}
		if (flag)
		{
			break;
		}

	}
}


void sStest(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		int min = i;
		for (int j = i + 1; j < size; j++)
		{
			if (arr[j] < arr[min])
			{
				min = j;
			}
		}
		if (i != min)
		{
			int temp = arr[min];
			arr[min] = arr[i];
			arr[i] = temp;
		}
	}
}


void insertTest(int arr[], int size)
{
	for (int i = 1; i < size; i++)
	{
		for (int j = i; j > 0; j--)
		{
			if (arr[j - 1] > arr[j])
			{
				int temp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = temp;
			}
		}
	}
}

#pragma once

#include "stdafx.h"
#include <vector>

using namespace std;

void   bubblesort(int arr[], int size)
{
	bool flag = false;
	for (int i = 1; i < size; i++)
	{
		flag = true;
		for (int j = 0; j < size - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				flag = false;
				std::swap(arr[j], arr[j + 1]);
			}
		}
		if (flag = true)
		{
			break;
		}
	}
}


int find(int arr[], int low, int high)
{
	int temp = arr[low];
	while (low < high)
	{	
		while (low < high && arr[high] > temp)
			high--;
		if (low < high)
			arr[low++] = arr[high];
		while (low < high && arr[low] < temp)
			low++;
		if (low < high)
			arr[high--] = arr[low];
	}
	arr[low] = temp;
	return low;
}


void  quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		int pivot = find(arr, low, high);
		quickSort(arr, low, pivot - 1);
		quickSort(arr, pivot + 1, high);
	}
}





int findIndex(int* arr, int low, int high)
{
	int pivot = arr[low];
	while (low < high)
	{
		while (low < high && arr[high] >= pivot)
		{
			--high;
		}

		if (low < high)
		{
			cout << "high移动到low的index：" << high << "  " << low << endl;
			arr[low++] = arr[high];
		}


		while (low < high && arr[low] < pivot)
		{
			low++;
		}
		if (low < high)
		{
			cout << "low移动到high的index：" << low << "  " << high << endl;
			arr[high--] = arr[low];
		}


	}
	arr[low] = pivot;
	return low;
}

void qkSort(int* arr, int low, int high)
{
	if (low < high)
	{
		int mid = findIndex(arr, low, high);
		cout << " 中间点：" << mid << endl;
		qkSort(arr, low, mid - 1);
		qkSort(arr, mid + 1, high);
	}
}
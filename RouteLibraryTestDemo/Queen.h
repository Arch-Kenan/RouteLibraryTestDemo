#pragma once
#include "stdafx.h"
#include "stdio.h"
#include <math.h>

int countNum = 0;

bool find(int arr[], int row, int column)
{
	for (int i = 0; i < row; i++)
	{
		if (column == arr[i] || abs(row - i) == abs(arr[i] - column))
		{
			return false;
		}
	}
	return true;

}

//int find(int q[], int i, int k)
//{
//	int j = 0;
//	while (j < i)
//	{
//
//		if (q[j] == k || abs(j - i) == abs(q[j] - k))
//			return 0;
//		j++;
//	}
//	return 1;
//}

void print(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (j != arr[i])
			{
				printf("x ");
			}
			else
			{
				printf("Q ");
			}
		}
		printf("\n");
	}
}


//
void place(int arr[], int row, int size)
{
	if (row >= size)
	{
		print(arr, size);
		++countNum;
		printf("%d \n", countNum);
	}
	for (int column = 0; column < size; column++)
	{
		if (find(arr, row, column))
		{
			arr[row] = column;
			place(arr, row + 1, size);
		}
	}
}



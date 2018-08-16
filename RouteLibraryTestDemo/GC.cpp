#include "stdafx.h"

int testK(const char* source, const char* target);
void makeNext(const char* arr, const int size, int result[]);

int testK(const char* source, const char* target)
{
	int strLens = strlen(source);
	int size = strlen(target);
	int*  pNextList = new int[size];
	makeNext(target, size, pNextList);
	int i = 0;
	int j = 0;
	while (i < strLens && j < size)
	{
		if (source[i] == target[j])
		{
			i++;
			j++;
		}
		else
		{
			j = pNextList[j];
			i++;
		}
	}
	if (j < strLens)
	{
		return i - j;
	}
	else
	{
		return -1;
	}

}


void makeNext(const char* arr, const int size, int result[])
{
	result[0] = 0;
	for (int idx = 1; idx < size; idx++)
	{
		int j = 0;
		if (arr[idx] == arr[j])
		{
			result[idx++] = j + 1;
			j++;
		}
		else
		{
			if (j != 0)
			{
				j = result[j - 1];
			}
			else
			{
				result[idx++] = j;
			}
		}

	}
}
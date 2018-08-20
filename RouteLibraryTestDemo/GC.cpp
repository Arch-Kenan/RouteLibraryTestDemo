#include "stdafx.h"


int testK(const char* source, const char* target);
void makeNext(const char* arr, const int size, int result[]);

//std::ifstream   file("../testList.txt");
//std::istreambuf_iterator<char> beg(file), end;
//if (file)
//{
//	std::string   fileStr(beg, end);
//	const char* arr = "HorizontalCurveRouteData";
//	std::cout << fileStr.substr(testK(fileStr.c_str(), arr), 22);
//}
//
//file.close();
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
	int idx = 1;
	int j = 0;
	while ( idx < size)
	{

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
#include "stdafx.h"
#include "stringMatch.h"



//int testK(const char* source, const char* target);
//void makeNext(const char* arr, const int size, int result[]);

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
int testKMP(const char* source, const char* target)
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



void getNext2(char * p, int * next)
{
	next[0] = 0;
	int  len = strlen(p);
	for (int post = 1; post < len; post++)
	{
		int pre = 0;
		int num = 0;
		int cur = 0;
		int temp = 0;
		for (int index = 1; index <= post; index++)
		{
			pre = 0;
			cur = index;
			temp = index;
			while (cur <= post && p[pre++] == p[cur])
			{
				++num;
				temp = cur++;
			}
			if (temp != post)
				num = 0;
			else
			{
				next[post] = num;
				break;
			}
		}
	}
}

int kmp(char * t, char * p)
{
	int pTar = 0;
	int pPat = 0;
	int lenP = strlen(p);
	int* arrs = new int[lenP];
	getNext2(p, arrs);

	while (pTar < strlen(t) || pPat < lenP)
	{
		if (t[pTar] == p[pPat])
		{
			++pTar;
			++pPat;
		}
		else
		{
			pPat = arrs[pPat];
			++pTar;
		}
	}
	return pTar - pPat;

}
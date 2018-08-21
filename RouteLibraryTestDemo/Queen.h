#pragma once
#include "stdafx.h"

int qArr[24];
bool testPos(int row, int column)
{
	for (int i = 0; i < row; i++)
	{
		if (qArr[i] == column || abs(i - row) == abs(qArr[i] - column))
		{
			return false;
		}
	}
	return true;
}

void place(int sRow, int eRow)
{
	if (sRow > eRow)
	{
		return;
	}
	else
	{
		for (int i = 0; i < eRow; i++)
		{
			if (testPos(sRow, i))
			{
				qArr[sRow] = i;
				place(sRow + 1, eRow);
			}
		}
	}
}

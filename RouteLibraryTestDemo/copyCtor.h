#pragma once
#include "stdafx.h"
#include <iostream>
using namespace std;
class CopyCtor
{
public:
	CopyCtor()
	{
		std::cout << "default ctor\n";
	};
	CopyCtor(int n, double d):_num(n), _distStake(d)
	{
		std::cout << "construct fun\n";
	}
	CopyCtor(const CopyCtor& other)
	{
		this->_num = other._num;
		this->_distStake = other._distStake;
		std::cout << "copy construct\n";
	}
	CopyCtor& operator = (const CopyCtor& rhs)
	{
		this->_num = rhs._num;
		this->_distStake = rhs._distStake;
		std::cout << " operator = \n";
		return *this;
	}
	void fun()
	{

	}
protected:
public:
	int        _num;
	double     _distStake;
};



class Foo
{
public:
	int val;
	Foo *pnext;
	int num;

	void fun()
	{

	}
};
void foo_fo()
{
	Foo fo1;
	fo1.val = 898;

	Foo* fo = new Foo(fo1);
	Foo* fo2 = new Foo(fo1);
	//*fo = fo1;
	cout << (*fo).val << endl;
	if (fo->val || fo->pnext)
	{
		cout << fo->val << endl;
		cout << fo->pnext << endl;
		cout << fo->num << endl;
	}
}



void foo_ctor() {

	CopyCtor fo;

	//fo.fun();
	if (fo._num)
	{
		cout << fo._num << endl;
	}
}


void arrayTest(char str[])
{
	cout << sizeof(str) << endl;
}
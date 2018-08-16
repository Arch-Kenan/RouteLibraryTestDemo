#pragma once


#pragma once
#include "stdafx.h"
#include <iostream>

template<typename T>
class container;

template<typename T>
class U_Point
{
private:
	friend  class container<T>;
	U_Point(T* rhs) : _ptr(rhs), _num(1) {};
	~U_Point()
	{
		if (_num == 0)
		{
			delete _ptr;
			std::cout << "delete ptr:" << std::endl;
		}
	}
	T*		_ptr;
	int		_num;
};


template<typename T>
class container
{
public:
	container(T* p) :_sp(new U_Point<T>(p)) {};
	container(const container<T>& rhs)
	{
		this->_sp = rhs._sp;
		_sp->_num++;
	}
	container&  operator =(const container<T>& rhs)
	{
		if (this != &rhs)
		{
			this->_sp = rhs._sp;
			rhs._sp->_num++;
			if (--_sp->_num == 0)
			{
				delete this->_sp;
			}
		}
	}
	~container()
	{
		if (--_sp->_num == 0)
		{
			delete _sp;
		}
		std::cout << "this->_sp->_num:" << _sp->_num << std::endl;
	}

private:
	U_Point<T>*    _sp;

};




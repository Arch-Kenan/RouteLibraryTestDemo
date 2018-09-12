#pragma once
#include <iostream>
#include <vector>
using namespace std;

////
////baseMenu* bPtr = new compositeMenu();
////baseMenu* ptr1 = new MenuA();
////baseMenu* ptr2 = new MenuB();
////bPtr->add(ptr1);
////bPtr->add(ptr2);
////bPtr->display();
//class baseMenu
//{
//public:
//	virtual void display() = 0;
//	virtual void add(baseMenu*) {};
//	virtual ~baseMenu() {};
//};
//
//class MenuA : public baseMenu
//{
//public:
//	void display() override
//	{
//		std::cout << "menuA \n";
//	}
//};
//
//class MenuB : public baseMenu
//{
//public:
//	void display() override
//	{
//		std::cout << "menuB \n";
//	}
//};
//
//class compositeMenu : public baseMenu
//{
//public:
//	void display() override
//	{
//		std::cout << " begin display composite\n";
//		for (auto itr = _menuData.begin(); itr != _menuData.end(); itr++)
//		{
//			(*itr)->display();
//		}
//	}
//	void add(baseMenu* other) override
//	{
//		_menuData.push_back(other);
//	}
//
//private:
//	std::vector<baseMenu*>  _menuData;
//
//};


class curve
{
public:
	virtual void show() {};
};

class hCurve : public curve
{
public:
	void show() override
	{
		std::cout << "hCurve\n";
	}
};

class vCurve : public curve
{
public:
	void show() override
	{
		cout << "vCurve\n";
	}
};

class  deCurve : public curve
{
public:
	deCurve(curve* other) : _curveDate(other) {};
	virtual void show()
	{
		_curveDate->show();
	}
private:
	curve * _curveDate;
};


class  deCurveA : public deCurve
{
public:
	deCurveA(curve* other) :deCurve(other) {};
	void show() override
	{
		deCurve::show();
		addfun();
	}
private:
	void addfun()
	{
		std::cout <<"add funA\n";
	}
};



class deCurveB : public deCurve
{
public:
	deCurveB(curve* other) :deCurve(other) {};
	void show() override
	{
		deCurve::show();
		addfun();
	}

private:
	void addfun()
	{
		std::cout << "add funB\n";
	}
};
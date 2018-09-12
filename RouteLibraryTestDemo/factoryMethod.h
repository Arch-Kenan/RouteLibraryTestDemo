#pragma once
#include <iostream>

//
//factortyA A;
//baseHCurve*  bH = A.createH();
//baseVCurve*  bV = A.createV();
//bH->draw();
//bV->draw();
//delete bH;
//delete bV;

enum CURVETYPE
{
	HC,
	VC
};
class  baseHCurve
{
public:
	virtual ~baseHCurve()
	{
		std::cout << "baseH\n";
	}
	virtual void draw() {};
};

class horizentalCurve1 : public baseHCurve
{
public:
	~horizentalCurve1()
	{
		std::cout << "deconstruct HCurve1111\n";
	}
	void draw() override
	{
		std::cout << "horizentalCurve1111\n";
	}
};

class horizentalCurve2 : public baseHCurve
{
public:
	~horizentalCurve2()
	{
		std::cout << "deconstruct HCurve2222\n";
	}
	void draw() override
	{
		std::cout << "horizentalCurve2222\n";
	}
};


class baseVCurve
{
public:
	virtual ~baseVCurve() { std::cout << "baseV\n"; };
	virtual void draw() = 0;
};
class verticalCurve1 : public baseVCurve
{
public:
	void draw() override
	{
		std::cout << " verticalCurve1111\n";
	}
	~verticalCurve1()
	{
		std::cout << "deconstruct verticalCurve1111\n";
	}
};

class verticalCurve2 : public baseVCurve
{
public:
	void draw() override
	{
		std::cout << "verticalCurve222222\n";
	}
	~verticalCurve2()
	{
		std::cout << "deconstruct verticalCurve22222\n";
	}
};

class baseFactory
{
public:
	virtual baseHCurve* createH() = 0;
	virtual baseVCurve* createV() = 0;
};

class factortyA: public baseFactory
{
public:
	baseHCurve* createH()  override
	{
		return new horizentalCurve1();
	}
	baseVCurve* createV() override
	{
		return new verticalCurve2();
	}
};

class factoryB: public baseFactory
{
public:
	baseHCurve * createH() override
	{
		return new horizentalCurve2();
	}
	baseVCurve*  createV()
	{
		return new verticalCurve1();
	}
};

//class factoryMethod
//{
//public:
//	factoryMethod()
//	{
//		std::cout << "new factory\n";
//	}
//	~factoryMethod()
//	{
//		std::cout << "deconstruct factory\n";
//	}
//	baseCurve * createCuvre(CURVETYPE type)
//	{
//		switch (type)
//		{
//		case HC:
//			return new horizentalCurve();
//			break;
//		case VC:
//			return new verticalCurve();
//			break;
//		default:
//			return nullptr;
//			break;
//		}
//	}
//	
//
//};



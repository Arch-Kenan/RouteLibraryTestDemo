#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


//include osg lib
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>
#include "RouteCurveImpl.h"
int testK(const char* source, const char* target);
void makeNext(const char* arr, const int size, int result[]);
//test file
//std::ifstream   file("../testList.txt");
//std::istreambuf_iterator<char> beg(file), end;
//if (file)
//{
//	std::string   fileStr(beg, end);
//	
//	const char* arr = "HorizontalCurveRouteData";

//	std::cout << fileStr.substr(fileStr.find(arr), 22);
//}

//file.close();

void test(osg::Vec3dArray& arrays)
{
	std::fstream    file("D:/VSTeamServer/routeLibrary/vertexsData.txt");
	std::stringstream  sStream;
	std::string   line;
	double x, y, z;
	if (file)
	{
		while (std::getline(file, line))
		{
			sStream.str(line);
			sStream >> x >> y >> z;
			arrays.push_back(osg::Vec3d(x, y, z));
			sStream.clear();
			sStream.str("");
		}
	}

}


//测试平曲线 ：直线 + 圆弧+缓和曲线+直线
void test1(std::vector<osg::Vec2d>& result_points)
{
	HorizontalCurveRouteData::FactorPointData  facPoint1, facPoint2;
	HorizontalCurveRouteData  horizentalcurve;
	facPoint1._stakeNum = 375;
	facPoint1._coordX = 4000;
	facPoint1._coordY = 4070;
	facPoint1._backRadius = 480;
	facPoint1._frontRadius = 480;
	//horizentalcurve._factorPointDatas.push_back(facPoint1);

	facPoint2._stakeNum = 217.5;
	facPoint2._coordX = 4110.083;
	facPoint2._coordY = 3957.703;
	facPoint2._backRadius = 3000;
	facPoint2._frontRadius = 3000;


	horizentalcurve._factorPointDatas.push_back(facPoint2);
	horizentalcurve._factorPointDatas.push_back(facPoint1);



	RouteCurveImpl tempCurve(&horizentalcurve);
	tempCurve.initHorizontalDrawPoints();
	result_points = tempCurve.getHorizentalPoints();

}

//int arr[] = { 5, 0, 9, 4, 12, 39, 34, 21, 78, 31 };
//sStest(arr, 10);
//for (auto i : arr)
//{
//	cout << i << "   ";
//}
//
void bbstest(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		int flag = true;
		for (int j = 1; j < size - i; j++)
		{
			if (arr[j - 1] > arr[j])
			{
				int temp = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = temp;
				flag = false;
			}
		}
		if (flag)
		{
			break;
		}

	}
}


void sStest(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		int min = i;
		for (int j = i+1; j < size; j++)
		{
			if (arr[j] < arr[min])
			{
				min = j;
			}
		}
		if (i != min)
		{
			int temp = arr[min];
			arr[min] = arr[i];
			arr[i] = temp;
		}
	}
}



void test4(std::vector<osg::Vec2d>& result_2dpoints, std::vector<osg::Vec3d>& result_points, std::vector<osg::Vec2d>& curveTangent)
{
	HorizontalCurveRouteData::FactorPointData  tempFacPoint;
	HorizontalCurveRouteData  horizentalcurve;
	std::fstream  data;
	std::istringstream  sstream;
	data.open("D:\\My_selfwork\\data.txt");
	double stakeMile, coordX, coordY, preR, postR;
	double stakeMile1, coordX1, coordY1;
	std::string line;
	if (data)
	{
		data >> stakeMile1 >> coordY1 >> coordX1;
		data.clear();
		data.seekg(0, std::ios::beg);
		while (std::getline(data, line))
		{
			sstream.str(line);
			sstream >> stakeMile >> coordY >> coordX >> postR >> preR;
			tempFacPoint._stakeNum = stakeMile;
			tempFacPoint._coordX = coordX - coordX1;
			tempFacPoint._coordY = coordY - coordY1;
			if (preR == 0.0)
			{
				preR = MAX_CURVATURE;
			}
			if (postR == 0.0)
			{
				postR = MAX_CURVATURE;
			}
			tempFacPoint._backRadius = postR;
			tempFacPoint._frontRadius = preR;
			//std::cout << stakeMile << "   " << coordY <<"  "<< coordX << "    " << postR << "    " << preR << std::endl;
			horizentalcurve._factorPointDatas.push_back(tempFacPoint);
			sstream.clear();
			sstream.str("");
		}
	}
	data.close();

	//生成竖曲线
	VerticalCurveRouteData::VerticalCurveData  verPoint;
	VerticalCurveRouteData verticalCurve;
	double stake, elevation, arcRadius;
	std::fstream  verticalData;
	std::stringstream   tempSstring;
	verticalData.open("D:\\My_selfwork\\verticalData.txt");
	if (verticalData)
	{
		while (std::getline(verticalData, line))
		{
			tempSstring.str(line);
			tempSstring >> stake >> elevation >> arcRadius;
			verPoint._stakeNum = stake;
			verPoint._elevation = elevation;
			verPoint._circleRadius = arcRadius;
			verticalCurve._verticalCurveDatas.push_back(verPoint);
			tempSstring.clear();
			tempSstring.str("");
		}
	}
	verticalData.close();

	//根据里程获得点位置
	RouteCurveImpl tempCurve(&horizentalcurve, &verticalCurve);
	tempCurve.initHorizontalDrawPoints();
	tempCurve.initVerticalDrawPoints();
	result_points = tempCurve.getVerticalPoints();
	result_2dpoints = tempCurve.getHorizentalPoints();
	osg::Vec2d  tangent;
	osg::Vec3d  points;
	tempCurve.get3dPositionByMile(500, points, tangent);
	
	curveTangent = tempCurve.getPointsTangent();
}

void insertTest(int arr[], int size)
{
	for (int i = 1; i < size; i++)
	{
		for (int j = i; j > 0; j--)
		{
			if (arr[j - 1] > arr[j])
			{
				int temp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = temp;
			}
		}	
	}
}


int test5()
{
	std::fstream   data("D:\\My_selfwork\\data.txt");
	std::string line;
	std::stringstream   sstream;
	double stakeMile, coordX, coordY, preR, postR;
	if (data)
	{
		while (std::getline(data, line))
		{
			sstream.str(line);
			sstream >> stakeMile >> coordY >> coordX >> postR >> preR;
			std::cout << stakeMile << "   " << coordY << "  " << coordX << "    " << postR << "    " << preR << std::endl;
			sstream.clear();
			sstream.str("");
		}
	}
	
	return 0;
}


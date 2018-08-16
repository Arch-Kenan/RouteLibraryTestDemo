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

//测试平曲线 ：直线 + 缓和 + 圆弧
void test2(std::vector<osg::Vec2d>& result_2dpoints, std::vector<osg::Vec3d>& result_points)
{
	HorizontalCurveRouteData::FactorPointData  facPoint1, facPoint2, facPoint3, facPoint4;
	HorizontalCurveRouteData  horizentalcurve;

	facPoint1._stakeNum = 0;
	facPoint1._coordX = 0;
	facPoint1._coordY = 0;
	facPoint1._backRadius = MAX_CURVATURE;
	facPoint1._frontRadius = MAX_CURVATURE;
	horizentalcurve._factorPointDatas.push_back(facPoint1);

	facPoint2._stakeNum = 2.5;
	facPoint2._coordX = 2.0;
	facPoint2._coordY = 1.5;
	facPoint2._backRadius = MAX_CURVATURE;
	facPoint2._frontRadius = MAX_CURVATURE;
	horizentalcurve._factorPointDatas.push_back(facPoint2);

	facPoint3._stakeNum = 5.5;
	facPoint3._coordX = 4.636;
	facPoint3._coordY = 2.861;
	facPoint3._backRadius = -3;
	facPoint3._frontRadius = 3;
	horizentalcurve._factorPointDatas.push_back(facPoint3);

	facPoint4._stakeNum = 11;
	facPoint4._coordX = 8.65;
	facPoint4._coordY = 6.20;
	facPoint4._backRadius = 3;
	facPoint4._frontRadius = 3;
	horizentalcurve._factorPointDatas.push_back(facPoint4);



	//生成竖曲线
	VerticalCurveRouteData::VerticalCurveData  verPoint1, verPoint2, verPoint3, verPoint4;
	VerticalCurveRouteData verticalCurve;

	verPoint1._stakeNum = 0;
	verPoint1._elevation = 0;
	verPoint1._circleRadius = MAX_CURVATURE;
	verticalCurve._verticalCurveDatas.push_back(verPoint1);

	verPoint2._stakeNum = 3;
	verPoint2._elevation = 1.5;
	verPoint2._circleRadius = 3;
	verticalCurve._verticalCurveDatas.push_back(verPoint2);

	verPoint3._stakeNum = 7;
	verPoint3._elevation = 0.5;
	verPoint3._circleRadius = 4;
	verticalCurve._verticalCurveDatas.push_back(verPoint3);

	verPoint4._stakeNum = 11;
	verPoint4._elevation = 2.5;
	verPoint4._circleRadius = MAX_CURVATURE;
	verticalCurve._verticalCurveDatas.push_back(verPoint4);





	RouteCurveImpl tempCurve(&horizentalcurve, &verticalCurve);
	tempCurve.initHorizontalDrawPoints();
	tempCurve.initVerticalDrawPoints();
	result_points = tempCurve.getVerticalPoints();
	result_2dpoints = tempCurve.getHorizentalPoints();
}


//测试平曲线 ：直线 + 缓和 + 圆弧
void test3(std::vector<osg::Vec2d>& result_2dpoints, std::vector<osg::Vec3d>& result_points)
{
	HorizontalCurveRouteData::FactorPointData  facPoint1, facPoint2, facPoint3, facPoint4, facPoint5, facPoint6;
	HorizontalCurveRouteData  horizentalcurve;

	facPoint1._stakeNum = 0;
	facPoint1._coordX = 32108.260628;
	facPoint1._coordY = 40242.667423;
	facPoint1._backRadius = MAX_CURVATURE;
	facPoint1._frontRadius = -1496.5;
	horizentalcurve._factorPointDatas.push_back(facPoint1);

	facPoint2._stakeNum = 93.278632;
	facPoint2._coordX = 32098.142819;
	facPoint2._coordY = 40335.323294;
	facPoint2._backRadius = -450;
	facPoint2._frontRadius = -450;
	horizentalcurve._factorPointDatas.push_back(facPoint2);

	facPoint3._stakeNum = 253.707785;
	facPoint3._coordX = 32121.8286;
	facPoint3._coordY = 40493.13663;
	facPoint3._backRadius = -450;
	facPoint3._frontRadius = -450;
	horizentalcurve._factorPointDatas.push_back(facPoint3);

	facPoint4._stakeNum = 315.137737;
	facPoint4._coordX = 32146.679925;
	facPoint4._coordY = 40549.200637;
	facPoint4._backRadius = -230;
	facPoint4._frontRadius = -230;
	horizentalcurve._factorPointDatas.push_back(facPoint4);

	facPoint5._stakeNum = 443.411494;
	facPoint5._coordX = 32238.202684;
	facPoint5._coordY = 40636.69717;
	facPoint5._backRadius = -230;
	facPoint5._frontRadius = -230;
	horizentalcurve._factorPointDatas.push_back(facPoint5);

	facPoint6._stakeNum = 584.281075;
	facPoint6._coordX = 32373.029863;
	facPoint6._coordY = 40675.440372;
	facPoint6._backRadius = MAX_CURVATURE;
	facPoint6._frontRadius = MAX_CURVATURE;
	horizentalcurve._factorPointDatas.push_back(facPoint6);


	//生成竖曲线
	VerticalCurveRouteData::VerticalCurveData  verPoint1, verPoint2, verPoint3, verPoint4, verPoint5;
	VerticalCurveRouteData verticalCurve;
	verPoint1._stakeNum = 0;
	verPoint1._elevation = 24.4369;
	verPoint1._circleRadius = 0;
	verticalCurve._verticalCurveDatas.push_back(verPoint1);

	verPoint2._stakeNum = 149.873;
	verPoint2._elevation = 24.4369;
	verPoint2._circleRadius = 0;
	verticalCurve._verticalCurveDatas.push_back(verPoint2);

	verPoint3._stakeNum = 154.922;
	verPoint3._elevation = 24.5592;
	verPoint3._circleRadius = 0;
	verticalCurve._verticalCurveDatas.push_back(verPoint3);

	verPoint4._stakeNum = 200;
	verPoint4._elevation = 25.6511;
	verPoint4._circleRadius = 1750;
	verticalCurve._verticalCurveDatas.push_back(verPoint4);

	verPoint5._stakeNum = 410;
	verPoint5._elevation = 19.9711;
	verPoint5._circleRadius = 5025;
	verticalCurve._verticalCurveDatas.push_back(verPoint5);

	//verPoint6._stakeNum = 457.41;
	//verPoint6._elevation = 19.5719;
	//verPoint6._circleRadius = 0;
	//verticalCurve._verticalCurveDatas.push_back(verPoint6);

	//verPoint7._stakeNum = 463.182;
	//verPoint7._elevation = 19.5233;
	//verPoint7._circleRadius = 0;
	//verticalCurve._verticalCurveDatas.push_back(verPoint7);

	//verPoint8._stakeNum = 584.281075;
	//verPoint8._elevation = 19.5233;
	//verPoint8._circleRadius = 0;
	//verticalCurve._verticalCurveDatas.push_back(verPoint8);





	RouteCurveImpl tempCurve(&horizentalcurve, &verticalCurve);
	tempCurve.initHorizontalDrawPoints();
	tempCurve.initVerticalDrawPoints();
	result_points = tempCurve.getVerticalPoints();
	result_2dpoints = tempCurve.getHorizentalPoints();
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


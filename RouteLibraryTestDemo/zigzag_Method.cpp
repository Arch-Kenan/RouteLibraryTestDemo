#pragma once
#include "stdafx.h"
#include <math.h>
#include "zigzag_Method.h"
#include "osg/Matrixd"
#include "osg/Matrix"
#include "osg/Quat"
#ifndef RADIAN
#define RADIAN   3.14259
#endif

//line-circle
ZIGZAG_METHOD_RESULT_TYPE zigzag_method(const osg::Vec2d& lineStart, const osg::Vec2d& lineEnd, const osg::Vec2d& circleCenter, double circleRadius, bool circleClockwise, RouteCurveImpl& pConvolution)
{
	double cirleR = RADIAN;
	//点到直线的距离
	double A = lineEnd.y() - lineStart.y();
	double B = lineStart.x() - lineEnd.x();
	double C = lineEnd.x()*lineStart.y() - lineStart.x()* lineEnd.y();
	double dist = (A*circleCenter.x() + B * circleCenter.y() + C) / sqrt(A*A + B * B);
	if (abs(dist) <= circleRadius)
	{
		return ZMRT_ARC_CENTER_OVERLAP;
	}
	//求取当前坐标系下缓和曲线与圆的交点坐标endPnt;
	osg::Vec2d  endPnt;
	osg::Vec2d  circleLineDir;
	osg::Vec3d  endPntDir;
	int flag = 1;
	osg::Vec2d  lineDirc(lineEnd.x() - lineStart.x(), lineEnd.y() - lineStart.y());
	lineDirc.normalize();
	if (dist > 0)//圆心在直线的下方,直线逆时针旋转
	{
		circleLineDir = osg::Vec2d(-lineDirc.y(), lineDirc.x());
		osg::Matrix mat;
		mat.makeRotate(-RADIAN, osg::Vec3d(0.0, 0.0, 1.0));//顺时针旋转
		endPntDir = mat.preMult(osg::Vec3d(circleLineDir.x(), circleLineDir.y(), 0));
		flag = -1;
	}
	else//圆心在直线的上方,直线顺时针旋转
	{
		circleLineDir = osg::Vec2d(lineDirc.y(), -lineDirc.x());
		osg::Matrix mat;
		mat.makeRotate(RADIAN, osg::Vec3d(0.0, 0.0, 1.0));
		endPntDir = mat.preMult(osg::Vec3d(circleLineDir.x(), circleLineDir.y(), 0));
	}
	endPnt = circleCenter + osg::Vec2d(endPntDir.x(), endPntDir.y()) * circleRadius;

	//用积分公式求出缓和曲线长度和半径，偏转角的关系公式
	double Ls = RADIAN * 2 * circleRadius;
	double linePntdist = abs(A * endPnt.x() + B * endPnt.y() + C) / sqrt(A*A + B*B);

	//test code
	//osg::Vec2d  linePnt = (endPnt + circleLineDir * linePntdist);
	//double  testdist = (A*linePnt.x() + B * linePnt.y() + C) / sqrt(A*A + B * B);

	osg::Vec2d  startPnt = (endPnt + circleLineDir * linePntdist) - lineDirc * (linePntdist / std::tan(RADIAN / 3));

	HorizontalCurveRouteData::FactorPointData   tempPnt1;
	tempPnt1._backRadius = MAX_CURVATURERADIAN;
	tempPnt1._frontRadius = MAX_CURVATURERADIAN;
	tempPnt1._coordX = startPnt.x();
	tempPnt1._coordY = startPnt.y();
	tempPnt1._stakeNum = 0;

	HorizontalCurveRouteData::FactorPointData   tempPnt2;
	tempPnt2._backRadius = flag * circleRadius;
	tempPnt2._frontRadius = flag * circleRadius;
	tempPnt2._coordX = endPnt.x();
	tempPnt2._coordY = endPnt.y();
	tempPnt2._stakeNum = Ls;

	HorizontalCurveRouteData    tempHCRdata;
	tempHCRdata._factorPointDatas.push_back(tempPnt1);
	tempHCRdata._factorPointDatas.push_back(tempPnt2);

	pConvolution.setHorizontalCurveData(&tempHCRdata);
	return ZMRT_SUCCESS;
}




////circle-cirlce testcode
//ZIGZAG_METHOD_RESULT_TYPE zigzag_method(const osg::Vec2d& circleCenter1, double& circleRadius1, bool circleClockwise1, const osg::Vec2d& circleCenter2, double& circleRadius2, bool circleClockwise2, const ARC_JOIN_TYPE join_type, const double ratio_A1_A2/*not used in Oval-shaped case*/, RouteCurveImpl& pConvolution)
//{
//	//求取两个圆心的距离
//	double dist = std::sqrt(std::pow(circleCenter1.x() - circleCenter2.x(), 2) + std::pow(circleCenter1.y() - circleCenter2.y(),2));
//
//	//终点
//	osg::Vec2d  lineMidPnt((circleCenter1.x() + circleCenter2.x())/2, (circleCenter1.y() + circleCenter2.y())/2);
//	const double magicNum = 1.4;
//
//	HorizontalCurveRouteData::FactorPointData   tempPnt1;
//	tempPnt1._backRadius  = circleRadius1;
//	tempPnt1._frontRadius = circleRadius1;
//	tempPnt1._coordX = circleCenter1.x();
//	tempPnt1._coordY = circleCenter1.y();
//	tempPnt1._stakeNum = 0;
//
//	HorizontalCurveRouteData::FactorPointData   midPnt;
//	midPnt._backRadius = MAX_CURVATURERADIAN;
//	midPnt._frontRadius = MAX_CURVATURERADIAN;
//	midPnt._coordX = lineMidPnt.x();
//	midPnt._coordY = lineMidPnt.y();
//	midPnt._stakeNum = magicNum * dist / 2;
//
//	HorizontalCurveRouteData::FactorPointData   tempPnt2;
//	tempPnt2._backRadius =  -circleRadius2;
//	tempPnt2._frontRadius = -circleRadius2;
//	tempPnt2._coordX = circleCenter2.x();
//	tempPnt2._coordY = circleCenter2.y();
//	tempPnt2._stakeNum = magicNum * dist;
//
//
//
//	HorizontalCurveRouteData    tempHCRdata;
//	tempHCRdata._factorPointDatas.push_back(tempPnt1);
//	tempHCRdata._factorPointDatas.push_back(midPnt);
//	tempHCRdata._factorPointDatas.push_back(tempPnt2);
//
//	pConvolution.setHorizontalCurveData(&tempHCRdata);
//	return ZMRT_SUCCESS;
//}


//circle-cirlce testcode
ZIGZAG_METHOD_RESULT_TYPE zigzag_method(const osg::Vec2d& circleCenter1, double& circleRadius1, bool circleClockwise1, const osg::Vec2d& circleCenter2, double& circleRadius2, bool circleClockwise2, const ARC_JOIN_TYPE join_type, const double ratio_A1_A2/*not used in Oval-shaped case*/, RouteCurveImpl& pConvolution)
{
	//求取中间直缓点
	double ratio = circleRadius1 / (circleRadius1 + circleRadius2);
	osg::Vec2d  lineMidPnt = circleCenter1 + (circleCenter2 - circleCenter1) * ratio ;
	double distCirlce1Circle2 = (circleCenter2 - circleCenter1).length();
	double test = (lineMidPnt - circleCenter1).length();
	double radian1 = std::acos(circleRadius1 / (lineMidPnt - circleCenter1).length());
	osg::Vec2d   circleLineDir1 = lineMidPnt - circleCenter1;
	circleLineDir1.normalize();
	osg::Matrix mat1;
	int flag1 = 1;
	if (circleClockwise1)//圆逆时针方向
	{	
		mat1.makeRotate(-(RADIAN + radian1), osg::Vec3d(0.0, 0.0, 1.0));//终点顺时针旋转	
	}
	else
	{
		mat1.makeRotate(RADIAN + radian1, osg::Vec3d(0.0, 0.0, 1.0));//终点逆时针旋转
		flag1 = -1;
	}
	osg::Vec3d  circleEndDir1 = mat1.preMult(osg::Vec3d(circleLineDir1.x(), circleLineDir1.y(), 0));
	osg::Vec2d  circleEndPnt1 = circleCenter1 + osg::Vec2d(circleEndDir1.x(), circleEndDir1.y()) * circleRadius1;
	HorizontalCurveRouteData::FactorPointData   tempPnt1;
	tempPnt1._backRadius = flag1*circleRadius1;
	tempPnt1._frontRadius = flag1*circleRadius1;
	tempPnt1._coordX = circleEndPnt1.x();
	tempPnt1._coordY = circleEndPnt1.y();
	tempPnt1._stakeNum = 0;

	double Ls1 = 2 * circleRadius1 * RADIAN;
	HorizontalCurveRouteData::FactorPointData   midPnt;
	midPnt._backRadius = MAX_CURVATURERADIAN;
	midPnt._frontRadius = MAX_CURVATURERADIAN;
	midPnt._coordX = lineMidPnt.x();
	midPnt._coordY = lineMidPnt.y();
	midPnt._stakeNum = Ls1;

	double radian2 = std::acos(circleRadius2 / (lineMidPnt - circleCenter2).length());
	osg::Vec2d   circleLineDir2 = lineMidPnt - circleCenter2;
	circleLineDir2.normalize();
	osg::Matrix mat2;
	int flag2 = 1;
	if (circleClockwise2)//圆逆时针方向
	{
		mat2.makeRotate(RADIAN + radian2, osg::Vec3d(0.0, 0.0, 1.0));//终点逆时针旋转	
	}
	else
	{
		mat2.makeRotate(-(RADIAN + radian2), osg::Vec3d(0.0, 0.0, 1.0));//终点顺时针旋转
		flag2 = -1;
	}
	osg::Vec3d circleEndDir2 = mat2.preMult(osg::Vec3d(circleLineDir2.x(), circleLineDir2.y(), 0));
	osg::Vec2d circleEndPnt2 = circleCenter2 + osg::Vec2d(circleEndDir2.x(), circleEndDir2.y()) * circleRadius2;
	HorizontalCurveRouteData::FactorPointData   tempPnt2;
	tempPnt2._backRadius = flag2*circleRadius1;
	tempPnt2._frontRadius = flag2*circleRadius1;
	tempPnt2._coordX = circleEndPnt2.x();
	tempPnt2._coordY = circleEndPnt2.y();
	tempPnt2._stakeNum = Ls1 + RADIAN*circleRadius2 *2;

	HorizontalCurveRouteData*    tempHCRdata = new HorizontalCurveRouteData;
	tempHCRdata->_factorPointDatas.push_back(tempPnt1);
	tempHCRdata->_factorPointDatas.push_back(midPnt);
	tempHCRdata->_factorPointDatas.push_back(tempPnt2);
	pConvolution.setHorizontalCurveData(tempHCRdata);

	delete tempHCRdata;
	return ZMRT_SUCCESS;
}





//circle-line
ZIGZAG_METHOD_RESULT_TYPE zigzag_method(const osg::Vec2d& circleCenter, double& circleRadius, bool circleClockwise, const osg::Vec2d& lineStart, const osg::Vec2d& lineEnd, RouteCurveImpl& pConvolution)
{
	//点到直线的距离
	double A = lineEnd.y() - lineStart.y();
	double B = lineStart.x() - lineEnd.x();
	double C = lineEnd.x()*lineStart.y() - lineStart.x()* lineEnd.y();
	double dist = (A*circleCenter.x() + B * circleCenter.y() + C) / sqrt(A*A + B * B);
	if (abs(dist) <= circleRadius)
	{
		return ZMRT_ARC_CENTER_OVERLAP;
	}
	//求取当前坐标系下缓和曲线与圆的交点坐标endPnt;
	osg::Vec2d  endPnt;
	osg::Vec2d  circleLineDir;
	osg::Vec3d  endPntDir;
	int flag = 1;
	osg::Vec2d  lineDirc(lineEnd.x() - lineStart.x(), lineEnd.y() - lineStart.y());
	lineDirc.normalize();
	if (dist > 0)//圆心在直线的下方,直线逆时针旋转
	{
		circleLineDir = osg::Vec2d(-lineDirc.y(), lineDirc.x());
		osg::Matrix mat;
		mat.makeRotate(RADIAN, osg::Vec3d(0.0, 0.0, 1.0));//逆时针旋转
		endPntDir = mat.preMult(osg::Vec3d(circleLineDir.x(), circleLineDir.y(), 0));
		flag = -1;
	}
	else//圆心在直线的上方,直线顺时针旋转
	{
		circleLineDir = osg::Vec2d(lineDirc.y(), -lineDirc.x());
		osg::Matrix mat;
		mat.makeRotate(-RADIAN, osg::Vec3d(0.0, 0.0, 1.0));
		endPntDir = mat.preMult(osg::Vec3d(circleLineDir.x(), circleLineDir.y(), 0));
	}
	endPnt = circleCenter + osg::Vec2d(endPntDir.x(), endPntDir.y()) * circleRadius;

	//用积分公式求出缓和曲线长度和半径，偏转角的关系公式
	double Ls = RADIAN * 2 * circleRadius;
	double linePntdist = abs(A*endPnt.x() + B * endPnt.y() + C) / sqrt(A*A + B * B);
	osg::Vec2d  startPnt = (endPnt + circleLineDir * linePntdist) + lineDirc * (linePntdist / std::tan(RADIAN / 3));

	HorizontalCurveRouteData::FactorPointData   tempPnt1;
	tempPnt1._backRadius = flag * circleRadius;
	tempPnt1._frontRadius = flag * circleRadius;
	tempPnt1._coordX = endPnt.x();
	tempPnt1._coordY = endPnt.y();
	tempPnt1._stakeNum = 0;

	HorizontalCurveRouteData::FactorPointData   tempPnt2;
	tempPnt2._backRadius =  MAX_CURVATURERADIAN;
	tempPnt2._frontRadius = MAX_CURVATURERADIAN;
	tempPnt2._coordX = startPnt.x();
	tempPnt2._coordY = startPnt.y();
	tempPnt2._stakeNum = Ls;

	HorizontalCurveRouteData*    tempHCRdata =new HorizontalCurveRouteData;
	tempHCRdata->_factorPointDatas.push_back(tempPnt1);
	tempHCRdata->_factorPointDatas.push_back(tempPnt2);
	pConvolution.setHorizontalCurveData(tempHCRdata);
	delete tempHCRdata;
	return ZMRT_SUCCESS;
}
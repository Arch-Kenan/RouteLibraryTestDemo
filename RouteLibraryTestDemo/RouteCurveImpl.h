#pragma once

#include "RouteCurveData.h"

#include "osg\Vec3d"




class  RouteCurveImpl
{
public:
	RouteCurveImpl(HorizontalCurveRouteData* H = nullptr, VerticalCurveRouteData* V = nullptr,
				   CrossSlopeRouteData* C = nullptr, StandardCrossSectionData* S = nullptr);

	~RouteCurveImpl();

	//生成平曲线的绘制点数组
	bool initHorizontalDrawPoints();

	//获取平曲线绘制点数组
	std::vector<osg::Vec2d>&  getHorizentalPoints();

	//生成绘制高程的三维点数组
	bool initVerticalDrawPoints();

	//获取高程三维点数组
	std::vector<osg::Vec3d>& getVerticalPoints();

	//获取平曲线绘制点切线数组
	std::vector<osg::Vec2d>&  getPointsTangent();

	//通过桩号获取平曲线上的单个点的坐标和切线
	bool get2dPositionByMile(double mile, osg::Vec2d& position, osg::Vec2d& tangent);


	//通过桩号获取平曲线上的一系列点的坐标和切线
	bool get2dPositionsByMile(std::vector<double>& miles, std::vector<osg::Vec2d>& points, std::vector<osg::Vec2d>& tangent);


	//通过桩号获取空间曲线的点的三维点坐标和切线
	bool get3dPositionByMile(double mile, osg::Vec3d& point, osg::Vec2d& tangent);

	//由平曲线上里程桩号获取高程信息
	bool getElevation(double stakeMile, double& elevation);

	//通过点坐标获取桩号
	double getMileByPos(osg::Vec2d);

	//偏移曲线
	RouteCurveImpl* offsetCurve(double offset);

	bool intersect(RouteCurveImpl* pOther, std::vector<osg::Vec2d>& points);

private:

	//获取平曲线各个要素点的方位角（用弧度表示），并将其存储在类成员变量_factorPointsTangent中
	bool initHorizontalTangent();

	//初始化竖曲线坡度信息
	bool initVerticalGradient();




	////缓和曲线上任意一点坐标推算
	//bool getTransitionCurve(double Direction, double R, double Ls, double Li);

private:
	HorizontalCurveRouteData*                     _horizontalCurveRouteData;

	VerticalCurveRouteData*                         _verticalCurveRouteData;

	CrossSlopeRouteData*                               _crossSlopeRouteData;

	StandardCrossSectionData*                         _standardCrossSection;

private:

	//存储每个要素点的切线弧度值
	std::vector<double>                               _factorPointsTangent;

	//存储竖曲线坡度信息
	std::vector<double>                              _verticalGradientData;

	//存储平曲线绘制点
	std::vector<osg::Vec2d>                          _drawHorizentalPointsData;

	//存储平曲线绘制点所对应的切线
	std::vector<osg::Vec2d>                         _drawPointsTangentData;



	//存储三维点信息
	std::vector<osg::Vec3d>                        _routeCurvePositionData;

};




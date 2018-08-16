#pragma once
#include "RouteCurveImpl.h"
#define RADIAN    (M_PI/8)

//返回值枚举

enum ZIGZAG_METHOD_RESULT_TYPE
{
	ZMRT_SUCCESS = 0,
	ZMRT_LINE_TERMINAL_POINT_OVERLAP,
	ZMRT_ARC_TERMINAL_POINT_OVERLAP,
	ZMRT_ARC_RAIDUS_TOO_SHORT,
	ZMRT_INVALID_ARC_DEFINITION,
	ZMRT_TWO_LINES_NOT_SUPPORTED,
	ZMRT_ONE_CIRCLE_ONE_ARC_NOT_SUPPORTED,
	ZMRT_INSUFFICIENT_CONDITION_TO_DETERMINE_ROTATION_DIRECTION,
	ZMRT_ROTATION_DIRECTIONS_DONT_MATCH,
	ZMRT_INVALID_CONVOLUTION_PARAMETER_RATIO,	//S, C
	ZMRT_ARC_RADIUS_ALMOST_EQUAL,				//Oval
	ZMRT_ARC_CENTER_OVERLAP,
	ZMRT_UNKNOWN_JOIN_TYPE,
	ZMRT_CONVOLUTION_DOES_NOT_EXIST,
	ZMRT_NOTCALC,
	ZMRT_UNKNOWN_ERROR,
};


//3.1.1 圆弧连接方式

enum ARC_JOIN_TYPE
{
	AJT_S = 0,				//S-shaped curve
	AJT_O,					//Oval-shaped curve
	AJT_C,					//C-shaped curve
};


//line - circle
ZIGZAG_METHOD_RESULT_TYPE zigzag_method(const osg::Vec2d& lineStart, const osg::Vec2d& lineEnd, const osg::Vec2d& cirlceCenter, double circleRadius, bool circleClockwise, RouteCurveImpl& pConvolution);

//circle-cirlce
ZIGZAG_METHOD_RESULT_TYPE zigzag_method(const osg::Vec2d& cirlceCenter1, double& circleRadius1, bool circleClockwise1, const osg::Vec2d& cirlceCenter2, double& circleRadius2, bool circleClockwise2, const ARC_JOIN_TYPE join_type, const double ratio_A1_A2/*not used in Oval-shaped case*/, RouteCurveImpl& pConvolution);

//circle-line
ZIGZAG_METHOD_RESULT_TYPE zigzag_method(const osg::Vec2d& cirlceCenter, double& circleRadius, bool circleClockwise, const osg::Vec2d& lineStart, const osg::Vec2d& lineEnd, RouteCurveImpl& pConvolution);



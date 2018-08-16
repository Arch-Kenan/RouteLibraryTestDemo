#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include <float.h>
#include <vector>
#include <string>
#include <map>
#define DEVIDENUM  96
#define MAX_CURVATURE  3.402823466e+38F
#define Z_COORDINATE  0.0

extern const int _devideNum;

//平曲线数据
class   HorizontalCurveRouteData
{
public:
	enum InputType
	{
		BASICWIREPOINT = 0,			//基本导线点
		COMPLEXWIREPOINT,			//复杂导线点
		FACTORPOINT					//要素点
	};

	struct BasicWirePointData
	{
		double _coordX;				//大地X坐标
		double _coordY;				//大地Y坐标
		double _curveParameter;		//曲线参数
		double _tangentParameter;	//切基线参数
	};

	struct ComplexWirePointData
	{
		double _coordX;
		double _coordY;
		double _startRadius;				//起始半径
		double _firstTransitionLenth;		//第一缓长
		double _circleRadius;				//圆弧半径
		double _secondTransitionLenth;		//第二缓长
		double _endRadius;					//终点半径
	};

	struct FactorPointData
	{
		double _stakeNum;				//桩号
		double _coordX;
		double _coordY;
		double _frontRadius;			//前半径
		double _backRadius;				//后半径
	};

public:
	InputType							_inputType;					//输入类型
	double								_startStakeNum;
	std::string							_controlPrecision;			//控制精度

	std::vector<BasicWirePointData>		_basicWirePointDatas;
	std::vector<ComplexWirePointData>	_complexWirePointDatas;
	std::vector<FactorPointData>		_factorPointDatas;

};


//竖曲线路线数据
class   VerticalCurveRouteData
{
public:
	struct VerticalCurveData
	{
		double	_stakeNum;			//桩号
		double   _elevation;		//高程
		double	_circleRadius;		//圆弧半径
	};


public:
	std::vector<VerticalCurveData>		_verticalCurveDatas;		//竖曲线数据
};

//横坡数据
class  CrossSlopeRouteData
{
public:
	enum ChangeType
	{
		LINEAR = 0,			//线性
		PARABOLA3			//三次抛物线
	};

	struct HorizontalPositionData
	{
		double		_stakeNum;
		double		_leftPosition;		//左侧高程线位置
		double		_rightPostion;		//右侧高程线位置
	};

	struct BridgeCrossSlopeData
	{
		double			_stakeNum;
		float			_leftHardShoulder;		//左硬路肩/人行道坡度
		float			_leftSlope;				//左横坡
		float			_rightSlope;			//右横坡
		float			_rightHardShoulder;		//右硬路肩/人行道坡度
		ChangeType		_changeType;			//渐变方式
	};

public:
	std::vector<HorizontalPositionData>		_horizontalPositionDatas;
	std::vector<BridgeCrossSlopeData>		_bridgeCrossSlopeData;
};



//标准横断面数据
class   StandardCrossSectionData
{
public:
	struct BridgeElementData
	{
		std::string		_type;
		double			_width;
		bool			_beChange;
		std::string		_note;
	};

private:
	std::vector<BridgeElementData>	_bridgeElementDatas;
};

class GroundLineData
{
public:
	enum Type
	{
		REALITY = 0,		//实际地面线
		PLAN				//规划地面线
	};

	struct ProfileGroundLine
	{
		std::string						_name;
		float							_crossPosition;
		Type							_type;
		std::map<double, double>		_data;
	};
	struct CrossSectionGroundLine
	{
		double								_stakeMark;
		std::map<double, double>			_leftDistance;
		std::map<double, double>			_rightDistance;
	};

public:
	std::vector<ProfileGroundLine*>			_profileGroundLines;
	std::vector<CrossSectionGroundLine*>	_crossSectionGroundLines;
};



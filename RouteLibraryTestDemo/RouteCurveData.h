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

//ƽ��������
class   HorizontalCurveRouteData
{
public:
	enum InputType
	{
		BASICWIREPOINT = 0,			//�������ߵ�
		COMPLEXWIREPOINT,			//���ӵ��ߵ�
		FACTORPOINT					//Ҫ�ص�
	};

	struct BasicWirePointData
	{
		double _coordX;				//���X����
		double _coordY;				//���Y����
		double _curveParameter;		//���߲���
		double _tangentParameter;	//�л��߲���
	};

	struct ComplexWirePointData
	{
		double _coordX;
		double _coordY;
		double _startRadius;				//��ʼ�뾶
		double _firstTransitionLenth;		//��һ����
		double _circleRadius;				//Բ���뾶
		double _secondTransitionLenth;		//�ڶ�����
		double _endRadius;					//�յ�뾶
	};

	struct FactorPointData
	{
		double _stakeNum;				//׮��
		double _coordX;
		double _coordY;
		double _frontRadius;			//ǰ�뾶
		double _backRadius;				//��뾶
	};

public:
	InputType							_inputType;					//��������
	double								_startStakeNum;
	std::string							_controlPrecision;			//���ƾ���

	std::vector<BasicWirePointData>		_basicWirePointDatas;
	std::vector<ComplexWirePointData>	_complexWirePointDatas;
	std::vector<FactorPointData>		_factorPointDatas;

};


//������·������
class   VerticalCurveRouteData
{
public:
	struct VerticalCurveData
	{
		double	_stakeNum;			//׮��
		double   _elevation;		//�߳�
		double	_circleRadius;		//Բ���뾶
	};


public:
	std::vector<VerticalCurveData>		_verticalCurveDatas;		//����������
};

//��������
class  CrossSlopeRouteData
{
public:
	enum ChangeType
	{
		LINEAR = 0,			//����
		PARABOLA3			//����������
	};

	struct HorizontalPositionData
	{
		double		_stakeNum;
		double		_leftPosition;		//���߳���λ��
		double		_rightPostion;		//�Ҳ�߳���λ��
	};

	struct BridgeCrossSlopeData
	{
		double			_stakeNum;
		float			_leftHardShoulder;		//��Ӳ·��/���е��¶�
		float			_leftSlope;				//�����
		float			_rightSlope;			//�Һ���
		float			_rightHardShoulder;		//��Ӳ·��/���е��¶�
		ChangeType		_changeType;			//���䷽ʽ
	};

public:
	std::vector<HorizontalPositionData>		_horizontalPositionDatas;
	std::vector<BridgeCrossSlopeData>		_bridgeCrossSlopeData;
};



//��׼���������
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
		REALITY = 0,		//ʵ�ʵ�����
		PLAN				//�滮������
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



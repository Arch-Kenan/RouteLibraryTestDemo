#pragma once

#include "RouteCurveData.h"

#include "osg\Vec3d"




class  RouteCurveImpl
{
public:
	RouteCurveImpl(HorizontalCurveRouteData* H = nullptr, VerticalCurveRouteData* V = nullptr,
				   CrossSlopeRouteData* C = nullptr, StandardCrossSectionData* S = nullptr);

	~RouteCurveImpl();

	//����ƽ���ߵĻ��Ƶ�����
	bool initHorizontalDrawPoints();

	//��ȡƽ���߻��Ƶ�����
	std::vector<osg::Vec2d>&  getHorizentalPoints();

	//���ɻ��Ƹ̵߳���ά������
	bool initVerticalDrawPoints();

	//��ȡ�߳���ά������
	std::vector<osg::Vec3d>& getVerticalPoints();

	//��ȡƽ���߻��Ƶ���������
	std::vector<osg::Vec2d>&  getPointsTangent();

	//ͨ��׮�Ż�ȡƽ�����ϵĵ���������������
	bool get2dPositionByMile(double mile, osg::Vec2d& position, osg::Vec2d& tangent);


	//ͨ��׮�Ż�ȡƽ�����ϵ�һϵ�е�����������
	bool get2dPositionsByMile(std::vector<double>& miles, std::vector<osg::Vec2d>& points, std::vector<osg::Vec2d>& tangent);


	//ͨ��׮�Ż�ȡ�ռ����ߵĵ����ά�����������
	bool get3dPositionByMile(double mile, osg::Vec3d& point, osg::Vec2d& tangent);

	//��ƽ���������׮�Ż�ȡ�߳���Ϣ
	bool getElevation(double stakeMile, double& elevation);

	//ͨ���������ȡ׮��
	double getMileByPos(osg::Vec2d);

	//ƫ������
	RouteCurveImpl* offsetCurve(double offset);

	bool intersect(RouteCurveImpl* pOther, std::vector<osg::Vec2d>& points);

private:

	//��ȡƽ���߸���Ҫ�ص�ķ�λ�ǣ��û��ȱ�ʾ����������洢�����Ա����_factorPointsTangent��
	bool initHorizontalTangent();

	//��ʼ���������¶���Ϣ
	bool initVerticalGradient();




	////��������������һ����������
	//bool getTransitionCurve(double Direction, double R, double Ls, double Li);

private:
	HorizontalCurveRouteData*                     _horizontalCurveRouteData;

	VerticalCurveRouteData*                         _verticalCurveRouteData;

	CrossSlopeRouteData*                               _crossSlopeRouteData;

	StandardCrossSectionData*                         _standardCrossSection;

private:

	//�洢ÿ��Ҫ�ص�����߻���ֵ
	std::vector<double>                               _factorPointsTangent;

	//�洢�������¶���Ϣ
	std::vector<double>                              _verticalGradientData;

	//�洢ƽ���߻��Ƶ�
	std::vector<osg::Vec2d>                          _drawHorizentalPointsData;

	//�洢ƽ���߻��Ƶ�����Ӧ������
	std::vector<osg::Vec2d>                         _drawPointsTangentData;



	//�洢��ά����Ϣ
	std::vector<osg::Vec3d>                        _routeCurvePositionData;

};




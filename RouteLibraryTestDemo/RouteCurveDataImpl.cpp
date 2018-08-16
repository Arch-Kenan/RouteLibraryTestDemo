#pragma once

#include "utility.h"
#include "RouteCurveImpl.h"

const int _devideNum = 100;




RouteCurveImpl::RouteCurveImpl(HorizontalCurveRouteData* H, VerticalCurveRouteData* V,
	CrossSlopeRouteData* C, StandardCrossSectionData* S) :
	_horizontalCurveRouteData(H), _verticalCurveRouteData(V), _crossSlopeRouteData(C), _standardCrossSection(S)
{

};


RouteCurveImpl::~RouteCurveImpl() { };


std::vector<osg::Vec2d>&  RouteCurveImpl::getHorizentalPoints()
{
	return this->_drawHorizentalPointsData;
}


std::vector<osg::Vec2d>&  RouteCurveImpl::getPointsTangent()
{
	return this->_drawPointsTangentData;
}


std::vector<osg::Vec3d>& RouteCurveImpl::getVerticalPoints()
{
	return this->_routeCurvePositionData;
}


bool RouteCurveImpl::initHorizontalTangent()
{
	std::vector<HorizontalCurveRouteData::FactorPointData>& curveDatas = this->_horizontalCurveRouteData->_factorPointDatas;
	this->_factorPointsTangent.clear();
	//�ж����߶�����
	int flag;//������ƫת������ƫת��־
	int flagDir = 1;  //����ǰ�������жϱ�־��������Ϊ���� ���ҵ���Ϊ��
	if (curveDatas.empty())
	{
		return false;
	}
	for (auto ptr = curveDatas.begin(); ptr != curveDatas.end() - 1; ptr++)
	{
		if ((ptr + 1)->_backRadius == ptr->_frontRadius)//ǰ�����ʰ뾶�Ƿ����
		{
			if ((ptr + 1)->_backRadius == MAX_CURVATURE)//�����Ϊ���������ʱ��Ϊֱ��
			{
				double lineRadian = atan2((ptr + 1)->_coordY - ptr->_coordY, ((ptr + 1)->_coordX - ptr->_coordX));
				this->_factorPointsTangent.push_back(lineRadian);
			}
			else //Բ��
			{
				double arclength = (ptr + 1)->_stakeNum - ptr->_stakeNum;
				double arcRadian = arclength / (ptr + 1)->_backRadius;//ͨ���뾶��ƫת���ж�ƫת
				double fistTangent = atan2((ptr + 1)->_coordY - ptr->_coordY, (ptr + 1)->_coordX - ptr->_coordX);
				this->_factorPointsTangent.push_back(fistTangent - arcRadian / 2);
			}
		}
		else
		{
			double C = fabs(((ptr + 1)->_stakeNum - ptr->_stakeNum) * ptr->_frontRadius * (ptr + 1)->_backRadius / (ptr->_frontRadius - (ptr + 1)->_backRadius));
			double fistTangent = atan2((ptr + 1)->_coordY - ptr->_coordY, (ptr + 1)->_coordX - ptr->_coordX);
			double L1, Ls, Len;
			int signFlag = 1;
			if (fabs(ptr->_frontRadius) > fabs((ptr + 1)->_backRadius))//˳��ʽ��������,���ʰ뾶�𽥼�С
			{
				Ls = C / fabs((ptr + 1)->_backRadius);
				L1 = C / fabs(ptr->_frontRadius);
				flag = (ptr + 1)->_backRadius / fabs((ptr + 1)->_backRadius);//���԰뾶�ٳ��Ծ���ֵ���ж����ߵ�ƫת����
				Len = L1;
			}
			else//����ʽ��������,���ʰ뾶������
			{
				Ls = C / fabs(ptr->_frontRadius);
				L1 = C / fabs((ptr + 1)->_backRadius);
				flag = ptr->_frontRadius / fabs(ptr->_frontRadius);//���԰뾶�ٳ��Ծ���ֵ���ж����ߵ�ƫת����
				Len = Ls;
				signFlag = -1;//����deltatangent��������
			}
			//X,Y ����Ϊ�ֲ����꣬���������޹�
			double X1 = L1 - pow(L1, 5) / (40 * C *C);
			double Y1 = pow(L1, 3) / (6 * C);
			double X2 = Ls - pow(Ls, 5) / (40 * C* C);
			double Y2 = pow(Ls, 3) / (6 * C);
			double deltaTangent = (atan2(Y2 - Y1, X2 - X1) - (Len*Len) / (2 * C)) * signFlag;
			this->_factorPointsTangent.push_back(fistTangent - flag * deltaTangent);
		}
	}
	return true;
}


//���ɻ��ƵĵĲ�ֵ�㣬��ֵ�����Ŀ�� DEVIDENUM �궨��
bool RouteCurveImpl::initHorizontalDrawPoints()
{

	std::vector<HorizontalCurveRouteData::FactorPointData>&  factor_pnts = this->_horizontalCurveRouteData->_factorPointDatas;
	if (!initHorizontalTangent())
	{
		return false;
	}
	//��ȡ׮��������Ĳ���ֵ
	double deltaLen = (factor_pnts.back()._stakeNum - factor_pnts.front()._stakeNum) / DEVIDENUM;

	std::vector<double>& directionRadians = this->_factorPointsTangent;
	int index = 0;
	this->_drawHorizentalPointsData.push_back(osg::Vec2d(factor_pnts.begin()->_coordX, factor_pnts.begin()->_coordY));

	//��ʼ���߷���
	double firstPointTangent = this->_factorPointsTangent[0];
	this->_drawPointsTangentData.push_back(osg::Vec2d(cos(firstPointTangent), sin(firstPointTangent)));

	for (std::vector<HorizontalCurveRouteData::FactorPointData>::iterator itr = factor_pnts.begin(); itr != factor_pnts.end() - 1; itr++)
	{
		if (itr->_frontRadius == (itr + 1)->_backRadius)
		{
			if (itr->_frontRadius != MAX_CURVATURE)//ǰ��뾶����Ҳ�Ϊ�����ʱ׮����������ΪԲ��
			{
				getPointsOnArc(itr, _factorPointsTangent[index], deltaLen,
					this->_drawHorizentalPointsData, this->_drawPointsTangentData);
				index++;//����ִ�к�λ��������
			}
			else //ǰ��뾶�����Ϊ�����ʱ������׮������Ϊֱ��
			{
				getPointsOnLine(itr, directionRadians[index], deltaLen,
					this->_drawHorizentalPointsData, this->_drawPointsTangentData);
				index++;//����ִ�к�λ��������
			}
		}
		else //ǰ��뾶����ʱ������׮������Ϊ��������
		{
			getPointsOnTransiLine(itr, directionRadians[index], deltaLen,
				this->_drawHorizentalPointsData, this->_drawPointsTangentData);
			index++;//����ִ�к�λ��������
		}
	}
	return true;
}



//��ȡ������Ҫ�ص����Ϣ�����ҽ����洢��·��ʵ������
//��ǰ����¶��ɵ�ǰ��͵�ǰ�������Լ�1�ĵ������ ���һ����ĺ����¶������һ������������Լ�1�ĵ����
bool RouteCurveImpl::initVerticalGradient()
{
	std::vector<VerticalCurveRouteData::VerticalCurveData>&  verticalPointsData =
		this->_verticalCurveRouteData->_verticalCurveDatas;

	//�洢��ʱ�¶���Ϣ
	double tempGradient;

	auto itr = verticalPointsData.begin();
	//��һ���̵߳�Ĭ��Ϊֱ�����Ժ�ǰ�¶�һ��
	tempGradient = ((itr + 1)->_elevation - itr->_elevation) / ((itr + 1)->_stakeNum - itr->_stakeNum);
	this->_verticalGradientData.push_back(tempGradient);

	for (; itr != verticalPointsData.end() - 1; itr++)
	{
		tempGradient = ((itr + 1)->_elevation - itr->_elevation) / ((itr + 1)->_stakeNum - itr->_stakeNum);

		this->_verticalGradientData.push_back(tempGradient);
	}
	//���һ����̵߳�Ĭ��Ϊֱ�ߣ� �����¶Ⱥ�ǰ�¶�һ��
	tempGradient = (itr->_elevation - (itr - 1)->_elevation) / (itr->_stakeNum - (itr - 1)->_stakeNum);
	this->_verticalGradientData.push_back(tempGradient);

	return true;
}



//���ɻ��Ƹ̵߳���ά�����飬����ʵ�������������㷨�����ɵ����ݷ������˽�г�Ա_routeCurvePositionData��
bool RouteCurveImpl::initVerticalDrawPoints()
{
	if (!this->initVerticalGradient())
	{
		return false;
	}
	std::vector<VerticalCurveRouteData::VerticalCurveData>& vertPoints = this->_verticalCurveRouteData->_verticalCurveDatas;
	std::vector<osg::Vec2d>&  result2d = this->_drawHorizentalPointsData;
	std::vector<osg::Vec3d>&  result = this->_routeCurvePositionData;

	double deltaLen = (vertPoints.back()._stakeNum - vertPoints.begin()->_stakeNum) / DEVIDENUM;
	double resultE = vertPoints.begin()->_elevation;

	double Li = 0;
	int index = 0;//�����߹ؼ����ǰ������
	int pointIndex = 0;//ƽ���ߵĻ��Ƶ������

	//��һ�������⴦��
	result.push_back(osg::Vec3d(result2d[pointIndex].x(), result2d[pointIndex].y(), resultE));
	pointIndex++;
	for (auto itr = vertPoints.begin(); itr != vertPoints.end() - 1; itr++)
	{
		do
		{
			resultE = getElevationAlgorithem(Li, _verticalGradientData[index], _verticalGradientData[index + 1],
				_verticalGradientData[index + 2], itr);
			result.push_back(osg::Vec3d(result2d[pointIndex].x(), result2d[pointIndex].y(), resultE));

			Li += deltaLen;

			++pointIndex;
		} while (Li < (itr + 1)->_stakeNum);

		++index;
	}
	return true;
}

//��ƽ���������׮�Ż�ȡ�߳���Ϣ,�ڲ������������㷨ʵ��
bool RouteCurveImpl::getElevation(double stakeMile, double& elevation)
{
	if (stakeMile <0 || stakeMile > _horizontalCurveRouteData->_factorPointDatas.back()._stakeNum || this->_verticalGradientData.empty())
	{
		return false;
	}
	int index = 0;
	auto itr = this->_verticalCurveRouteData->_verticalCurveDatas.begin();
	while (itr->_stakeNum < stakeMile)
	{
		itr++;
		index++;
	}
	elevation = getElevationAlgorithem(stakeMile, _verticalGradientData[index - 1],
		_verticalGradientData[index], _verticalGradientData[index + 1], itr - 1);
	return true;
}


//����׮����Ϣ��ȡ��ά�����������߷���
bool RouteCurveImpl::get2dPositionByMile(double mile, osg::Vec2d& position, osg::Vec2d& tangent)
{
	//Ҫ�ص�����
	std::vector<HorizontalCurveRouteData::FactorPointData>&  curveDatas = this->_horizontalCurveRouteData->_factorPointDatas;
	//Ҫ�ص㷽������
	std::vector<double>   tangentArrs = this->_factorPointsTangent;

	if (mile > curveDatas.back()._stakeNum || mile < 0 || tangentArrs.empty())
	{
		return false;
	}

	auto itr = curveDatas.begin();
	int index = 0;
	//��λmile���ĸ���������
	do
	{
		itr++;
		index++;
	} while (itr->_stakeNum <= mile);

	double Li = mile - (itr - 1)->_stakeNum;
	double curDirection = tangentArrs[index - 1];
	double postDirection = tangentArrs[index];

	if ((itr - 1)->_frontRadius == itr->_backRadius)
	{
		if ((itr - 1)->_frontRadius != MAX_CURVATURE)//Բ��
		{
			position = arcPointAlgorithem(itr - 1, Li, curDirection, tangent);
		}
		else//ֱ��
		{
			double coordX = (itr - 1)->_coordX;
			double coordY = (itr - 1)->_coordY;
			double resultX = coordX + Li * cos(postDirection);
			double resultY = coordY + Li * sin(postDirection);
			position = osg::Vec2d(resultX, resultY);
			tangent = osg::Vec2d(cos(curDirection), sin(curDirection));
		}
	}
	else//��������
	{
		position = transCurveAlgorithem(itr - 1, Li, curDirection, tangent);
	}
	return true;
}


//����׮����Ϣ��ȡ��ά�����������߷���
bool RouteCurveImpl::get3dPositionByMile(double mile, osg::Vec3d& point, osg::Vec2d& tangent)
{
	double elevation;
	osg::Vec2d   tempPoint;
	if (!get2dPositionByMile(mile, tempPoint, tangent))
	{
		return false;
	}
	if (!getElevation(mile, elevation))
	{
		return false;
	}
	point = osg::Vec3d(tempPoint.x(), tempPoint.y(), elevation);
	return true;
}

bool RouteCurveImpl::get2dPositionsByMile(std::vector<double>& miles, std::vector<osg::Vec2d>& points, std::vector<osg::Vec2d>& tangent)
{
	return true;

}

bool RouteCurveImpl::intersect(RouteCurveImpl* pOther, std::vector<osg::Vec2d>& points)
{

	return true;
}








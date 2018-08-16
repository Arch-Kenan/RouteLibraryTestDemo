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
	//判断曲线段类型
	int flag;//向右下偏转和左上偏转标志
	int flagDir = 1;  //曲线前进方向判断标志，从左到右为正， 从右到左为负
	if (curveDatas.empty())
	{
		return false;
	}
	for (auto ptr = curveDatas.begin(); ptr != curveDatas.end() - 1; ptr++)
	{
		if ((ptr + 1)->_backRadius == ptr->_frontRadius)//前后曲率半径是否相等
		{
			if ((ptr + 1)->_backRadius == MAX_CURVATURE)//相等且为无穷大的情况时，为直线
			{
				double lineRadian = atan2((ptr + 1)->_coordY - ptr->_coordY, ((ptr + 1)->_coordX - ptr->_coordX));
				this->_factorPointsTangent.push_back(lineRadian);
			}
			else //圆弧
			{
				double arclength = (ptr + 1)->_stakeNum - ptr->_stakeNum;
				double arcRadian = arclength / (ptr + 1)->_backRadius;//通过半径的偏转来判断偏转
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
			if (fabs(ptr->_frontRadius) > fabs((ptr + 1)->_backRadius))//顺延式缓和曲线,曲率半径逐渐减小
			{
				Ls = C / fabs((ptr + 1)->_backRadius);
				L1 = C / fabs(ptr->_frontRadius);
				flag = (ptr + 1)->_backRadius / fabs((ptr + 1)->_backRadius);//乘以半径再除以绝对值来判断曲线的偏转方向
				Len = L1;
			}
			else//逆延式缓和曲线,曲率半径逐渐增大
			{
				Ls = C / fabs(ptr->_frontRadius);
				L1 = C / fabs((ptr + 1)->_backRadius);
				flag = ptr->_frontRadius / fabs(ptr->_frontRadius);//乘以半径再除以绝对值来判断曲线的偏转方向
				Len = Ls;
				signFlag = -1;//控制deltatangent的正负，
			}
			//X,Y 都是为局部坐标，与大地坐标无关
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


//生成绘制的的插值点，插值点的数目由 DEVIDENUM 宏定义
bool RouteCurveImpl::initHorizontalDrawPoints()
{

	std::vector<HorizontalCurveRouteData::FactorPointData>&  factor_pnts = this->_horizontalCurveRouteData->_factorPointDatas;
	if (!initHorizontalTangent())
	{
		return false;
	}
	//求取桩号样条点的步幅值
	double deltaLen = (factor_pnts.back()._stakeNum - factor_pnts.front()._stakeNum) / DEVIDENUM;

	std::vector<double>& directionRadians = this->_factorPointsTangent;
	int index = 0;
	this->_drawHorizentalPointsData.push_back(osg::Vec2d(factor_pnts.begin()->_coordX, factor_pnts.begin()->_coordY));

	//初始切线方向
	double firstPointTangent = this->_factorPointsTangent[0];
	this->_drawPointsTangentData.push_back(osg::Vec2d(cos(firstPointTangent), sin(firstPointTangent)));

	for (std::vector<HorizontalCurveRouteData::FactorPointData>::iterator itr = factor_pnts.begin(); itr != factor_pnts.end() - 1; itr++)
	{
		if (itr->_frontRadius == (itr + 1)->_backRadius)
		{
			if (itr->_frontRadius != MAX_CURVATURE)//前后半径相等且不为无穷大时桩号所属类型为圆弧
			{
				getPointsOnArc(itr, _factorPointsTangent[index], deltaLen,
					this->_drawHorizentalPointsData, this->_drawPointsTangentData);
				index++;//操作执行后方位索引自增
			}
			else //前后半径相等且为无穷大时，所属桩号类型为直线
			{
				getPointsOnLine(itr, directionRadians[index], deltaLen,
					this->_drawHorizentalPointsData, this->_drawPointsTangentData);
				index++;//操作执行后方位索引自增
			}
		}
		else //前后半径不等时，所属桩号类型为缓和曲线
		{
			getPointsOnTransiLine(itr, directionRadians[index], deltaLen,
				this->_drawHorizentalPointsData, this->_drawPointsTangentData);
			index++;//操作执行后方位索引自增
		}
	}
	return true;
}



//获取竖曲线要素点的信息，并且将它存储在路线实现类中
//当前点的坡度由当前点和当前点索引自减1的点求出， 最后一个点的后项坡度由最后一个点和其索引自减1的点求出
bool RouteCurveImpl::initVerticalGradient()
{
	std::vector<VerticalCurveRouteData::VerticalCurveData>&  verticalPointsData =
		this->_verticalCurveRouteData->_verticalCurveDatas;

	//存储临时坡度信息
	double tempGradient;

	auto itr = verticalPointsData.begin();
	//第一个高程点默认为直线所以后前坡度一致
	tempGradient = ((itr + 1)->_elevation - itr->_elevation) / ((itr + 1)->_stakeNum - itr->_stakeNum);
	this->_verticalGradientData.push_back(tempGradient);

	for (; itr != verticalPointsData.end() - 1; itr++)
	{
		tempGradient = ((itr + 1)->_elevation - itr->_elevation) / ((itr + 1)->_stakeNum - itr->_stakeNum);

		this->_verticalGradientData.push_back(tempGradient);
	}
	//最后一个点高程点默认为直线， 即后坡度和前坡度一致
	tempGradient = (itr->_elevation - (itr - 1)->_elevation) / (itr->_stakeNum - (itr - 1)->_stakeNum);
	this->_verticalGradientData.push_back(tempGradient);

	return true;
}



//生成绘制高程的三维点数组，函数实现依赖竖曲线算法，生成的数据放在类的私有成员_routeCurvePositionData中
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
	int index = 0;//竖曲线关键点的前后索引
	int pointIndex = 0;//平曲线的绘制点的索引

	//第一个点特殊处理
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

//由平曲线上里程桩号获取高程信息,内部依赖竖曲线算法实现
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


//根据桩号信息获取二维点的坐标和切线方向
bool RouteCurveImpl::get2dPositionByMile(double mile, osg::Vec2d& position, osg::Vec2d& tangent)
{
	//要素点数组
	std::vector<HorizontalCurveRouteData::FactorPointData>&  curveDatas = this->_horizontalCurveRouteData->_factorPointDatas;
	//要素点方向数组
	std::vector<double>   tangentArrs = this->_factorPointsTangent;

	if (mile > curveDatas.back()._stakeNum || mile < 0 || tangentArrs.empty())
	{
		return false;
	}

	auto itr = curveDatas.begin();
	int index = 0;
	//定位mile在哪个曲线区间
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
		if ((itr - 1)->_frontRadius != MAX_CURVATURE)//圆弧
		{
			position = arcPointAlgorithem(itr - 1, Li, curDirection, tangent);
		}
		else//直线
		{
			double coordX = (itr - 1)->_coordX;
			double coordY = (itr - 1)->_coordY;
			double resultX = coordX + Li * cos(postDirection);
			double resultY = coordY + Li * sin(postDirection);
			position = osg::Vec2d(resultX, resultY);
			tangent = osg::Vec2d(cos(curDirection), sin(curDirection));
		}
	}
	else//缓和曲线
	{
		position = transCurveAlgorithem(itr - 1, Li, curDirection, tangent);
	}
	return true;
}


//根据桩号信息获取三维点的坐标和切线方向
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








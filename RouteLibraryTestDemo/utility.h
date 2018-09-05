//#pragma once
//
//#define _USE_MATH_DEFINES
//#include <cmath>
//#include <osg\Vec3d>
//#include "RouteCurveData.h"
//
//
////计算圆弧插值点和切线的基础算法
////iter为要素点的迭代器， pointTangent为所求点的切线
//osg::Vec2d  arcPointAlgorithem(std::vector<HorizontalCurveRouteData::FactorPointData>::iterator iter,
//							   double Li, double curDirection, osg::Vec2d& pointTangent)
//{
//	double coordX = iter->_coordX;
//	double coordY = iter->_coordY;
//	//圆心角
//	double centralRadian = Li / iter->_frontRadius;
//	double tangentRadian = 0;
//	double directionRadian = 0;
//
//	//圆心角除以2获得圆弧曲线的偏转角
//	double deflectionRadian = centralRadian / 2;
//	double chordLen = fabs(2 * (iter->_frontRadius)*sin(deflectionRadian)); //弦长
//
//	directionRadian = curDirection + deflectionRadian;
//	tangentRadian = curDirection + centralRadian;
//
//	pointTangent = osg::Vec2d(cos(tangentRadian), sin(tangentRadian));
//	double resultX = coordX + chordLen * cos(directionRadian);
//	double resultY = coordY + chordLen * sin(directionRadian);
//
//	return osg::Vec2d(resultX, resultY);
//}
//
//
//
////
////计算缓和曲线插值点和切线的基础算法
////iter为要素点的迭代器， pointTangent为所求点的切线
//osg::Vec2d transCurveAlgorithem1(std::vector<HorizontalCurveRouteData::FactorPointData>::iterator iter,
//	double Li, double curDirection, double postDirection, osg::Vec2d& pointTangent)
//{
//	double R = fabs((iter + 1)->_backRadius);
//	double Ls = ((iter + 1)->_stakeNum - iter->_stakeNum);
//	double coordX = iter->_coordX;
//	double coordY = iter->_coordY;
//	double tangentRadian = 0;
//	double tangentLine = pow(Li, 2) / (2 * R * Ls);//得到点的切线角
//
//	double deflectionRadian = tangentLine / 3;//得到偏转角	
//
//	double directionRadian;//获取点的方位角
//
//	if (postDirection > curDirection)//路线左偏(相对于当前点)加上偏转角
//	{
//		directionRadian = curDirection + deflectionRadian;
//		tangentRadian = curDirection + tangentLine;
//	}
//	else//路线右偏减去偏转角
//	{
//		directionRadian = curDirection - deflectionRadian;
//		tangentRadian = curDirection - tangentLine;
//	}
//
//	pointTangent = osg::Vec2d(cos(tangentRadian), sin(tangentRadian));
//
//	//double lengthX = Li - (pow(Li, 5) / (40 * pow(R* Ls, 2)));
//	//double lengthY = pow(Li, 3) / (6 * R * Ls);
//	//double lenC = sqrt(pow(lengthX, 2) + pow(lengthY, 2));//缓和曲线的弦长
//	double lenC = Li - pow(Li, 5) / (90 * pow(R * Ls, 2));
//
//	double resultX = coordX + lenC * cos(directionRadian);
//	double resultY = coordY + lenC * sin(directionRadian);
//
//	return osg::Vec2d(resultX, resultY);
//}
//
//
//
////计算缓和曲线插值点和切线的基础算法
////iter为要素点的迭代器， pointTangent为所求点的切线
////返回插值样条点
//osg::Vec2d transCurveAlgorithem2(std::vector<HorizontalCurveRouteData::FactorPointData>::iterator iter,
//	double Li, double curDirection, osg::Vec2d& pointTangent)
//{
//	double C = fabs(((iter + 1)->_stakeNum -iter->_stakeNum) * (iter + 1)->_backRadius* iter->_frontRadius / (iter->_frontRadius - (iter + 1)->_backRadius));
//	double L1 = C / fabs(iter->_frontRadius);
//	double Ls = C / fabs((iter + 1)->_backRadius);
//	//Li = 0.0;
//	int flag;
//	double startTangent;
//	//将以缓和曲线地点的切线为X轴的临时坐标系转换到大地坐标系
//	//乘以旋转矩阵
//	double Xi, Yi, lineTangent;
//	if (fabs(iter->_frontRadius) > fabs((iter+1)->_backRadius))//顺延式缓和曲线,曲率半径逐渐减小	
//	{
//		flag = (iter + 1)->_backRadius / fabs((iter + 1)->_backRadius);//乘以半径在除以绝对值来判断正负
//		startTangent = pow(L1, 2) / (2 * C) * flag;
//		curDirection -= startTangent;
//		double A = Li - (pow(L1 + Li, 5) - pow(L1, 5)) / (40 * C* C);
//		double B = (pow(L1 + Li, 3) - pow(L1, 3)) / (6 * C) * flag;
//		Xi = A * cos(curDirection) - B * sin(curDirection);
//		Yi = A * sin(curDirection) + B * cos(curDirection);
//		Xi += iter->_coordX;
//		Yi += iter->_coordY;
//		lineTangent = (pow(Li + L1, 2) - pow(L1, 2)) / (2 * C) + curDirection;
//	}
//	else//逆延式缓和曲线， 曲率半径逐渐增大
//	{
//		flag = iter->_frontRadius/ fabs(iter->_frontRadius);//乘以半径在除以绝对值来判断正负
//		Ls = C / fabs(iter->_frontRadius);
//		L1 = C / fabs((iter + 1)->_backRadius);
//		startTangent = pow(L1, 2) / (2 * C) *flag;
//		double postDirection = curDirection + ((pow(Ls, 2) - pow(L1, 2)) / (2 * C))*flag + startTangent;
//		double A = -(Ls - Li - L1 - (pow(Ls - Li, 5) - pow(L1, 5)) / (40 * C* C));
//		double B = ((pow(Ls - Li, 3) - pow(L1, 3)) / (6 * C)) * flag  ;
//		
//		//double temp = ((pow(Ls, 2) - pow(L1, 2)) / (2 * C))*flag;
//		//double temp1 = (pow(Ls - Li, 5) - pow(L1, 5)) / (40 * C* C);
//		//double temp3 = B * sin(postDirection);
//		//double temp4 = A * cos(postDirection);
//		//double temp5 = A * sin(postDirection);
//		//double temp6 = B * cos(postDirection);
//		//double temp7 = -((pow(Ls - Li, 7) - pow(L1, 7)) / (336 * C*C*C)) * flag;
//		Xi = A * cos(postDirection) - B * sin(postDirection);
//		Yi = A * sin(postDirection) + B * cos(postDirection);
//		Xi += (iter + 1)->_coordX;
//		Yi += (iter + 1)->_coordY;
//		lineTangent = (pow(Ls - Li, 2) - pow(Ls, 2)) / (2 * C) + curDirection;
//	}
//
//
//	pointTangent = osg::Vec2d(cos(lineTangent), sin(lineTangent));
//	return osg::Vec2d(Xi, Yi);
//}
//
//
//
//
////计算缓和曲线插值点和切线的基础算法
////iter为要素点的迭代器， pointTangent为所求点的切线
////返回插值样条点
//osg::Vec2d transCurveAlgorithem(std::vector<HorizontalCurveRouteData::FactorPointData>::iterator iter,
//	double Li, double curDirection,  osg::Vec2d& pointTangent)
//{
//	double C = fabs(((iter + 1)->_stakeNum - iter->_stakeNum) * (iter + 1)->_backRadius* iter->_frontRadius / (iter->_frontRadius - (iter + 1)->_backRadius));
//	double L1, Ls, X1, X2, Y1, Y2;
//	int flag;//向上向下偏转标志;
//	double lineTangent; //每个点的切线
//	if (fabs(iter->_frontRadius) > fabs((iter + 1)->_backRadius))//顺延式缓和曲线,曲率半径逐渐减小
//	{
//		 L1 = C / fabs(iter->_frontRadius);
//		 Ls = C / fabs((iter + 1)->_backRadius);
//		 flag = (iter + 1)->_backRadius / fabs((iter + 1)->_backRadius);//向上向下偏转标志;
//		//缓和曲线起点和终点坐标计算：
//		 X1 = L1 - pow(L1, 5) / (40 * C* C);
//		 Y1 = pow(L1, 3) / (6 * C) * flag;
//		 X2 = Ls - pow(Ls, 5) / (40 * C* C);
//		 Y2 = pow(Ls, 3) / (6 * C) * flag;
//		 Li = Li + L1;
//		 lineTangent = flag*(pow(Li, 2) - pow(L1, 2)) / (2 * C) + curDirection;
//	}
//	else
//	{
//		L1 = C / fabs((iter + 1)->_backRadius);
//		Ls = C / fabs(iter->_frontRadius);
//		flag = -(iter->_frontRadius / fabs(iter->_frontRadius));//向上向下偏转标志;
//		//缓和曲线起点和终点坐标计算：
//		X2 = (L1 - pow(L1, 5) / (40 * C* C));
//		Y2 = pow(L1, 3) / (6 * C) * flag;
//		X1 = (Ls - pow(Ls, 5) / (40 * C* C));
//		Y1 = pow(Ls, 3) / (6 * C) * flag;
//		Li = Ls - Li;
//		lineTangent = flag*(pow(Li, 2) - pow(Ls, 2)) / (2 * C) + curDirection;
//	}
//	double a = X2 - X1;
//	double b = Y2 - Y1;
//	//根据独立坐标和大地坐标的转换关系，求解坐标转换系数
//	double Cx = (iter + 1)->_coordX - iter->_coordX;
//	double Cy = (iter + 1)->_coordY - iter->_coordY;
//	double RaCos = (a*Cx + b * Cy) / (a*a + b * b);
//	double RaSin = (a* Cy - b * Cx) / (a*a + b * b);
//	double X0 = iter->_coordX - X1 * RaCos + Y1 * RaSin;
//	double Y0 = iter->_coordY - X1 * RaSin - Y1 * RaCos;
//	//缓和曲线任意点坐标计算：
//	double Xi = (Li - pow(Li, 5) / (40 * C*C));
//	double Yi = pow(Li, 3) / (6 * C) * flag;
//
//
//	double resultX = X0 + Xi * RaCos - Yi * RaSin;
//	double resultY = Y0 + Xi * RaSin + Yi * RaCos;
//	pointTangent = osg::Vec2d(cos(lineTangent), sin(lineTangent));
//	return osg::Vec2d(resultX, resultY);
//}
//
//
////计算圆弧段上所有绘制点的坐标和切线
////result_points为保存点数组, result_tangent为保存切线数组
//bool getPointsOnArc(std::vector<HorizontalCurveRouteData::FactorPointData>::iterator iter, double &curDirection,
//					double deltaLen, std::vector<osg::Vec2d> &result_points, std::vector<osg::Vec2d>& result_tangent)
//{
//	osg::Vec2d tempTangent;
//	int preIndex = (int)(iter->_stakeNum / deltaLen);
//	int postIndex = (int)((iter+1)->_stakeNum / deltaLen);
//
//	double Li = (++preIndex)* deltaLen - iter->_stakeNum;
//	while (preIndex <= postIndex)
//	{
//		result_points.push_back(arcPointAlgorithem(iter, Li, curDirection, tempTangent));
//		result_tangent.push_back(tempTangent);
//		Li += deltaLen;
//		preIndex++;
//	}
//	return true;
//}
//
//
////计算直线段上所有绘制点的坐标和切线
////result_points为保存点数组, result_tangent为保存切线数组
//bool getPointsOnLine(std::vector<HorizontalCurveRouteData::FactorPointData>::iterator iter, double curDirection,
//					 double deltaLen, std::vector<osg::Vec2d> &result_points, std::vector<osg::Vec2d>& result_tangent)
//{
//	int preIndex = (int)(iter->_stakeNum / deltaLen);
//	int postIndex = (int)((iter+1)->_stakeNum / deltaLen);
//
//	double Li = (++preIndex)* deltaLen - iter->_stakeNum;
//	double resultX = iter->_coordX + Li * cos(curDirection);
//	double resultY = iter->_coordY + Li * sin(curDirection);
//
//	osg::Vec2d  tempTangent(cos(curDirection), sin(curDirection));
//	while (preIndex <= postIndex)
//	{
//		result_points.push_back(osg::Vec2d(resultX, resultY));
//		result_tangent.push_back(tempTangent);
//		resultX += deltaLen * cos(curDirection);
//		resultY += deltaLen * sin(curDirection);
//		preIndex++;
//	}
//	return true;
//
//}
//
//
//
////计算缓和曲线段上所有绘制点的坐标和切线
////result_points为保存点数组, result_tangent为保存切线数组
//bool getPointsOnTransiLine(std::vector<HorizontalCurveRouteData::FactorPointData>::iterator iter, double &curDirection,
//						   double deltaLen, std::vector<osg::Vec2d> &result_points, std::vector<osg::Vec2d>& result_tangent)
//{
//	osg::Vec2d tempTangent;
//	int preIndex = (int)(iter->_stakeNum / deltaLen);
//	int postIndex = floor((iter+1)->_stakeNum / deltaLen);
//	double Li = (++preIndex)* deltaLen - iter->_stakeNum;
//
//	while (preIndex <= postIndex)
//	{
//		result_points.push_back(transCurveAlgorithem(iter, Li, curDirection, tempTangent));
//		result_tangent.push_back(tempTangent);
//		Li += deltaLen;
//		preIndex++;
//	}
//	return true;
//}
//
//
////
//////求取任意桩号的设计高程算法
////double getElevationAlgorithem(double stakeMile, double preGradient, double postGradient,
////							  double curStakeNum,double curElevation, double R)
////{
////	//计算竖曲线要素
////	double L = R * fabs(postGradient - preGradient);
////	double T = L / 2;
////	//计算设计高程
////	//竖曲线起点桩号
////	double startMile = curStakeNum - T;
////	//竖曲线起点高程
////	double startElevation = curElevation - T * preGradient;
////	//求取目标桩号的高程信息
////	double deltaMile = (stakeMile - startMile);
////	double retElevation = 0;
////
////	if (preGradient > postGradient)//凸型竖曲线
////	{
////		//切线高程—竖向距离
////		if (deltaMile > 0)
////		{
////			retElevation = (startElevation + deltaMile * preGradient) - pow(deltaMile, 2) / (2 * R);
////		}
////		else
////		{
////			retElevation = startElevation + deltaMile * preGradient;
////		}
////	}
////	else//凹型竖曲线
////	{
////		//切线高程 + 竖向高程
////		if (deltaMile > 0)
////		{
////			retElevation = (startElevation - deltaMile * preGradient) + pow(deltaMile, 2) / (2 * R);
////		}
////		else
////		{
////			retElevation = startElevation - deltaMile * preGradient;
////		}
////	}
////	return retElevation;
////}
//
//
//
////求取任意桩号的设计高程算法
//double getElevationAlgorithem(double stakeMile, double preGradient, double curGradient, double postGradient,
//	                        std::vector<VerticalCurveRouteData::VerticalCurveData>::iterator iter)
//{
//	double preS = iter->_stakeNum;
//	double preE = iter->_elevation;
//	double preR = iter->_circleRadius;
//
//	double curS = (iter + 1)->_stakeNum;
//	double curE = (iter + 1)->_elevation;
//	double curR = (iter + 1)->_circleRadius;
//
//
//	double retElevation = 0;
//
//
//	//计算竖曲线要素,各段切线长
//	double preT = preR * fabs(curGradient - preGradient) / 2;
//	double curT = curR * fabs(postGradient - curGradient) / 2;
//
//	//计算起点的设计高程
//	double startElevation = preE - preT * preGradient;//竖曲线起点切线高程
//	double endElevation = preE + preT * curGradient;//竖曲线终点切线高程
//
//	double startMile = preS - preT;//竖曲线起点桩号
//	double endMile = preS + preT;
//
//	double curStartMile = curS - curT;
//
//	//求取目标桩号的高程信息
//	double deltaMile = (stakeMile - startMile);
//
//	if (stakeMile < endMile)
//	{
//		if (preGradient > curGradient)//凸型竖曲线
//		{
//			retElevation = (startElevation + deltaMile * preGradient) - pow(deltaMile, 2) / (2 * preR);
//		}
//		else//凹型竖曲线
//		{
//			retElevation = (startElevation + deltaMile * preGradient) + pow(deltaMile, 2) / (2 * preR);
//		}
//		
//	}
//	else if( curR ==0.0 || stakeMile < curStartMile)//线段中间直线过渡
//	{
//
//		retElevation = preE + (stakeMile - preS)*curGradient;
//	}
//	else
//	{	 
//		if (curGradient < postGradient )//凹型竖曲线
//		{
//			retElevation = curE - (curS - stakeMile) * curGradient + pow((stakeMile - curStartMile), 2) / (2 * curR);
//		}
//		else//凸型竖曲线
//		{
//			retElevation = curE - (curS - stakeMile) * curGradient - pow((stakeMile - curStartMile), 2) / (2 * curR);
//		}
//	}
//	return retElevation;
//}
//
//

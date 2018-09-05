//#pragma once
//
//#define _USE_MATH_DEFINES
//#include <cmath>
//#include <osg\Vec3d>
//#include "RouteCurveData.h"
//
//
////����Բ����ֵ������ߵĻ����㷨
////iterΪҪ�ص�ĵ������� pointTangentΪ����������
//osg::Vec2d  arcPointAlgorithem(std::vector<HorizontalCurveRouteData::FactorPointData>::iterator iter,
//							   double Li, double curDirection, osg::Vec2d& pointTangent)
//{
//	double coordX = iter->_coordX;
//	double coordY = iter->_coordY;
//	//Բ�Ľ�
//	double centralRadian = Li / iter->_frontRadius;
//	double tangentRadian = 0;
//	double directionRadian = 0;
//
//	//Բ�Ľǳ���2���Բ�����ߵ�ƫת��
//	double deflectionRadian = centralRadian / 2;
//	double chordLen = fabs(2 * (iter->_frontRadius)*sin(deflectionRadian)); //�ҳ�
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
////���㻺�����߲�ֵ������ߵĻ����㷨
////iterΪҪ�ص�ĵ������� pointTangentΪ����������
//osg::Vec2d transCurveAlgorithem1(std::vector<HorizontalCurveRouteData::FactorPointData>::iterator iter,
//	double Li, double curDirection, double postDirection, osg::Vec2d& pointTangent)
//{
//	double R = fabs((iter + 1)->_backRadius);
//	double Ls = ((iter + 1)->_stakeNum - iter->_stakeNum);
//	double coordX = iter->_coordX;
//	double coordY = iter->_coordY;
//	double tangentRadian = 0;
//	double tangentLine = pow(Li, 2) / (2 * R * Ls);//�õ�������߽�
//
//	double deflectionRadian = tangentLine / 3;//�õ�ƫת��	
//
//	double directionRadian;//��ȡ��ķ�λ��
//
//	if (postDirection > curDirection)//·����ƫ(����ڵ�ǰ��)����ƫת��
//	{
//		directionRadian = curDirection + deflectionRadian;
//		tangentRadian = curDirection + tangentLine;
//	}
//	else//·����ƫ��ȥƫת��
//	{
//		directionRadian = curDirection - deflectionRadian;
//		tangentRadian = curDirection - tangentLine;
//	}
//
//	pointTangent = osg::Vec2d(cos(tangentRadian), sin(tangentRadian));
//
//	//double lengthX = Li - (pow(Li, 5) / (40 * pow(R* Ls, 2)));
//	//double lengthY = pow(Li, 3) / (6 * R * Ls);
//	//double lenC = sqrt(pow(lengthX, 2) + pow(lengthY, 2));//�������ߵ��ҳ�
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
////���㻺�����߲�ֵ������ߵĻ����㷨
////iterΪҪ�ص�ĵ������� pointTangentΪ����������
////���ز�ֵ������
//osg::Vec2d transCurveAlgorithem2(std::vector<HorizontalCurveRouteData::FactorPointData>::iterator iter,
//	double Li, double curDirection, osg::Vec2d& pointTangent)
//{
//	double C = fabs(((iter + 1)->_stakeNum -iter->_stakeNum) * (iter + 1)->_backRadius* iter->_frontRadius / (iter->_frontRadius - (iter + 1)->_backRadius));
//	double L1 = C / fabs(iter->_frontRadius);
//	double Ls = C / fabs((iter + 1)->_backRadius);
//	//Li = 0.0;
//	int flag;
//	double startTangent;
//	//���Ի������ߵص������ΪX�����ʱ����ϵת�����������ϵ
//	//������ת����
//	double Xi, Yi, lineTangent;
//	if (fabs(iter->_frontRadius) > fabs((iter+1)->_backRadius))//˳��ʽ��������,���ʰ뾶�𽥼�С	
//	{
//		flag = (iter + 1)->_backRadius / fabs((iter + 1)->_backRadius);//���԰뾶�ڳ��Ծ���ֵ���ж�����
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
//	else//����ʽ�������ߣ� ���ʰ뾶������
//	{
//		flag = iter->_frontRadius/ fabs(iter->_frontRadius);//���԰뾶�ڳ��Ծ���ֵ���ж�����
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
////���㻺�����߲�ֵ������ߵĻ����㷨
////iterΪҪ�ص�ĵ������� pointTangentΪ����������
////���ز�ֵ������
//osg::Vec2d transCurveAlgorithem(std::vector<HorizontalCurveRouteData::FactorPointData>::iterator iter,
//	double Li, double curDirection,  osg::Vec2d& pointTangent)
//{
//	double C = fabs(((iter + 1)->_stakeNum - iter->_stakeNum) * (iter + 1)->_backRadius* iter->_frontRadius / (iter->_frontRadius - (iter + 1)->_backRadius));
//	double L1, Ls, X1, X2, Y1, Y2;
//	int flag;//��������ƫת��־;
//	double lineTangent; //ÿ���������
//	if (fabs(iter->_frontRadius) > fabs((iter + 1)->_backRadius))//˳��ʽ��������,���ʰ뾶�𽥼�С
//	{
//		 L1 = C / fabs(iter->_frontRadius);
//		 Ls = C / fabs((iter + 1)->_backRadius);
//		 flag = (iter + 1)->_backRadius / fabs((iter + 1)->_backRadius);//��������ƫת��־;
//		//�������������յ�������㣺
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
//		flag = -(iter->_frontRadius / fabs(iter->_frontRadius));//��������ƫת��־;
//		//�������������յ�������㣺
//		X2 = (L1 - pow(L1, 5) / (40 * C* C));
//		Y2 = pow(L1, 3) / (6 * C) * flag;
//		X1 = (Ls - pow(Ls, 5) / (40 * C* C));
//		Y1 = pow(Ls, 3) / (6 * C) * flag;
//		Li = Ls - Li;
//		lineTangent = flag*(pow(Li, 2) - pow(Ls, 2)) / (2 * C) + curDirection;
//	}
//	double a = X2 - X1;
//	double b = Y2 - Y1;
//	//���ݶ�������ʹ�������ת����ϵ���������ת��ϵ��
//	double Cx = (iter + 1)->_coordX - iter->_coordX;
//	double Cy = (iter + 1)->_coordY - iter->_coordY;
//	double RaCos = (a*Cx + b * Cy) / (a*a + b * b);
//	double RaSin = (a* Cy - b * Cx) / (a*a + b * b);
//	double X0 = iter->_coordX - X1 * RaCos + Y1 * RaSin;
//	double Y0 = iter->_coordY - X1 * RaSin - Y1 * RaCos;
//	//�������������������㣺
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
////����Բ���������л��Ƶ�����������
////result_pointsΪ���������, result_tangentΪ������������
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
////����ֱ�߶������л��Ƶ�����������
////result_pointsΪ���������, result_tangentΪ������������
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
////���㻺�����߶������л��Ƶ�����������
////result_pointsΪ���������, result_tangentΪ������������
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
//////��ȡ����׮�ŵ���Ƹ߳��㷨
////double getElevationAlgorithem(double stakeMile, double preGradient, double postGradient,
////							  double curStakeNum,double curElevation, double R)
////{
////	//����������Ҫ��
////	double L = R * fabs(postGradient - preGradient);
////	double T = L / 2;
////	//������Ƹ߳�
////	//���������׮��
////	double startMile = curStakeNum - T;
////	//���������߳�
////	double startElevation = curElevation - T * preGradient;
////	//��ȡĿ��׮�ŵĸ߳���Ϣ
////	double deltaMile = (stakeMile - startMile);
////	double retElevation = 0;
////
////	if (preGradient > postGradient)//͹��������
////	{
////		//���߸̡߳��������
////		if (deltaMile > 0)
////		{
////			retElevation = (startElevation + deltaMile * preGradient) - pow(deltaMile, 2) / (2 * R);
////		}
////		else
////		{
////			retElevation = startElevation + deltaMile * preGradient;
////		}
////	}
////	else//����������
////	{
////		//���߸߳� + ����߳�
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
////��ȡ����׮�ŵ���Ƹ߳��㷨
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
//	//����������Ҫ��,�������߳�
//	double preT = preR * fabs(curGradient - preGradient) / 2;
//	double curT = curR * fabs(postGradient - curGradient) / 2;
//
//	//����������Ƹ߳�
//	double startElevation = preE - preT * preGradient;//������������߸߳�
//	double endElevation = preE + preT * curGradient;//�������յ����߸߳�
//
//	double startMile = preS - preT;//���������׮��
//	double endMile = preS + preT;
//
//	double curStartMile = curS - curT;
//
//	//��ȡĿ��׮�ŵĸ߳���Ϣ
//	double deltaMile = (stakeMile - startMile);
//
//	if (stakeMile < endMile)
//	{
//		if (preGradient > curGradient)//͹��������
//		{
//			retElevation = (startElevation + deltaMile * preGradient) - pow(deltaMile, 2) / (2 * preR);
//		}
//		else//����������
//		{
//			retElevation = (startElevation + deltaMile * preGradient) + pow(deltaMile, 2) / (2 * preR);
//		}
//		
//	}
//	else if( curR ==0.0 || stakeMile < curStartMile)//�߶��м�ֱ�߹���
//	{
//
//		retElevation = preE + (stakeMile - preS)*curGradient;
//	}
//	else
//	{	 
//		if (curGradient < postGradient )//����������
//		{
//			retElevation = curE - (curS - stakeMile) * curGradient + pow((stakeMile - curStartMile), 2) / (2 * curR);
//		}
//		else//͹��������
//		{
//			retElevation = curE - (curS - stakeMile) * curGradient - pow((stakeMile - curStartMile), 2) / (2 * curR);
//		}
//	}
//	return retElevation;
//}
//
//

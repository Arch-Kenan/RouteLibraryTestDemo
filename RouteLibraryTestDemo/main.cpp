#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <functional>


//inlcude other project
#include "compositePatten.h"








using namespace std;
//平曲线测试主程序
int main()
{
	curve*   ptrH = new hCurve();
	curve*   ptrV = new vCurve();
	deCurve  dPtr = new deCurveA(ptrH);
	dPtr.show();

	





	//for (auto itr = result2Dto3D.begin(); itr != result2Dto3D.end(); itr++)
	//{
	//	arrs2to3->push_back(osg::Vec3d(itr->x(), 0, itr->y()));
	//}

	//osg::ref_ptr<osg::DrawElementsUInt>    primitive = new osg::DrawElementsUInt(osg::PrimitiveSet::LINE_STRIP);
	//for (int i = 3; i < arrs2to3->size(); i++)
	//{
	//	primitive->push_back(i);
	//}
	//geom2to3->addPrimitiveSet(primitive.get());


	//viewer->setSceneData(root);
	//
	//// add the state manipulator
	//viewer->addEventHandler(new osgGA::StateSetManipulator(viewer->getCamera()->getOrCreateStateSet()));

	//// add the window size toggle handler
	//viewer->addEventHandler(new osgViewer::WindowSizeHandler);

	//// add the stats handler
	//viewer->addEventHandler(new osgViewer::StatsHandler);
	//viewer->realize();
	//viewer->run();

	return 0;

}




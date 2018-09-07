#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <thread>
//include osg lib
//#include "osgDB/ReadFile"
//#include "osgViewer/Viewer"
//#include "osg/MatrixTransform"
//#include "osgViewer/ViewerEventHandlers"
//#include "osgGA/StateSetManipulator"

//inlcude other project
//#include "../routeLib/tree.h"

#include "RouteCurveImpl.h"
#include "dynamic.h"
#include "mutiThread.h"
#include "list.h"





//平曲线测试主程序
int maintt()
{
	ListNode*   root = nullptr;
	ListNode*   root1 = nullptr;
	ListNode*	res = nullptr;

	std::vector<int>   arr = { 2, 4, 8, 10, 14, 16, 18 };
	std::vector<int>   arr1 = { 1 };
	//for (auto itr = arr.begin(); itr != arr.end(); itr++)
	//{
	//	insertNode(root, *itr);
	//}
	for (auto itr = arr1.begin(); itr != arr1.end(); itr++)
	{
		insertNode(root1, *itr);
	}
	res = Merge(root, root1);
	travalNode(res);







	/*test4(result2Dto3D, resultPnts, curveTangent);*/





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




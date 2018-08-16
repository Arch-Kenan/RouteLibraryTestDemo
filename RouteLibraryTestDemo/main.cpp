#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>

//include osg lib
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include "osg/MatrixTransform"
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>
#include "RouteCurveImpl.h"
#include "test.h"
#include <utility>
#include <queue>
#include <functional>
#include "copyCtor.h"




//平曲线测试主程序
int main()
{
	

	
	
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	osg::ref_ptr<osg::Group> root = new osg::Group;
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	root->addChild(geode.get());

	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	osg::ref_ptr<osg::Vec3dArray>   arrs = new osg::Vec3dArray;
	geom->setVertexArray(arrs);
	geode->addDrawable(geom);
	
	osg::Vec3d   cenPnt(50, 0, 50);
	osg::Vec3d   p0(40, 0.0, 0);
	osg::Vec3d   move = p0 - cenPnt;
	arrs->push_back(cenPnt);
	arrs->push_back(p0);
	arrs->push_back(osg::Vec3d(0, 0, 0));
	double delta = 0.3;
	double roateRadian = 0;
	osg::Matrix    mat;
	osg::Matrix    mat1;
	osg::Quat      makeQuat;
	mat.makeTranslate(-cenPnt);
	p0 = mat.preMult(p0);
	arrs->push_back(p0);
	mat1.makeTranslate(cenPnt);
	for (int i = 0; i < 8; i++)
	{
		makeQuat.makeRotate(roateRadian, osg::Vec3d(0, 1,0));
		mat.makeRotate(makeQuat);
		osg::Vec3d   tempPnt =mat1.preMult(mat.preMult(p0));
		
		/*tempPnt = mat.preMult(tempPnt);*/
		arrs->push_back(tempPnt);
		roateRadian += delta;
	}
	//test(*arrs);
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, arrs->size()));

	osg::ref_ptr<osg::Geometry> geom2to3 = new osg::Geometry;
	osg::ref_ptr<osg::Vec3dArray>   arrs2to3 = new osg::Vec3dArray;
	geom2to3->setVertexArray(arrs2to3);
	geode->addDrawable(geom2to3);

	std::vector<osg::Vec3d>  resultPnts;
	std::vector<osg::Vec2d>  result2Dto3D;
	std::vector<osg::Vec2d>  curveTangent;

	test4(result2Dto3D, resultPnts, curveTangent);





	for (auto itr = result2Dto3D.begin(); itr != result2Dto3D.end(); itr++)
	{
		arrs2to3->push_back(osg::Vec3d(itr->x(), 0, itr->y()));
	}

	osg::ref_ptr<osg::DrawElementsUInt>    primitive = new osg::DrawElementsUInt(osg::PrimitiveSet::LINE_STRIP);
	for (int i = 3; i < arrs2to3->size(); i++)
	{
		primitive->push_back(i);
	}
	geom2to3->addPrimitiveSet(primitive.get());


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




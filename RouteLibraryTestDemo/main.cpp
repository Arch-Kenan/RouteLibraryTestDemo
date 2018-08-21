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
#include <utility>
#include <queue>
#include <functional>
#include "copyCtor.h"
#include "testRoute.h"


#include <stdio.h>
#include <stdlib.h>

const int N = 20;   
int q[N];         
int cont = 0;     
				  
void print(int n)
{
	int i, j;
	cont++;
	printf("第%d个解：", cont);
	for (i = 1; i <= n; i++)
		printf("(%d,%d) ", i, q[i]);
	printf("\n");
	for (i = 1; i <= n; i++)        //行
	{
		for (j = 1; j <= n; j++)    //列
		{
			if (q[i] != j)
				printf("x ");
			else
				printf("Q ");
		}
		printf("\n");
	}
}


int find(int i, int k)
{
	int j = 1;
	while (j < i)  
	{
		
		if (q[j] == k || abs(j - i) == abs(q[j] - k))
			return 0;
		j++;
	}
	return 1;
}


void place(int k, int n)
{
	int j;
	if (k > n)
		print(n);
	else
	{
		for (j = 1; j <= n; j++)   //试探第k行的每一个列
		{
			if (find(k, j))
			{
				q[k] = j;
				place(k + 1, n);  //递归总是在成功完成了上次的任务的时候才做下一个任务
			}
		}
	}
}

int main(void)
{
	int n;
	printf("请输入皇后的个数(n<=20),n=:");
	scanf("%d", &n);
	if (n > 20)
		printf("n值太大，不能求解!\n");
	else
	{
		printf("%d皇后问题求解如下(每列的皇后所在的行数):\n", n);
		place(1, n);        //问题从最初状态解起
		printf("\n");
	}
	system("pause");
	return 0;
}



//平曲线测试主程序
int maintt()
{

	int arr[] = { 5, 0, 9, 4, 12, 39, 34, 21, 78, 31 };
	insertTest(arr, 10);
	for (auto i : arr)
	{
		cout << i << "   ";
	}

	
	
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




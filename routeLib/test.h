#pragma once
#include "stdafx.h"
#include <iostream>
#include "macro.h"

// Minimum and maximum macros
#define __max(a,b) (((a) > (b)) ? (a) : (b))
#define __min(a,b) (((a) < (b)) ? (a) : (b))

struct ROUTELIB_API BTnode
{
	int num;
	int height;
	BTnode* lchild;
	BTnode* rchild;

};

int ROUTELIB_API GetHeight(BTnode* root);
bool ROUTELIB_API LLRotate(BTnode* &root);
bool ROUTELIB_API RRRotate(BTnode* &root);
bool ROUTELIB_API LRRotate(BTnode* &root);
bool ROUTELIB_API RLRotate(BTnode* &root);
bool ROUTELIB_API InsertNode(BTnode* &root, int key);
bool ROUTELIB_API DeleteNode(BTnode* &root, int key);
//bool DeleteNode(BTnode* &root, int key);
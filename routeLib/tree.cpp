#include "stdafx.h"
#include "tree.h"
#include <stack>

int GetHeight(BTnode* root)
{
	if (root)
	{
		return root->height;
	}
	return 0;
}

bool LLRotate(BTnode* &root)
{
	BTnode* tempRef = nullptr;
	tempRef = root->lchild;
	root->lchild = tempRef->rchild;
	tempRef->rchild = root;
	root->height = __max(GetHeight(root->lchild), GetHeight(root->rchild)) + 1;
	tempRef->height = __max(GetHeight(tempRef->lchild), GetHeight(tempRef->rchild)) + 1;
	std::cout << "调用LL旋转:" << root->num << std::endl;
	root = tempRef;
	
	return true;
}

bool RRRotate(BTnode* &root)
{
	BTnode* tempRef = nullptr;
	tempRef = root->rchild;
	root->rchild = tempRef->lchild;
	tempRef->lchild = root;
	root->height = __max(GetHeight(root->lchild), GetHeight(root->rchild)) + 1;
	tempRef->height =__max( GetHeight(tempRef->lchild), GetHeight(tempRef->rchild)) + 1;

	root = tempRef;
	return true;
}

bool LRRotate(BTnode* &root)
{
	RRRotate(root->lchild);
	LLRotate(root);
	return true;
}

bool RLRotate(BTnode* &root)
{
	LLRotate(root->rchild);
	RRRotate(root);
	return true;
}

bool InsertNode(BTnode* &root, int key)
{
	BTnode* tempObj = nullptr;
	if (!root)
	{
		tempObj = (BTnode*)malloc(sizeof(BTnode));
		tempObj->num = key;
		tempObj->height = 1;
		tempObj->lchild = nullptr;
		tempObj->rchild = nullptr;
		root = tempObj;
		return true;
	}
	else if (key == root->num)
	{
		return false;
	}
	else if (key < root->num)
	{
		if (!(InsertNode(root->lchild, key)))
		{
			return false;
		}
		else
		{
			root->height = __max(GetHeight(root->lchild), GetHeight(root->rchild)) + 1;
			if ( (GetHeight(root->lchild) - GetHeight(root->rchild)) == 2 )
			{
				if (GetHeight(root->lchild->lchild) > GetHeight(root->lchild->rchild))
				{
					LLRotate(root);
				}
				else
				{
					LRRotate(root);
				}
			}
			return true;
		}
	}
	else 
	{
		if (!InsertNode(root->rchild, key))
		{
			return false;
		}
		else
		{
			root->height = __max(GetHeight(root->lchild), GetHeight(root->rchild)) + 1;
			if (GetHeight(root->lchild) - GetHeight(root->rchild) == -2)
			{
				if (GetHeight(root->rchild->rchild) > GetHeight(root->rchild->lchild))
				{
					RRRotate(root);
				}
				else
				{
					RLRotate(root);
				}
			}
			return true;
		}
	}
}

bool DeleteNode(BTnode* &root,int key)
{
	if (!root)
	{
		return false;
	}
	else if (key == root->num)
	{
		if ( !(root->lchild) && !(root->rchild) )
		{
			free(root);
			root = nullptr;
		}
		else if (!(root->rchild))
		{
			BTnode* temp = nullptr;
			temp = root;
			root = root->lchild;
			free(temp);
		}
		else if (!(root->lchild))
		{
			BTnode* temp = nullptr;
			temp = root;
			root = root->rchild;
			free(temp);
		}
		else
		{
			if (GetHeight(root->lchild) > GetHeight(root->rchild) )
			{
				BTnode* tempPre = nullptr;
				tempPre = root->lchild;
				while (tempPre->rchild)
				{
					tempPre = tempPre->rchild;
				}
				root->num = tempPre->num;
				DeleteNode(root->lchild, tempPre->num);
			}
			else
			{
				BTnode* success = nullptr;
				success = root->rchild;
				while (success->lchild)
				{
					success = success->lchild;
				}
				root->num = success->num;
				DeleteNode(root->rchild, success->num);
			}
		}
		return true;

	}
	else if (key < root->num)
	{
		if (!(DeleteNode(root->lchild, key)) )
		{
			return false;
		}
		else
		{
			//root->height = __max(GetHeight(root->lchild), GetHeight(root->rchild)) + 1;
			//if (GetHeight(root->lchild) - GetHeight(root->rchild) == -2)
			//{
			//	if (GetHeight(root->rchild->lchild) > GetHeight(root->rchild->rchild))
			//	{
			//		RLRotate(root);
			//	}
			//	else
			//	{
			//		RRRotate(root);
			//	}
			//}
			return true;
		}
	}
	else
	{
		if (!(DeleteNode(root->rchild, key)))
		{
			return false;
		}
		else
		{
			//root->height = __max(GetHeight(root->lchild), GetHeight(root->rchild)) + 1;
			//if (GetHeight(root->lchild) - GetHeight(root->rchild) == 2)
			//{
			//	if (GetHeight(root->lchild->lchild)> GetHeight(root->lchild->rchild))
			//	{
			//		LLRotate(root);
			//	}
			//	else
			//	{
			//		LRRotate(root);
			//	}
			//}
			return true;
		}
	}
}


void preTraval(BTnode* root)
{
	if (!root)
		return;
	std::stack<BTnode*> stack_temp;
	stack_temp.push(root);
	int index = 0;
	while (!stack_temp.empty())
	{
		root = stack_temp.top();
		stack_temp.pop();
		while (root)
		{
			std::cout << index++ << "浏览节点:" << root->num << std::endl;
			if (root->rchild)
				stack_temp.push(root->rchild);
			root = root->lchild;
		}
	}
}
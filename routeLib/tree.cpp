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
	/*std::cout << "调用LL旋转:" << root->num << std::endl;*/
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

//bool InsertNode(BTnode* &root, int key)
//{
//	if (root == nullptr)
//	{
//		root = new BTnode(key, 1);
//		return true;
//	}
//	else if (root->num == key)
//	{
//		return false;
//	}
//	else
//	{
//		if (key < root->num)
//		{
//			if (!InsertNode(root->lchild, key))
//			{
//				return false;
//			}
//			else
//			{
//				//root->height = cMAX(GetHeight(root->lchild), GetHeight(root->rchild)) + 1;
//				if (GetHeight(root->lchild) - GetHeight(root->rchild) == 2)
//				{
//					if (GetHeight(root->lchild->lchild) > GetHeight(root->lchild->rchild))
//					{
//						LLRotate(root);
//					}
//					else
//					{
//						LRRotate(root);
//					}
//				}
//				root->height = __max(GetHeight(root->lchild), GetHeight(root->rchild)) + 1;
//
//			}
//		}
//		else
//		{
//			if (!InsertNode(root->rchild, key))
//			{
//				return false;
//			}
//			else
//			{
//				//root->height = cMAX(GetHeight(root->lchild), GetHeight(root->rchild)) + 1;
//				if (GetHeight(root->rchild) - GetHeight(root->lchild) == 2)
//				{
//					if (GetHeight(root->rchild->rchild) > GetHeight(root->rchild->lchild))
//					{
//						RRRotate(root);
//					}
//					else
//					{
//						RLRotate(root);
//					}
//				}
//				root->height = __max(GetHeight(root->lchild), GetHeight(root->rchild)) + 1;
//			}
//		}
//		return true;
//	}
//
//}



//bool DeleteNode(BTnode* &root,int key)
//{
//	if (!root)
//	{
//		return false;
//	}
//	else if (key == root->num)
//	{
//		if ( !(root->lchild) && !(root->rchild) )
//		{
//			delete root;
//			root = nullptr;
//		}
//		else if (!(root->rchild))
//		{
//			BTnode* temp = nullptr;
//			temp = root;
//			root = root->lchild;
//			delete temp;
//		}
//		else if (!(root->lchild))
//		{
//			BTnode* temp = nullptr;
//			temp = root;
//			root = root->rchild;
//			delete temp;
//		}
//		else
//		{
//			if (GetHeight(root->lchild) > GetHeight(root->rchild) )
//			{
//				BTnode* tempPre = nullptr;
//				tempPre = root->lchild;
//				while (tempPre->rchild)
//				{
//					tempPre = tempPre->rchild;
//				}
//				root->num = tempPre->num;
//				DeleteNode(root->lchild, tempPre->num);
//			}
//			else
//			{
//				BTnode* success = nullptr;
//				success = root->rchild;
//				while (success->lchild)
//				{
//					success = success->lchild;
//				}
//				root->num = success->num;
//				DeleteNode(root->rchild, success->num);
//			}
//		}
//		return true;
//
//	}
//	else if (key < root->num)
//	{
//		if (!(DeleteNode(root->lchild, key)) )
//		{
//			return false;
//		}
//		else
//		{
//			//root->height = __max(GetHeight(root->lchild), GetHeight(root->rchild)) + 1;
//			//if (GetHeight(root->lchild) - GetHeight(root->rchild) == -2)
//			//{
//			//	if (GetHeight(root->rchild->lchild) > GetHeight(root->rchild->rchild))
//			//	{
//			//		RLRotate(root);
//			//	}
//			//	else
//			//	{
//			//		RRRotate(root);
//			//	}
//			//}
//			return true;
//		}
//	}
//	else
//	{
//		if (!(DeleteNode(root->rchild, key)))
//		{
//			return false;
//		}
//		else
//		{
//			//root->height = __max(GetHeight(root->lchild), GetHeight(root->rchild)) + 1;
//			//if (GetHeight(root->lchild) - GetHeight(root->rchild) == 2)
//			//{
//			//	if (GetHeight(root->lchild->lchild)> GetHeight(root->lchild->rchild))
//			//	{
//			//		LLRotate(root);
//			//	}
//			//	else
//			//	{
//			//		LRRotate(root);
//			//	}
//			//}
//			return true;
//		}
//	}
//}


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
			std::cout << index++ << "浏览节点:" << root->height << std::endl;
			if (root->rchild)
				stack_temp.push(root->rchild);
			root = root->lchild;
		}
	}
}

//void preTraval(BTnode* root)
//{
//	if (root)
//	{
//		std::stack<BTnode*>   sStack;
//		sStack.push(root);
//		BTnode*  head = nullptr;
//		while (!sStack.empty())
//		{
//			head = sStack.top();
//			sStack.pop();
//			while (head)
//			{
//				std::cout << head->height << std::endl;
//				sStack.push(head->rchild);
//				head = head->lchild;
//			}
//		}
//	}
//}

//void midTraval(BTnode* root)
//{
//	if (!root)
//	{
//		return;
//	}
//
//	midTraval(root->lchild);
//	std::cout << root->num << std::endl;
//	midTraval(root->rchild);
//}

void midTraval(BTnode* root)
{
	if (!root)
	{
		return;
	}
	BTnode*  head = root;
	std::stack<BTnode*>   sStack;

	while (head)
	{
		sStack.push(head);
		head = head->lchild;
	}

	while(!sStack.empty())
	{
		head = sStack.top();
		std::cout << head->num << std::endl;
		sStack.pop();
		head = head->rchild;
		while (head)
		{
			sStack.push(head);
			head = head->lchild;
		}
	}

}


bool  InsertNode(BTnode* &root, int key)
{
	if (!root)
	{
		root = new BTnode(key, 0);
		return true;
	}
	if (root->num == key)
	{
		return false;
	}
	else if (key < root->num)
	{
		if (!InsertNode(root->lchild, key))
		{
			return false;
		}
		int lh = GetHeight(root->lchild);
		int rh = GetHeight(root->rchild);
		root->height = max(lh, rh) + 1;
		if (lh - rh > 1)
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
	else
	{
		if (!InsertNode(root->rchild, key))
		{
			return false;
		}
		int lh = GetHeight(root->lchild);
		int rh = GetHeight(root->rchild);
		root->height = max(lh, rh) + 1;
		if (rh - lh > 1)
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



bool  DeleteNode(BTnode* &root, int key)
{
	if (!root)
	{
		return false;
	}
	if (key < root->num)
	{
		if (!DeleteNode(root->lchild, key))
		{
			return false;
		}
		int lh = GetHeight(root->lchild);
		int rh = GetHeight(root->rchild);
		root->height = max(lh, rh) + 1;
		if (rh - lh > 1)
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
	else if (key > root->num)
	{
		if (!DeleteNode(root->rchild, key))
		{
			return false;
		}
		int lh = GetHeight(root->lchild);
		int rh = GetHeight(root->rchild);
		root->height = max(lh, rh) + 1;
		if (lh - rh > 1)
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
	else
	{
		if (root->lchild == nullptr && root->rchild == nullptr)
		{
			delete root;
			root = nullptr;
		}
		else
		{
			BTnode* head = nullptr;
			if (GetHeight(root->lchild) > GetHeight(root->rchild))
			{
				head = root->lchild;
				while (head->rchild)
				{
					head = head->rchild;
				}
				root->num = head->num;
				DeleteNode(root->lchild, head->num);
			}
			else
			{
				head = root->rchild;
				while (head->lchild)
				{
					head = head->lchild;
				}
				root->num = head->num;
				DeleteNode(root->rchild, head->num);
			}
			root->height = max(GetHeight(root->lchild), GetHeight(root->rchild)) + 1;
		}
		
		return true;
	}
}

void reverseMidTraval(BTnode* root)
{
	if (!root)
	{
		return;
	}
	reverseMidTraval(root->rchild);
	std::cout << root->num << std::endl;
	reverseMidTraval(root->lchild);
}

//void  reverse(BTnode* &root)
//{
//	if (!root)
//	{
//		return;
//	}
//	BTnode* temp = root->lchild;
//	root->lchild = root->rchild;
//	root->rchild = temp;
//	reverse(root->lchild);
//	reverse(root->rchild);
//
//}


void  reverse(BTnode* &root)
{
	std::stack<BTnode*>   sStack;
	sStack.push(root);
	while (!sStack.empty())
	{
		BTnode* head = sStack.top();
		sStack.pop();
		if (head->lchild)
			sStack.push(head->lchild);
		if (head->rchild)
			sStack.push(head->rchild);
		BTnode* temp = head->lchild;
		head->lchild = head->rchild;
		head->rchild = temp;
	}
}
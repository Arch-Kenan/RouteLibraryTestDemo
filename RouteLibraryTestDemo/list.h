#pragma once

struct ListNode
{
public:
	ListNode(int num) : val(num), next(nullptr) {};
	int val;
	struct ListNode *next;

};

ListNode* Merge(ListNode *pLeft, ListNode *pRight)
{
	ListNode*   head = nullptr;
	//if (pLeft == nullptr)
	//{
	//	if (!pRight)
	//		head = pLeft;
	//	else
	//		head = pRight;
	//}
	//if (pLeft != nullptr)
	//{
	//	if (!pRight)
	//		head = pLeft;
	//	else
	//	{
	//		if (pLeft->val < pRight->val)
	//		{
	//			head = pLeft;
	//			pLeft = pLeft->next;
	//		}
	//		else
	//		{
	//			head = pRight;
	//			pRight = pRight->next;
	//		}
	//	}
	//}
	if (pLeft == pRight)
	{
		if (pLeft == nullptr)
			return pLeft;
	}
	if (pLeft || pRight)
	{
		if (pRight && pLeft)
		{
			if (pLeft->val < pRight->val)
			{
				head = pLeft;
				pLeft = pLeft->next;
			}
			else
			{
				head = pRight;
				pRight = pRight->next;
			}
		}
		else
		{
			if (pLeft)
				return pLeft;
			else
				return pRight;

		}
	}
	ListNode*   cur = head;
	while (pLeft && pRight)
	{
		if (pLeft->val < pRight->val)
		{
			cur->next = pLeft;
			pLeft = pLeft->next;
		}
		else
		{
			cur->next = pRight;
			pRight = pRight->next;
		}
		cur = cur->next;
	}
	if (!pLeft)
	{
		cur->next = pRight;
	}
	if (!pRight)
	{
		cur->next = pLeft;
	}
	return   head;
}



//ListNode*   root = nullptr;
//std::vector<int>   arr = { 2, 4, 8, 10, 14, 16, 18 };
//for (auto itr = arr.begin(); itr != arr.end(); itr++)
//{
//	insertNode(root, *itr);
//}
//ReverseList(root);
//travalNode(root);
void insertNode(ListNode* &root, int key)
{
	if (root == nullptr)
	{
		root = new ListNode(key);
	}
	else
	{
		ListNode*  head = root;
		while (head->next)
		{
			head = head->next;
		}
		head->next = new ListNode(key);
	}

	return;
}

void travalNode(ListNode* root)
{
	while (root)
	{
		std::cout << root->val << std::endl;
		root = root->next;
	}
}

//void  ReverseList(ListNode* &pHead)
//{
//	ListNode *pReversedHead = nullptr;
//	ListNode *pNode = pHead;
//	ListNode *pPrev = nullptr;
//	ListNode *pNext = nullptr;
//
//	// pPrev -> pNode -> pNext;
//	while (pNode != nullptr)
//	{
//		pNext = pNode->next;        //  保存其下一个节点
//
//		pNode->next = pPrev;        //  指针指向反转
//
//		pPrev = pNode;              //  保存前一个指针
//		pNode = pNext;              //  递增指针, 指向下一个结点
//	}
//	pHead = pPrev;
//	return;
//}

//void  ReverseList(ListNode* &pHead)
//{
//	ListNode* cur = pHead;
//	ListNode* next = nullptr;
//	ListNode* pre = nullptr;
//	while (cur)
//	{
//		next = cur->next;
//
//		cur->next = pre;
//		
//		pre = cur;
//		cur = next;
//	}
//	pHead = pre;
//	return;
//}

void  ReverseList(ListNode* &pHead)
{
	if (pHead == nullptr)
	{
		return ;
	}

	ListNode *pNode = pHead;
	ListNode *nNode = nullptr;
	ListNode *pNext = nullptr;


	nNode = pNode;
	///////////////

	pNode = pNode->next;           //  保存next指向，防止丢失

								   ///////////////
	nNode->next = nullptr;



	while (pNode != nullptr)
	{
		pNext = pNode->next;       
						
		pNode->next = nNode;
		nNode = pNode;
		pNode = pNext;          //  移动指针
	}
	pHead = nNode;
	return ;
	
}




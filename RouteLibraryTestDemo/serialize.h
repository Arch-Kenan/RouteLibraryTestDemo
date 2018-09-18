#pragma once
#include "stdafx.h"
#include <string.h>
#include <vector>
#include <stack>
#include <iostream>
#include <sstream>


using namespace std;
struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

std::string serialize(TreeNode* root)
{
	if (root == nullptr)
	{
		return "#";
	}
	char  chr[20];
	sprintf(chr, "%d", root->val);
	std::string ss = chr;
	ss += serialize(root->left);
	ss += serialize(root->right);
	return ss;
}

TreeNode*  deseri(std::vector<TreeNode*>& arrs)
{
	int index = 0;
	TreeNode* root = arrs[0];
	TreeNode*   head = arrs[0];
	std::stack<TreeNode*>   sStack;
	if (head)
	{
		sStack.push(head);
	}
	TreeNode* temp = arrs[++index];
	while (!sStack.empty())
	{
		if (temp)
		{
			if (head)
			{
				head->left = temp;
				sStack.push(temp);
				head = temp;
				temp = arrs[++index];
			}
		}
		else
		{
			//head->left = nullptr;//temp = nullptr
			head = sStack.top();
			sStack.pop();

			temp = arrs[++index];
			head->right = temp;
			head = temp;
			if (head)
				temp = arrs[++index];
		}
	}
	return root;
}

TreeNode* deserialize(std::string data)
{
	if (data.empty())
	{
		return nullptr;
	}
	std::vector<TreeNode*>    arrsTN;
	std::stringstream   sStr(data);
	std::string word;
	while (sStr >> word)
	{
		if (word == "#")
		{
			arrsTN.push_back(nullptr);
		}
		else
		{
			int num = std::atoi(word.c_str());
			arrsTN.push_back(new TreeNode(num));
		}
	}
	TreeNode* root = deseri(arrsTN);
	return root;
}

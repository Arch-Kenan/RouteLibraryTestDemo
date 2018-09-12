#pragma once
#include "stdafx.h"
#include <iostream>
#include <thread>

#include <list>
#include <mutex>
#include <algorithm>

#ifndef _UNISTD_H
#define _UNISTD_H
#include <io.h>
#include <process.h>
#endif // !_UNISTD_H

std::list<int>    listN;
std::mutex        addMutex;

void adToList(int num)
{
	//std::lock_guard<std::mutex>  guard(addMutex);
	addMutex.lock();
	listN.push_back(num);
	addMutex.unlock();
}

bool findKey(int Key)
{
	std::lock_guard<std::mutex>  guard(addMutex);
	return std::find(listN.begin(), listN.end(), Key) != listN.end();
}



std::list<int> some_list;    // 1
std::mutex some_mutex;    // 2

void add_to_list(int new_value)
{
	std::lock_guard<std::mutex> guard(some_mutex);    // 3
	some_list.push_back(new_value);
}

bool list_contains(int value_to_find)
{
	std::lock_guard<std::mutex> guard(some_mutex);    // 4
	return std::find(some_list.begin(), some_list.end(), value_to_find) != some_list.end();
}

// gujinjin 08/10/05_06
// 避免死锁银行家算法的C++ 编程实现

#include<iostream>
using namespace std;

// p 进程数，r 资源种类
#define p 4
#define r 3


///*-----------------------------------------------*/
///*输入函数*/
///*-----------------------------------------------*/
////a-max,b-allocation,c-need,d-available
//void input(int a[p][r], int b[p][r], int c[p][r], int d[r])
//{
//	int i, j;
//	cout << "* input max data:\n";
//	for (i = 0; i < p; i++)
//		for (j = 0; j < r; j++)cin >> a[i][j];
//	cout << "* input allocation data:\n";
//	for (i = 0; i < p; i++)
//		for (j = 0; j < r; j++)cin >> b[i][j];
//	cout << "* input need data:\n";
//	for (i = 0; i < p; i++)
//		for (j = 0; j < r; j++)cin >> c[i][j];
//	cout << "* input available data:\n";
//	for (j = 0; j < r; j++)cin >> d[j];
//}
//
///*-----------------------------------------------*/
///*比较函数*/
///*-----------------------------------------------*/
////比较结果为m中的元素全大于n中的元素返回1，否则返回0
//int com(int m[r], int n[r])
//{
//	int i, flag = 0;
//	for (i = 0; i < r; i++)
//		if (m[i] < n[i])
//		{
//			flag = 1;
//			break;
//		}
//	if (flag == 1)	return(0);
//	else return(1);
//}
//
//
///*-----------------------------------------------*/
///*安全性检验函数*/
///*-----------------------------------------------*/
////b、c、d意义同上
//int stest(int b[p][r], int c[p][r], int d[r])
//{
//	int i, j, k, l, flag = 0, flag1 = 0;
//	int t[r], finish[p], dd[r];
//	for (i = 0; i < p; i++)finish[i] = 0;//finish为1即表示available满足某一进程并让其实现
//
//	for (i = 0; i < r; i++) dd[i] = d[i];
//	cout << "分配序列：\n";
//	for (k = 0; k < p; k++)            //全搜索，直至实现或不可能实现
//	{
//		for (i = 0; i < p; i++)
//		{
//			if (finish[i] == 1)continue;
//			else
//			{
//				for (j = 0; j < r; j++)t[j] = c[i][j];
//				if (com(dd, t))
//				{
//					finish[i] = 1;
//					cout << i + 1 << '\t';
//					flag = 1;
//					for (l = 0; l < r; l++)dd[l] = dd[l] + b[i][l];
//					break;
//				}
//			}
//			if (flag == 1)break;
//		}
//	}
//	cout << '\n';
//	for (l = 0; l < p; l++)
//	{
//		//cout<<finish[l]<<endl;
//		if (finish[l] == 0)flag1 = 1;
//	}
//	//cout<<flag1<<endl;
//	if (flag1 == 0)return(1);    //flag1为记录finish是否有0存在的标记，当flag1=0时，安全
//	else return(0);
//}
//
//
///*-----------------------------------------------*/
///*申请进程后的安全性检验函数*/
///*-----------------------------------------------*/
////req-request,n-第n个进程申请资源
//void rtest(int b[p][r], int c[p][r], int d[r], int req[r], int n)
//{
//	int i, j;
//	int t[r];
//	n = n - 1;
//	for (i = 0; i < r; i++)t[i] = c[n][i];
//	if (com(d, req) && com(t, req))//对available，request进行比较
//	{
//		for (j = 0; j < r; j++)
//		{
//			b[n][j] = b[n][j] + req[j];
//			c[n][j] = c[n][j] - req[j];
//			d[j] = d[j] - req[j];
//		}
//		if (stest(b, c, d))cout << "允许" << n + 1 << "个进程申请资源！\n";
//		else
//		{
//			cout << "不允许" << n + 1 << "个进程申请资源！\n";
//
//			cout << "恢复以前状态！\n";
//			for (j = 0; j < r; j++)
//			{
//				b[n][j] = b[n][j] - req[j];
//				c[n][j] = c[n][j] + req[j];
//				d[j] = d[j] + req[j];
//			}
//		}
//	}
//
//	else cout << "申请资源量出错！\n";
//}
//
//
///*-----------------------------------------------*/
///*主函数*/
///*-----------------------------------------------*/
//void main()
//{
//	int j, n;                   //n-第n个资源申请
//	int max[p][r], allocation[p][r], need[p][r];
//	int available[r], request[r];
//	input(max, allocation, need, available);
//
//	if (stest(allocation, need, available) == 1)cout << "初始状态安全！\n";
//	else cout << "初始状态不安全！\n";
//
//	cout << " input request data:\n";
//	for (j = 0; j < r; j++)cin >> request[j];
//
//	cout << "第n个进程申请资源——n的值\n";
//	cin >> n;
//
//	rtest(allocation, need, available, request, n);
//}

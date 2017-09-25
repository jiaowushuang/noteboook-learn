#pragma once


typedef struct    //定义顺序表结构
{
	int  MaxNum;  //最多可经过的节点数
	int	 ListLen;    //顺序表已存结点的数量 
	int* ListData;  //保存顺序表的数组
}PathNodeType;

PathNodeType *PathNodeInit(int MaxNum);
int PathNodeLength(PathNodeType *SL);
int PathNodeAdd(PathNodeType *SL, int data);
int PathNodeInsert(PathNodeType *SL, int n, int data);
int PathNodeDelete(PathNodeType *SL, int n);
int *PathNodeFindByNum(PathNodeType *SL, int n);
int PathNodeFind(PathNodeType *SL, int no1, int no2);
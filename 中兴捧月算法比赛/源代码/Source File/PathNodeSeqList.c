#include "PathNodeSeqList.h"
#include <stdio.h>

PathNodeType *PathNodeInit(int MaxNum)
{//初始化顺序表
	PathNodeType *p;
	if (MaxNum <= 0)
	{
		printf("顺序表最大值设置不合理\n");
		getchar();
		exit(0);

	}
	if (!(p = (PathNodeType *)malloc(sizeof(PathNodeType)))) //申请内存 
	{
		printf("申请顺序表内存失败\n");
		getchar();
		exit(0);
	}
	if (!(p->ListData = (int*)malloc(MaxNum * sizeof(int))))
	{
		printf("申请顺序表节点数组内存失败\n");
		getchar();
		exit(0);

	}
	p->ListLen = 0;     //初始化时，设置顺序表长度为0
	p->MaxNum = MaxNum;
	return p;
}
int PathNodeLength(PathNodeType *SL)
{//返回顺序表的元素数量 
	return (SL->ListLen);
}
int PathNodeAdd(PathNodeType *SL, int data)
{//增加元素到顺序表尾部
	if (SL->ListLen >= SL->MaxNum)  //顺序表已满 
	{
		printf("顺序表已满，不能再添加结点了！\n");
		return 0;
	}
	SL->ListData[++SL->ListLen] = data;
	return 1;
}
int PathNodeInsert(PathNodeType *SL, int n, int data)
{
	int i;
	if (SL->ListLen >= SL->MaxNum)   //顺序表结点数量已超过最大数量 
	{
		printf("顺序表已满，不能插入结点!\n");
		return 0;             //返回0表示插入不成功 
	}
	if (n<1 || n>SL->ListLen)  //插入结点序号不正确
	{
		printf("插入元素序号错误，不能插入元素！\n");
		return 0;              //返回0，表示插入不成功 
	}
	for (i = SL->ListLen; i >= n; i--)  //将顺序表中的数据向后移动 
		SL->ListData[i + 1] = SL->ListData[i];
	SL->ListData[n] = data;        //插入结点 
	SL->ListLen++;               //顺序表结点数量增加1 
	return 1;                   //返回成功插入  
}
int PathNodeDelete(PathNodeType *SL, int n)
{//删除顺序表中的数据元素 
	int i;
	if (n<1 || n>SL->ListLen)  //删除元素序号不正确
	{
		printf("删除结点序号错误，不能删除结点！\n");
		return 0;              //返回0，表示删除不成功 
	}
	for (i = n; i<SL->ListLen; i++)  //将顺序表中的数据向前移动 
		SL->ListData[i] = SL->ListData[i + 1];
	SL->ListLen--;               //顺序表元素数量减1 
	return 1;                   //返回成功删除  
}

//note:返回该元素所在地址，可对线性表中此元素进行读-写操作
int *PathNodeFindByNum(PathNodeType *SL, int n)
{//根据序号返回数据元素
	if (n<1 || n>SL->ListLen + 1)  //元素序号不正确
	{
		printf("结点序号错误，不能返回结点！\n");
		return NULL;              //返回0，表示不成功 
	}
	return &(SL->ListData[n]);
}
int PathNodeFind(PathNodeType *SL, int no1, int no2)
{/* 寻找元素序号 */
	int i;
	for (i = 1; i <= SL->ListLen; i++)
		if (SL->ListData[i] == no1)  //如果找到所需结点 
		{
			if (SL->ListData[i+1] == no2)
				return i;        //返回结点序号 
		}
	return 0;  //遍历后仍没有找到，则返回0 
}
/* 
note:表中0位置为空，按自然顺序1,2,3...操作
note:线性表的基本操作过程
1-初始化
2-获取线性表长度/元素个数
3-增加节点
4-插入节点
5-删除节点
6-获取表中第i个元素—读/写
 -获取表中第i个元素—只读
7-关键字查询
8-获取i的前驱元素
9-获取i的后继元素
10-置空表
11-释放表
12-判断表是否为空
note:Zhangximing 2017.3.27
*/

#include <stdio.h>
#include "InsertList.h"

SeqListType *SeqListInit() 
{//初始化顺序表
	SeqListType *p;
	if (p = (SeqListType *)malloc(sizeof(SeqListType))) //申请内存 
	{
		p->ListLen = 0;     //初始化时，设置顺序表长度为0
		return p;
	}
	return NULL;
}
int SeqListLength(SeqListType *SL)
{//返回顺序表的元素数量 
	return (SL->ListLen);
}
int SeqListAdd(SeqListType *SL, ListDataType data)
{//增加元素到顺序表尾部
	if (SL->ListLen >= MAXSIZE)  //顺序表已满 
	{
		printf("顺序表已满，不能再添加结点了！\n");
		return 0;
	}
	SL->ListData[++SL->ListLen] = data;
	return 1;
}
int SeqListInsert(SeqListType *SL, int n, ListDataType data)
{
	int i;
	if (SL->ListLen >= MAXSIZE)   //顺序表结点数量已超过最大数量 
	{
		printf("顺序表已满，不能插入结点!\n");
		return 0;             //返回0表示插入不成功 
	}
	if (n<1 || n>SL->ListLen )  //插入结点序号不正确
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
int SeqListDelete(SeqListType *SL, int n)
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
ListDataType *SeqListFindByNum(SeqListType *SL, int n)
{//根据序号返回数据元素
	if (n<1 || n>SL->ListLen + 1)  //元素序号不正确
	{
		printf("结点序号错误，不能返回结点！\n");
		return NULL;              //返回0，表示不成功 
	}
	return &(SL->ListData[n]);
}
//int SeqListFindByCont(SeqListType *SL, char *key)  //按关键字查询结点 
//{
//	int i;
//	for (i = 1; i <= SL->ListLen; i++)
//		if (strcmp(SL->ListData[i].key, key) == 0)  //如果找到所需结点 
//			return i;        //返回结点序号 
//	return 0;  //遍历后仍没有找到，则返回0 
//}

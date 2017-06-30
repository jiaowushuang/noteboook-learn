#include <stdio.h>
#include "Storage.h"

EdgeLinkType *EdgeListInit()
{//初始化顺序表——必经边链
	EdgeLinkType *p;
	if (p = (EdgeLinkType *)malloc(sizeof(EdgeLinkType)))
	{
		p->ListLen = 0; //设置顺序表长度为0
		return p;
	}
	return NULL;
}
int EdgeListLength(EdgeLinkType *SL)
{//返回顺序表的元素数量 
	return (SL->ListLen);
}
int EdgeListAdd(EdgeLinkType *SL, EdgeLinkDataType data)
{//增加元素到顺序表尾部
	if (SL->ListLen >= MAXSIZE)  //顺序表已满 
	{
		printf("必经边链——顺序表已满，不能再添加结点了！\n");
		return 0;
	}
	SL->ListData[++SL->ListLen] = data;
	return 1;
}
int EdgeListInsert(EdgeLinkType *SL, int n, EdgeLinkDataType data)
{
	int i;
	if (SL->ListLen >= MAXSIZE)   //顺序表结点数量已超过最大数量 
	{
		printf("必经边链——顺序表已满，不能插入结点!\n");
		return 0;             //返回0表示插入不成功 
	}
	if (n<1 || n>SL->ListLen)  //插入结点序号不正确
	{
		printf("必经边链——插入元素序号错误，不能插入元素！\n");
		return 0;              //返回0，表示插入不成功 
	}
	for (i = SL->ListLen; i >= n; i--)  //将顺序表中的数据向后移动 
		SL->ListData[i + 1] = SL->ListData[i];
	SL->ListData[n] = data;        //插入结点 
	SL->ListLen++;               //顺序表结点数量增加1 
	return 1;                   //返回成功插入  
}
int EdgeListDelete(EdgeLinkType *SL, int n)
{//删除顺序表中的数据元素 
	int i;
	if (n<1 || n>SL->ListLen)  //删除元素序号不正确
	{
		printf("必经边链——删除结点序号错误，不能删除结点！\n");
		return 0;              //返回0，表示删除不成功 
	}
	for (i = n; i<SL->ListLen; i++)  //将顺序表中的数据向前移动 
		SL->ListData[i] = SL->ListData[i + 1];
	SL->ListLen--;               //顺序表元素数量减1 
	return 1;                   //返回成功删除  
}
void getEdgeSum()
{
	for (int i = 1; i <= mustEdgeLink.ListLen; i++)
	{
		mustEdgeLink.ListData[i].costSum =
			mustEdgeLink.ListData[i].InsertAddCost + mustEdgeLink.ListData[i].DeleteSubCost;
	}
}
void EdgeLinkSortByCost()
{
	int flag = 1;
	while (flag)
	{
		flag = 0;
		for (int i = 1; i <= mustEdgeLink.ListLen - 1; i++)
		{
			if (mustEdgeLink.ListData[i].costSum < mustEdgeLink.ListData[i + 1].costSum)
			{
				flag++;
				EdgeLinkDataType temp = mustEdgeLink.ListData[i];
				mustEdgeLink.ListData[i] = mustEdgeLink.ListData[i + 1];
				mustEdgeLink.ListData[i + 1] = temp;
			}
		}
	}
}
NodeLinkType *NodeListInit()
{//初始化顺序表——必经点链
	NodeLinkType *p;
	if (p = (NodeLinkType *)malloc(sizeof(NodeLinkType)))
	{
		p->ListLen = 0;     //设置顺序表长度为0
		return p;
	}
	return NULL;
}
int NodeListLength(NodeLinkType *SL)
{//返回顺序表的元素数量 
	return (SL->ListLen);
}
int NodeListAdd(NodeLinkType *SL, NodeLinkDataType data)
{//增加元素到顺序表尾部
	if (SL->ListLen >= MAXSIZE)
	{
		printf("必经点链——顺序表已满，不能再添加结点了！\n");
		return 0;
	}
	SL->ListData[++SL->ListLen] = data;
	return 1;
}
int NodeListInsert(NodeLinkType *SL, int n, NodeLinkDataType data)
{
	int i;
	if (SL->ListLen >= MAXSIZE)   //顺序表结点数量已超过最大数量 
	{
		printf("必经点链——顺序表已满，不能插入结点!\n");
		return 0;             //返回0表示插入不成功 
	}
	if (n<1 || n>SL->ListLen )  //插入结点序号不正确
	{
		printf("必经点链——插入元素序号错误，不能插入元素！\n");
		return 0;              //返回0，表示插入不成功 
	}
	for (i = SL->ListLen; i >= n; i--)  //将顺序表中的数据向后移动 
		SL->ListData[i + 1] = SL->ListData[i];
	SL->ListData[n] = data;        //插入结点 
	SL->ListLen++;               //顺序表结点数量增加1 
	return 1;                   //返回成功插入  
}
int NodeListDelete(NodeLinkType *SL, int n)
{//删除顺序表中的数据元素 
	int i;
	if (n<1 || n>SL->ListLen)  //删除元素序号不正确
	{
		printf("必经点链——删除结点序号错误，不能删除结点！\n");
		return 0;              //返回0，表示删除不成功 
	}
	for (i = n; i<SL->ListLen; i++)  //将顺序表中的数据向前移动 
		SL->ListData[i] = SL->ListData[i + 1];
	SL->ListLen--;               //顺序表元素数量减1 
	return 1;                   //返回成功删除  
}
int getNodeListElePos(NodeLinkType *SL, NodeLinkDataType data)
{//获得元素在线性表中的位置
	int i;
	for (i = 1; i <= SL->ListLen; i++)
	{
		if (data.no == SL->ListData[i].no)
			return i;
	}
	return 0;//未找到，错误
}
void getNodeSum()
{
	for (int i = 1; i <= mustNodeLink.ListLen; i++)
	{
		mustNodeLink.ListData[i].costSum =
			mustNodeLink.ListData[i].DeleteSubCost + mustNodeLink.ListData[i].InsertAddCost;
	}
}
void NodeListSortByCost()
{
	int flag = 1;
	while (flag)
	{
		flag = 0;
		for (int i = 1; i <= mustNodeLink.ListLen - 1; i++)
		{
			if (mustNodeLink.ListData[i].costSum < mustNodeLink.ListData[i + 1].costSum)
			{
				flag++;
				NodeLinkDataType temp = mustNodeLink.ListData[i];
				mustNodeLink.ListData[i] = mustNodeLink.ListData[i + 1];
				mustNodeLink.ListData[i + 1] = temp;
			}
		}

		//for (int i = mustNodeLink.ListLen; i > 1; i--)
		//{
		//	if (mustNodeLink.ListData[i].costSum > mustNodeLink.ListData[i - 1].costSum)
		//	{
		//		flag++;
		//		NodeLinkDataType temp = mustNodeLink.ListData[i];
		//		mustNodeLink.ListData[i] = mustNodeLink.ListData[i - 1];
		//		mustNodeLink.ListData[i - 1] = temp;
		//	}
		//}
	}
}
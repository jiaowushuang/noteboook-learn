#include <stdio.h>
#include <MustNode2Path.h>
#include <Storage.h>
#include <InsertList.h>
#include "Joint.h"
#include "2opt.h"
#include "DeleteMust.h"
void ClearUsedFlag(int val)
{
	mustNodeLink.usedNum = mustNodeLink.ListLen;
	for (int i = 0; i <= mustNodeLink.ListLen; i++)
	{
		mustNodeLink.ListData[i].IsUsed = val;
	}
	mustEdgeLink.usedNum = mustEdgeLink.ListLen;
	for (int i = 0; i <= mustEdgeLink.ListLen; i++)
	{
		mustEdgeLink.ListData[i].IsUsed = val;
	}
}
void ClearInsertCost()
{
	for (int i = 0; i <= mustNodeLink.ListLen; i++)
	{
		mustNodeLink.ListData[i].InsertAddCost = -1;
	}
	mustEdgeLink.usedNum = mustEdgeLink.ListLen;
	for (int i = 0; i <= mustEdgeLink.ListLen; i++)
	{
		mustEdgeLink.ListData[i].InsertAddCost = -1;
	}
}
void InitInsertLink()
{//初始化可插入链
	ListDataType ele;//可插入链节点元素
	InsertLink = SeqListInit();//开辟可插入链存储空间
	ele.startNo = AdjGraf.StartNode;/* 加入头节点和尾节点 */
	ele.endNo = AdjGraf.EndNode;
	ele.flag = 1;
	SeqListAdd(InsertLink, ele);
}
int AddEdge(int edge_index)
{//加入一条边 no1 --> no2
	int no1 = mustEdgeLink.ListData[edge_index].no1;
	int no2 = mustEdgeLink.ListData[edge_index].no2;
	int start, end;
	int num1 = 0, num2 = 0, num3 = 0, val = MAX_VALUE;
	int pos = 1, dir = 1;
	int i, j;
	ListDataType ele;
	for (i = 1; i <= InsertLink->ListLen; i++)
	{//寻找最优插入节点
		if (InsertLink->ListData[i].flag == 1)
		{//如果可插入
			start = InsertLink->ListData[i].startNo;
			end = InsertLink->ListData[i].endNo;
			/*原路径跳数、正向插入跳数、反向插入跳数*/
			/* start --> end */
			num1 = pPathMatrix[getPos(start)*gatherNode.num + getPos(end)].LayerNum;
			/* start --> no1 --> no2 --> end */
			num2 = pPathMatrix[getPos(start)*gatherNode.num + getPos(no1)].LayerNum +
				pPathMatrix[getPos(no2)*gatherNode.num + getPos(end)].LayerNum;
			/* start --> no2 --> no1 --> end */
			num3 = pPathMatrix[getPos(start)*gatherNode.num + getPos(no2)].LayerNum + pPathMatrix[getPos(no1)*gatherNode.num + getPos(end)].LayerNum;
			if (num2 < num3)
			{//正向插入/* start --> no1 --> no2 --> end */
				if ((num2 - num1) < val)
				{//寻找最优插入节点
					val = num2 - num1;
					pos = i; dir = 1;
				}
			}
			else
			{//反向插入/* start --> no2 --> no1 --> end */
				if ((num3 - num1) < val)
				{//寻找最优插入节点
					val = num3 - num1;
					pos = i; dir = 2;
				}
			}
		}/*end if*/
		if (val < 0)
		{
			val = 0;
		}
	}
	mustEdgeLink.ListData[edge_index].InsertAddCost = val;
	if (dir == 1)
	{//正向插入/* start --> no1 --> no2 --> end */
		start = InsertLink->ListData[pos].startNo;
		end = InsertLink->ListData[pos].endNo;
		ele.startNo = start;
		ele.endNo = no1;
		ele.flag = 1;
		SeqListInsert(InsertLink, pos, ele);
		ele.startNo = no1;
		ele.endNo = no2;
		ele.flag = 0;//必经边，不可进行插入
		SeqListInsert(InsertLink, pos + 1, ele);
		ele.startNo = no2;
		ele.endNo = end;
		ele.flag = 1;
		SeqListInsert(InsertLink, pos + 2, ele);
		
	}
	else
	{//反向插入/* start --> no2 --> no1 --> end */
		start = InsertLink->ListData[pos].startNo;
		end = InsertLink->ListData[pos].endNo;
		ele.startNo = start;
		ele.endNo = no2;
		ele.flag = 1;
		SeqListInsert(InsertLink, pos, ele);
		ele.startNo = no2;
		ele.endNo = no1;
		ele.flag = 0;//必经边，不可进行插入
		SeqListInsert(InsertLink, pos + 1, ele);
		ele.startNo = no1;
		ele.endNo = end;
		ele.flag = 1;
		SeqListInsert(InsertLink, pos + 2, ele);
	}
	SeqListDelete(InsertLink, pos + 3);
	return dir;
}
void AddNode(int no_index)
{//加入节点
	int no = mustNodeLink.ListData[no_index].no;
	int start, end;
	int num1 = 0, num2 = 0, num3 = 0, val = MAX_VALUE;
	int pos = 1, dir = 1;
	int i, j;
	ListDataType ele;
	for (i = 1; i <= InsertLink->ListLen; i++)
	{//寻找最优插入点
		if (InsertLink->ListData[i].flag == 1)
		{
			start = InsertLink->ListData[i].startNo;
			end = InsertLink->ListData[i].endNo;
			/* 原路径跳数、插入后路径跳数 */
			/* start --> end */
			num1 = pPathMatrix[getPos(start)*gatherNode.num + getPos(end)].LayerNum;
			/* start --> no--> end */
			num2 = pPathMatrix[getPos(start)*gatherNode.num + getPos(no)].LayerNum +
				pPathMatrix[getPos(no)*gatherNode.num + getPos(end)].LayerNum;

			if ((num2 - num1) < val)
			{
				val = num2 - num1;
				pos = i;
			}
		}
	}
	mustNodeLink.ListData[no_index].InsertAddCost = val - 1;
	/* start --> no--> end */
	ele.startNo = InsertLink->ListData[pos].startNo;
	ele.endNo = no;
	ele.flag = 1;
	SeqListInsert(InsertLink, pos, ele);
	ele.startNo = no;
	ele.endNo = InsertLink->ListData[pos + 1].endNo;
	ele.flag = 1;
	SeqListInsert(InsertLink, pos + 1, ele);

	SeqListDelete(InsertLink, pos + 2);  /* start --> end */
}
int getDis(int no, EdgeLinkDataType edge)
{//获得点到边的最小跳数
	int value1, value2;
	value1 = pPathMatrix[getPos(no)*gatherNode.num + getPos(edge.no1)].LayerNum;
	value2 = pPathMatrix[getPos(no)*gatherNode.num + getPos(edge.no2)].LayerNum;
	return value1 < value2 ? value1 : value2;
}
void InsertMustPass()
{//插入一条边或者一个节点——邻近+节省插入法
	int temp;
	int head, tail, no;
	
	int FlagInsertDir = 0; /* no = 头 / 尾节点链尾元素*/
	head = AdjGraf.StartNode;
	tail = AdjGraf.EndNode;

	ClearUsedFlag(0); /* 清除使用标记 */
	ClearInsertCost(); /* 清除插入成本*/
	//while ((mustEdgeLink.ListLen > 0) || (mustNodeLink.ListLen > 0))
	while ((mustEdgeLink.usedNum > 0) || (mustNodeLink.usedNum > 0))
	{
		int minVal = MAX_VALUE;//保存最小跳数
		int addFlag, addIndex;

		if (FlagInsertDir == 0)	no = head;
		else	                no = tail;

		for (int i = 1; i <= mustNodeLink.ListLen; i++)
		{//获取节点 no 到 必经节点的的最小跳数和该必经节点编号
			if (mustNodeLink.ListData[i].IsUsed == 0)
			{
				temp = pPathMatrix[getPos(no)*gatherNode.num
					+ getPos(mustNodeLink.ListData[i].no)].LayerNum;
				if (temp < minVal)
				{
					minVal = temp;
					addFlag = 0; addIndex = i;//加入必经节点i
				}
			}
		}
		for (int i = 1; i <= mustEdgeLink.ListLen; i++)
		{//获取节点 no 到 必经边的的最小跳数和该必经边编号
			if (mustEdgeLink.ListData[i].IsUsed == 0)
			{
				temp = temp = getDis(no, mustEdgeLink.ListData[i]);
				if (temp < minVal)
				{
					minVal = temp;
					addFlag = 1; addIndex = i;//加入必经节点i
				}
			}
		}
		if (addFlag == 0)
		{//加入节点
			AddNode(addIndex);
			no = mustNodeLink.ListData[addIndex].no;
			//NodeListDelete(&mustNodeLink, addIndex);/* 删除该节点 */
			mustNodeLink.ListData[addIndex].IsUsed = 1; mustNodeLink.usedNum--;
		}
		else if (addFlag == 1)
		{//加入边
			int dir;//边的插入方向
			dir = AddEdge(addIndex);
			if (FlagInsertDir == 0)
			{/* 当前选择为头链 */
				if (dir == 1)
				{//正向插入
					no = mustEdgeLink.ListData[addIndex].no2;
				}
				else
				{//反向插入
					no = mustEdgeLink.ListData[addIndex].no1;
				}
			}
			else
			{/* 当前选择为尾链 */
				if (dir == 1)
				{//正向插入
					no = mustEdgeLink.ListData[addIndex].no1;
				}
				else
				{//反向插入
					no = mustEdgeLink.ListData[addIndex].no2;
				}
			}
			//EdgeListDelete(&mustEdgeLink, addIndex);/* 删除该边 */
			mustEdgeLink.ListData[addIndex].IsUsed = 1; mustEdgeLink.usedNum--;
		}
		if (FlagInsertDir == 0)/* 当前选择为头链 */
		{//更新头结点链尾元素
			head = no;
			FlagInsertDir = 1; /* 更改插入方向 */
		}
		else/* 当前选择为尾链 */
		{//更新尾节点链尾元素
			tail = no;
			FlagInsertDir = 0; /* 更改插入方向 */
		}
	}/* end while()*/
}
void PrintfInsertLink()
{//打印可插入链
	printf("可插入链：");
	for (int i = 1; i <= InsertLink->ListLen; i++)
	{
		printf(" %d-%d[%d]", InsertLink->ListData[i].startNo, 
			InsertLink->ListData[i].endNo, InsertLink->ListData[i].flag);
	}
	printf("\n");
}
void getAllMustNodeLink()
{//可插入链—>所有必经节点的顺序集合
	AllMustNodeOrderGather.num = InsertLink->ListLen;
	AllMustNodeOrderGather.p = (int *)malloc(AllMustNodeOrderGather.num * sizeof(int));
	int j = 0;
	for (int i = 1; i <= InsertLink->ListLen; i++)
	{
		if (InsertLink->ListData[i].startNo != InsertLink->ListData[i].endNo)
		{
			AllMustNodeOrderGather.p[j++] = InsertLink->ListData[i].startNo;
		}
	}
	AllMustNodeOrderGather.p[j++] = AdjGraf.EndNode;
	AllMustNodeOrderGather.num = j;
}
void PrintfOrderGather()
{//打印所有必经节点顺序集合
	printf("【所有必经节点顺序集合 = %d】", AllMustNodeOrderGather.num);
	for (int i = 0; i < AllMustNodeOrderGather.num; i++)
	{
		printf(" %d ", AllMustNodeOrderGather.p[i]);
	}
	printf("\n");
}
void PrintOnePath(int startNo, int endNo, gatherNodeType AllMustNodeOrderGather)
{
	int pathNum, layout; /* 路径数  跳数 */ 
	/* 矩阵 = 路径数 *（跳数 + 1) 首元素为 花费  */
	int selectedPath;
	int cost = MAX_VALUE;
	int* link;
	int loc_startNo = getPos(startNo); /* 获取节点在所有必经节点集合的下标位置 */
	int loc_endNo = getPos(endNo);

	if (loc_startNo < loc_endNo)
	{//正向打印
		pathNum = pPathMatrix[loc_startNo*gatherNode.num + loc_endNo].PathNum;
		layout = pPathMatrix[loc_startNo*gatherNode.num + loc_endNo].LayerNum;
		link = pPathMatrix[loc_startNo*gatherNode.num + loc_endNo].link;
		for (int i = 0; i < pathNum; i++)
		{//选择花费最小的路径
			if (link[i*(layout + 1) + 0 ] < cost)
			{
				selectedPath = i;
				cost = link[i*(layout + 1) + 0];
			}
		}
		for (int i = 1; i < layout; i++)
		{// s -> 1 -> 2 -> t 不打印 endNo
			printf("%d-->", link[selectedPath*(layout + 1) + i]);
		}
	}
	else
	{//反向打印
		pathNum = pPathMatrix[loc_endNo*gatherNode.num + loc_startNo].PathNum;
		layout = pPathMatrix[loc_endNo*gatherNode.num + loc_startNo].LayerNum;
		link = pPathMatrix[loc_endNo*gatherNode.num + loc_startNo].link;
		for (int i = 0; i < pathNum; i++)
		{//选择花费最小的路径
			if (link[i*(layout + 1) + 0] < cost)
			{
				selectedPath = i;
				cost = link[i*(layout + 1) + 0];
			}
		}
		for (int i = layout; i > 1; i--)
		{// cost  t -> 2 -> 1 -> s
			printf("%d-->", link[selectedPath*(layout + 1) + i]);
		}
	}
}
void PrintPathes(gatherNodeType AllMustNodeOrderGather)
{
	int no, end_no;
	printf("路径：");
	for (int i = 1; i < AllMustNodeOrderGather.num; i++)
	{
		no = AllMustNodeOrderGather.p[i - 1];
		end_no = AllMustNodeOrderGather.p[i];

		PrintOnePath(no, end_no, AllMustNodeOrderGather);
	}
	printf("%d\n", end_no);//打印终止节点
}
void Joint()
{
	InitInsertLink(); /* 初始化可插入链 */

	InsertMustPass(); /* 最近 + 节省 插入 */

	//PrintfInsertLink();/* 打印可插入链 */
	getAllMustNodeLink();/* 获得并打印所有必经节点顺序链 */
	//PrintfOrderGather();
	deleteGather_1();
	//printf("\n邻近+节省 仅插入 操作——路径跳数 = %d\n", optEffect(AllMustNodeOrderGather));
	//PrintPathes(AllMustNodeOrderGather);

	opt();
	deleteGather_1();
}
void PrintfMustNode_Edge()
{
	printf("【必经点点点点点！！！】 ");
	for (int i = 1; i <= mustNodeLink.ListLen; i++)
	{
		printf("[%3d %d %d]", mustNodeLink.ListData[i].no, mustNodeLink.ListData[i].InsertAddCost, mustNodeLink.ListData[i].DeleteSubCost);
	}
	printf("\n");
	printf("【必经边边边边！！！！】 ");
	for (int i = 1; i <= mustEdgeLink.ListLen; i++)
	{
		printf("[%3d-%3d  %d %d]", mustEdgeLink.ListData[i].no1, mustEdgeLink.ListData[i].no2, mustEdgeLink.ListData[i].InsertAddCost, mustEdgeLink.ListData[i].DeleteSubCost);
	}
	printf("\n");

	getEdgeSum();
	getNodeSum();
	EdgeLinkSortByCost();
	NodeListSortByCost();

	printf("【必经点点点点点！！！】 ");
	for (int i = 1; i <= mustNodeLink.ListLen; i++)
	{
		printf("[%3d  %d %d %d]", mustNodeLink.ListData[i].no, 
			mustNodeLink.ListData[i].InsertAddCost, mustNodeLink.ListData[i].DeleteSubCost,
			mustNodeLink.ListData[i].costSum);
	}
	printf("\n");
	printf("【必经边边边边！！！！】 ");
	for (int i = 1; i <= mustEdgeLink.ListLen; i++)
	{
		printf("[%3d-%3d  %d %d %d]", mustEdgeLink.ListData[i].no1, mustEdgeLink.ListData[i].no2, mustEdgeLink.ListData[i].InsertAddCost, mustEdgeLink.ListData[i].DeleteSubCost,
			mustEdgeLink.ListData[i].costSum);
	}
	printf("\n");
}
void deleteGather_1()
{
	int i;
	for (i = 0; i < (AllMustNodeOrderGather.num - 1); i++)
	{
		if (AllMustNodeOrderGather.p[i] == AllMustNodeOrderGather.p[i + 1])
		{
			AllMustNodeOrderGather.num--;
			for (int j = i + 1; j < AllMustNodeOrderGather.num; j++)
			{
				AllMustNodeOrderGather.p[j] = AllMustNodeOrderGather.p[j + 1];
			}
		}
	}
}
void deleteGather_2()
{
	int i;
	for (i = 0; i < (AllMustNodeOrderGather_2.num - 1); i++)
	{
		if (AllMustNodeOrderGather_2.p[i] == AllMustNodeOrderGather_2.p[i + 1])
		{
			AllMustNodeOrderGather_2.num--;
			for (int j = i + 1; j < AllMustNodeOrderGather_2.num; j++)
			{
				AllMustNodeOrderGather_2.p[j] = AllMustNodeOrderGather_2.p[j + 1];
			}
		}
	}
}
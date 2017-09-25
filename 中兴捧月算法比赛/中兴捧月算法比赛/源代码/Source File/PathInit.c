#include <stdio.h>
#include "PathInit.h"
#include "Storage.h"
#include "MustNode2Path.h"
#include <malloc.h>
#include "cost.h"

#define MaxPassVertex  150  /*最多可经过的节点数*/

PathNodeType* list;
MaxHeapType* heap;

int getWeight(int no, int end)
{
	//不是必须边返回权重
	//必须边返回-1
	//边不存在返回0
	EdgeNodeType* p = AdjGraf.VNode[no].firstEdge;
	while (p != NULL)
	{
		if (p->End_No == end)
		{
			if (p->E_data.eType == 1)
				return - 1;
			else
				return p->E_data.weight;
		}
		p = p->nextEdge;
	}
	return 0;
}
void AddOnePath(int startNo, int endNo,PathNodeType* list,MaxHeapType* heap)
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
			if (link[i*(layout + 1) + 0] < cost)
			{
				selectedPath = i;
				cost = link[i*(layout + 1) + 0];
			}
		}
		for (int i = 1; i < layout; i++)
		{// s -> 1 -> 2 -> t 不打印 endNo
			PathNodeAdd(list,link[selectedPath*(layout + 1) + i]);
			MaxHeapEdgeType* edge = (MaxHeapType*)malloc(sizeof(MaxHeapEdgeType));
			edge->No = link[selectedPath*(layout + 1) + i];
			edge->End_NO = link[selectedPath*(layout + 1) + i + 1];
			edge->Weight = getWeight(edge->No, edge->End_NO);
			edge->LayerNum = 2;
			edge->Price = 0;
			if (edge->Weight>0)
			{
				MaxHeapAdd(heap, edge);
			}
			
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
			PathNodeAdd(list, link[selectedPath*(layout + 1) + i]);
			MaxHeapEdgeType* edge = (MaxHeapType*)malloc(sizeof(MaxHeapEdgeType));
			edge->No = link[selectedPath*(layout + 1) + i];
			edge->End_NO = link[selectedPath*(layout + 1) + i -1];
			edge->Weight = getWeight(edge->No, edge->End_NO);
			edge->LayerNum = 2;
			edge->Price = 0;
			if (edge->Weight>0)
			{
				MaxHeapAdd(heap, edge);
			}

		}
	}
}
void ListAndHeapInit(PathNodeType* list, MaxHeapType* heap)
{
	int n = AllMustNodeOrderGather.num-1;
	for (int i = 0; i < n; i++)
	{
		int node1 = AllMustNodeOrderGather.p[i];
		int node2 = AllMustNodeOrderGather.p[i+1];

		AddOnePath(node1,node2,list,heap);
	}
	PathNodeAdd(list, AllMustNodeOrderGather.p[n]);

	//PrintfPathNodeList();
}
void PrintfPathNodeList()
{//路径线性表 顺序存放路径通过的所有节点
	int cost = 0;
	//printf("【线性表存储路径 %d 】： ", list->ListLen);
	for (int i = 1; i < list->ListLen; i++)
	{
		//printf("%d -> ", list->ListData[i]);
		cost += getCost(list->ListData[i], list->ListData[i+1]);
	}
	//printf("%d ", list->ListData[list->ListLen]);
	//printf("\n");
	printf("\n【最优路径：经过节点数 = %d, 花费 = %d】\n", list->ListLen, cost);
	printf("路径：");
	for (int i = 1; i < list->ListLen; i++)
	{
		printf("%d -> ", list->ListData[i]);
	}
	printf("%d ", list->ListData[list->ListLen]);
	printf("\n");
}
void Test(int hop)
{
	int k = 2 * (AdjGraf.MaxHop - hop);
	list = PathNodeInit(AdjGraf.MaxHop);
	heap = MaxHeapInit(hop);

	ListAndHeapInit(list, heap);/* 初始化线性表存储路径 / 最大堆 （权重较大的边）*/
	for (int i = 0; i < heap->size; i++)
	{/* 松弛权值较大的边，记录新路径及替换性价比*/
		getCost_Layer(heap->edge[i].No, heap->edge[i].End_NO, heap->edge[i].Weight,
			&heap->edge[i]);
	}
	MaxHeapSortByPrice(heap);/* 最大堆按 性价比 排序*/
	//OutPrintMaxHeap(heap);/* 打印最大堆，按性价比排序后*/

	CostOpt();/* 费用优化 */
	PrintfPathNodeList();/**/
}

void CostOpt()
{
	int i;
	int pos = 0;
	for (i = 0; i < heap->size; i++)
	{//遍历最大堆元素
		if (list->ListLen < AdjGraf.MaxHop)
		{
			if (heap->edge[i].WeightChange < heap->edge[i].Weight)
			{
				pos = PathNodeFind(list, heap->edge[i].No, heap->edge[i].End_NO);
				if (heap->edge[i].LayerNUmChange == 3)
				{
					PathNodeInsert(list, pos + 1, heap->edge[i].path[0]);
				}
				else if (heap->edge[i].LayerNUmChange == 4)
				{
					if (AdjGraf.MaxHop > (list->ListLen + 1))
					{
						PathNodeInsert(list, pos + 1, heap->edge[i].path[0]);
						PathNodeInsert(list, pos + 2, heap->edge[i].path[1]);
					}
				}
				else if (heap->edge[i].LayerNUmChange == 5)
				{
					if (AdjGraf.MaxHop > (list->ListLen + 2))
					{
						PathNodeInsert(list, pos + 1, heap->edge[i].path[0]);
						PathNodeInsert(list, pos + 2, heap->edge[i].path[1]);
						PathNodeInsert(list, pos + 3, heap->edge[i].path[2]);
					}
				}
			}
		}/* end (list->ListLen < MaxPassVertex) */
	}/* end  i < heap->size */
}
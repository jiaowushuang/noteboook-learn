#include <stdio.h>
#include "ShortestPath.h"
#include "MinHeap.h"
#include <Storage.h>
#include "cost.h"
#include "MustNode2Path.h"

DijkstraMatrix *DijMatrix;

void InitDijMatrix()
{//初始化迪杰斯特拉必经节点最小花费矩阵
	DijMatrix = (DijkstraMatrix *)malloc(gatherNode.num * gatherNode.num * sizeof(DijkstraMatrix));
	for (int i = 0; i < gatherNode.num; i++)
	{// <i,i>
		DijMatrix[i*gatherNode.num + i].LayerNum = 0;
		DijMatrix[i*gatherNode.num + i].cost = 0;
		DijMatrix[i*gatherNode.num + i].link = NULL;
	}
	for (int i = 0; i < gatherNode.num; i++)
	{
		DijkstraAdj(&AdjGraf, gatherNode.p[i]);
	}
	//PrintfDijMatrix();
	//PrintfDiffer();
}
void DijkstraHeap(AdjListGraph *G, int v0)
{//最小堆优化版本——迪杰斯特拉算法
	MinHeap *pQueue;          //最小堆指针
	ElementType ele,minNode;  //最小堆数据元素
	int path[VERTEX_MAX];     //某源点到终点经过的顶点
	int tmpvertex[VERTEX_MAX];//最短路径的终点集合
	EdgeNodeType  *pEdge;     //指向边信息的指针
	int i, k;

	pQueue = MinHeapInit(G->VertexNum);
	for (i = 0; i < G->VertexNum; i++)
	{//初始化数据
		pQueue->pos[i] = G->VertexNum + 1; //设置节点 i 在最小堆的位置（下标）
		path[i] = v0;
		tmpvertex[i] = 0; 
	}
	tmpvertex[v0] = 1; //将顶点v0添加到集合U中 
	pEdge = G->VNode[v0].firstEdge;
	while (pEdge != NULL)
	{//初始化V0的相邻接节点，插入找到最小堆中
		ele.weight = pEdge->E_data.weight;
		ele.nodeID = pEdge->End_No;
		MinHeapInsertEle(&ele, pQueue);
		pEdge = pEdge->nextEdge;
	}
	for (i = 0; i < G->VertexNum; i++)
	{
		Delete(pQueue, &minNode);
		tmpvertex[minNode.nodeID] = 1;  //将顶点k加入集合U
		pEdge = G->VNode[minNode.nodeID].firstEdge;
		while (pEdge != NULL)
		{//用 minNode.nodeID 节点松弛其他节点
			if (tmpvertex[pEdge->End_No] == 0)
			{
				if (minNode.weight + pEdge->E_data.weight <
					pQueue->elements[pQueue->pos[pEdge->End_No]].weight)
				{//松弛操作
					/* 判断节点是否一囧存在于最小堆中 */
					if (pQueue->pos[pEdge->End_No] > G->VertexNum)
					{//将该节点插入最小堆中
						ele.weight = pEdge->E_data.weight;
						ele.nodeID = pEdge->End_No;
						MinHeapInsertEle(&ele, pQueue);
					}
					else
					{//调整该节点在最小堆的位置
						Adjust(pEdge->End_No, pQueue,
							(minNode.weight + pEdge->E_data.weight));
					}
					path[pEdge->End_No] = minNode.nodeID;
				}
			}
			pEdge = pEdge->nextEdge;
		}
	}
	
	/* 打印 汇点 <-- 源点 最小花费路径 */
	//PrintfMinCostPath(&tmpvertex, &path, G, v0);
	DijSave(&tmpvertex, &path, G, v0);
}
void PrintfMinCostPath(int *tmpvertex, int *path, AdjListGraph *G, int v0)
{
	int i, k;
	printf("\n邻接表图——顶点%d到各顶点的最短路径是(终点<源点):\n", G->VNode[v0].V_data.No);
	for (i = 0; i<G->VertexNum; i++)//输出结果
	{
		if (tmpvertex[i] == 1)
		{
			k = i;
			while (k != v0)
			{
				printf("%d<--", G->VNode[k].V_data.No);
				k = path[k];
			}
			printf("%d\n", G->VNode[k].V_data.No);
		}
		else
			printf("%c<-%c:无路径\n", G->VNode[i].V_data.No, G->VNode[v0].V_data.No);
	}
}
void DijSave(int *tmpvertex, int *path, AdjListGraph *G, int v0)
{/* 花费最小 s -> t */
	int i, k;
	EdgeNodeType *p;
	for (i = 0; i<gatherNode.num; i++)//输出结果
	{
		int layer = 0;
		int link[VERTEX_MAX];
		int cost = 0;
		if (gatherNode.p[i] != v0)
		{
			if (tmpvertex[gatherNode.p[i]] == 1)
			{
				k = gatherNode.p[i]; /* 终止节点 t */
				while (k != v0)
				{
					link[layer++] = G->VNode[k].V_data.No;  
					//printf("%d<--", G->VNode[k].V_data.No);
					k = path[k];
				}
				link[layer++] = G->VNode[k].V_data.No; 
				//printf("%d\n", G->VNode[k].V_data.No); /* 起始节点 */
				
				/* vo -> gatherNode.p[i] */
				DijMatrix[getPos(v0)*gatherNode.num + getPos(gatherNode.p[i])].
					LayerNum = layer;
				DijMatrix[getPos(v0)*gatherNode.num + getPos(gatherNode.p[i])].
					link = (int *)malloc(layer * sizeof(int));
				DijMatrix[getPos(v0)*gatherNode.num + getPos(gatherNode.p[i])].
					link[0] = link[layer - 1 - 0];
				//printf("%d", link[layer - 1 - 0]);
				for (int j = 1; j < layer; j++)
				{
					DijMatrix[getPos(v0)*gatherNode.num + getPos(gatherNode.p[i])].
						link[j] = link[layer - 1 - j];
					//printf("-->%d", link[layer - 1 - j]);
					for (p = G->VNode[link[layer - j]].firstEdge;
						p->End_No != link[layer - 1 - j]; p = p->nextEdge);
					cost += p->E_data.weight;
				}
				DijMatrix[getPos(v0)*gatherNode.num + getPos(gatherNode.p[i])].
					cost = cost;
				//printf(" \tlayer = %d, cost = %d\n", layer, cost);
			}
		}
	}
}
void DijkstraAdj(AdjListGraph *G, int v0)
{/* 迪杰斯特拉算法——邻接表矩阵单源点( no )最短路径 */
	int weight[VERTEX_MAX];//某源点到各顶点的最短路径长度
	int path[VERTEX_MAX];  //某源点到终点经过的顶点
	int tmpvertex[VERTEX_MAX];//最短路径的终点集合
	int i, j, k, min;
	EdgeNodeType  *pEdge;

	for (i = 0; i<G->VertexNum; i++)
	{/* 初始辅助数组 */
		weight[i] = MAX_VALUE;
		path[i] = -1;
		tmpvertex[i] = 0; //初始化终点集合为空 
	}

	tmpvertex[v0] = 1; //将顶点v0添加到集合U中 
	weight[v0] = 0; //将源顶点的权值设为0 
	pEdge = G->VNode[v0].firstEdge;
	while (pEdge != NULL)
	{
		weight[pEdge->End_No] = pEdge->E_data.weight;
		path[pEdge->End_No] = v0;
		pEdge = pEdge->nextEdge;
	}
	for (i = 0; i<G->VertexNum; i++)
	{
		min = MAX_VALUE;
		k = v0; //源顶点序号 
		for (j = 0; j < G->VertexNum; j++)
		{//在U集合中查找未用顶点的最小权值 
			if (tmpvertex[j] == 0 && weight[j] < min)
			{
				min = weight[j];
				k = j;
			}
		}
		tmpvertex[k] = 1;//将顶点k加入集合U
		pEdge = G->VNode[k].firstEdge;
		while (pEdge != NULL)
		{
			if (tmpvertex[pEdge->End_No] == 0)
			{
				if (weight[k] + pEdge->E_data.weight < weight[pEdge->End_No])
				{//有更小权值的路径
					weight[pEdge->End_No] = weight[k] + pEdge->E_data.weight;
					path[pEdge->End_No] = k;
				}
			}
			pEdge = pEdge->nextEdge;
		}
	}

	/* 打印 汇点 <-- 源点 最小花费路径 */
	//PrintfMinCostPath(&tmpvertex, &path, G, v0);
	DijSave(&tmpvertex, &path, G, v0);
}
void PrintfDijMatrix()
{/* 打印必经节点迪杰斯特拉矩阵 */
	int i, j;
	printf("\n【必经节点路径矩阵】\n");
	printf("   ");
	for (j = 0; j < gatherNode.num; j++)
		printf("   %2d   ", gatherNode.p[j]);
	printf("\n");
	for (i = 0; i < gatherNode.num; i++)
	{
		printf("%2d ", gatherNode.p[i]);

		for (j = 0; j < gatherNode.num; j++)
		{
			printf(" %2d(%2d) ", DijMatrix[i*gatherNode.num + j].LayerNum,
				DijMatrix[i*gatherNode.num + j].cost);
		}
		printf("\n");
	}
	printf("\n");
}
void PrintfDiffer()
{
	int i, j;
	printf("\n【必经节点路径矩阵】\n");
	printf("   ");
	for (j = 0; j < gatherNode.num; j++)
		printf("   %2d   ", gatherNode.p[j]);
	printf("\n");
	for (i = 0; i < gatherNode.num; i++)
	{
		printf("%2d ", gatherNode.p[i]);

		for (j = 0; j < gatherNode.num; j++)
		{
			if (DijMatrix[i*gatherNode.num + j].LayerNum == pPathMatrix[i*gatherNode.num + j].LayerNum)
			{
				printf("        ");
			}
			else
			{
				printf(" %2d(%2d) ", DijMatrix[i*gatherNode.num + j].LayerNum,
					DijMatrix[i*gatherNode.num + j].cost);
			}
		}
		printf("\n");
	}
	printf("\n");
}
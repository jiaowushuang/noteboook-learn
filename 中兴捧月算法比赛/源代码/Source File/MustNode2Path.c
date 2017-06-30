#include <stdio.h>
#include "SeqStack.h"
#include "SeqQueue.h"
#include "Storage.h"
#include "MustNode2Path.h"

void InitGatherNode(AdjListGraph *G)
{/* 建立必经节点集合（起始、终止节点+必经节点+必经边节点）*/
	int i, j;

	gatherNode.num = G->MustNodeNum + 2 * G->MustEdgeNum + 2;
	gatherNode.p = (int *)malloc(gatherNode.num * sizeof(int));

	j = 0; /* 加入起始节点+终止节点 */
	gatherNode.p[j++] = G->StartNode; gatherNode.p[j++] = G->EndNode;

	for (i = 1; i <= G->MustNodeNum; i++)
	{//加入必经节点
		gatherNode.p[j++] = mustNodeLink.ListData[i].no;
	}
	for (i = 1; i <= G->MustEdgeNum; i++)
	{//加入必经边的节点
		gatherNode.p[j++] = mustEdgeLink.ListData[i].no1;
		gatherNode.p[j++] = mustEdgeLink.ListData[i].no2;
	}

	/*删除相同元素——必经边 1-2 1-3 1-4 */
	gatherNode.num = DelSameEle(gatherNode.num, gatherNode.p);

	//printf("\n【所有必经点 = %d】", gatherNode.num);
	//for (i = 0; i < gatherNode.num; i++)
	//{
	//	printf(" %d ", gatherNode.p[i]);
	//}
	//printf("\n");
}
void InitPathMatrix()
{//创建并初始化所有必经节点的路径——规模压缩
	int i, j;
	pPathMatrix = (path2Node *)malloc(gatherNode.num * gatherNode.num * sizeof(path2Node));
	for (i = 0; i < (gatherNode.num - 1); i++)
	{//初始化路径 <i,j>
		for (j = i + 1; j < gatherNode.num; j++)
		{
			path(gatherNode.p[i], gatherNode.p[j], &AdjGraf);
			//PrintfPath(gatherNode.p[i], gatherNode.p[j]);
			//printf("**********************************************************\n");
		}
	}
	for (i = 0; i < (gatherNode.num - 1); i++)
	{//无向图 <i,j> = <j,i>
		for (j = i + 1; j < gatherNode.num; j++)
		{
			pPathMatrix[j*gatherNode.num + i].LayerNum = pPathMatrix[i*gatherNode.num + j].LayerNum;
			pPathMatrix[j*gatherNode.num + i].PathNum = pPathMatrix[i*gatherNode.num + j].PathNum;
			pPathMatrix[j*gatherNode.num + i].link = pPathMatrix[i*gatherNode.num + j].link;
		}
	}
	for (i = 0; i < gatherNode.num; i++)
	{// <i,i>
		pPathMatrix[i*gatherNode.num + i].LayerNum = 0;
		pPathMatrix[i*gatherNode.num + i].PathNum = 0;
		pPathMatrix[i*gatherNode.num + i].minCost = 0;
		pPathMatrix[i*gatherNode.num + i].minCostIndex = 0;
		pPathMatrix[i*gatherNode.num + i].link = NULL;
	}
	//PathMatrixLayer();
}
void PathMatrixLayer()
{/* 打印必经节点路径矩阵 */
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
			int cost = MAX_VALUE;
			int hangNum = pPathMatrix[i*gatherNode.num + j].LayerNum + 1;
			for (int k = 0; k < pPathMatrix[i*gatherNode.num + j].PathNum; k++)
			{
				if (pPathMatrix[i*gatherNode.num + j].link[k*hangNum + 0] < cost)
				{
					cost = pPathMatrix[i*gatherNode.num + j].link[k*hangNum + 0];
					pPathMatrix[i*gatherNode.num + j].minCostIndex = k;
					pPathMatrix[i*gatherNode.num + j].minCost = cost;
				}
			}
			printf(" %2d(%2d) ", pPathMatrix[i*gatherNode.num + j].LayerNum,
				pPathMatrix[i*gatherNode.num + j].minCost);
		}
		printf("\n");
	}
	printf("\n");
}
int getPos(int no)
{//获得必须经过的节点元素在所有必经点集合数组中的下标位置
	int i;
	for (i = 0; i < gatherNode.num; i++)
	{
		if (no == gatherNode.p[i])
		{
			return i;
		}
	}
	return 0;
}
void pathSave(int s, int t, AdjListGraph *G)
{
	int cost=0;
	int hangNum = pPathMatrix[getPos(s)*gatherNode.num+getPos(t)].LayerNum + 1;
	//int pathNum = pPathMatrix[getPos(s)*gatherNode.num+getPos(t)].PathNum;
	EdgeNodeType *p;
	int pathNo = 0;//路径序号
	int k, j, i=0;
	int path[VERTEX_MAX];
	SeqStack *Stack;
	PreNodeType *gPre_t, *gPre;//指向前驱节点类型的指针
	Stack = SeqStackInit();
	for (gPre_t = G->VNode[t].firstPre; gPre_t != NULL; gPre_t = gPre_t->nextPre)
	{//打印路径——DFS
		++pathNo; // printf("path[%d]: ", ++pathNo);
		k = 0;
		path[k++] = t;  //printf("%d <-- ", t);
		for (j = gPre_t->pre_No; j != s; j = G->VNode[j].firstPre->pre_No)
		{
			path[k++] = j;  //printf("%d <-- ", j);
			gPre = G->VNode[j].firstPre->nextPre;
			for (gPre = G->VNode[j].firstPre->nextPre; gPre != NULL; gPre = gPre->nextPre)
			{//若节点有多个前驱节点，将该节点其余前驱节点啊压入堆栈
				SeqStackPush(Stack, gPre->pre_No);
			}
		}
		path[k] = s; //printf("%d\n", s);
		i = 0; cost = 0;
		i++;  pPathMatrix[getPos(s)*gatherNode.num+getPos(t)].link[hangNum*(pathNo-1)+i] = s; //s
		for (; k > 0; k--)
		{
			i++;  pPathMatrix[getPos(s)*gatherNode.num+getPos(t)].link[hangNum*(pathNo - 1)+i] = path[k-1];
			for (p = G->VNode[path[k]].firstEdge;
				p->End_No != path[k-1]; p = p->nextEdge);
			cost += p->E_data.weight;
		}
		pPathMatrix[getPos(s)*gatherNode.num+getPos(t)].link[hangNum*(pathNo - 1)] = cost;
		while (!SeqStackIsEmpty(Stack))
		{
			SeqStackPop(Stack, &j);
			++pathNo; // printf("path[%d]: ", ++pathNo);
			for (k = 0; k < VERTEX_MAX; k++)
			{//寻找新路径与上次路径首次不一样的节点
				if (G->isTrav[path[k]] == G->isTrav[j])
				{//与上条路径首次不一样的节点——两节点在该路径上的层次一样
					path[k] = j;
					break;//执行完该循坏块的本次循环内容之后跳出循环
				}
				else
				{//打印新路径与上次路径一样的部分
					//printf("%d <-- ", path[k]);
				}
			}
			for (; j != s; j = G->VNode[j].firstPre->pre_No)
			{//打印新路径的剩余部分
				path[k++] = j;  //printf("%d <-- ", j);
				gPre = G->VNode[j].firstPre->nextPre;
				for (gPre = G->VNode[j].firstPre->nextPre; gPre != NULL; gPre = gPre->nextPre)
				{//若节点有多个前驱节点，将该节点其余前驱节点啊压入堆栈
					SeqStackPush(Stack, gPre->pre_No);
				}
			}
			path[k] = s; //printf("%d\n", s);
			i = 0;  cost = 0;
			i++;  pPathMatrix[getPos(s)*gatherNode.num+getPos(t)].link[hangNum*(pathNo - 1) + i] = s; //s
			for (; k > 0; k--)
			{
				i++;  pPathMatrix[getPos(s)*gatherNode.num+getPos(t)].link[hangNum*(pathNo - 1) + i] = path[k - 1];
				for (p = G->VNode[path[k]].firstEdge;
					p->End_No != path[k-1]; p = p->nextEdge);
				cost += p->E_data.weight;
			}
			pPathMatrix[getPos(s)*gatherNode.num+getPos(t)].link[hangNum*(pathNo - 1)] = cost;
		}
	}
	//printf("path num  of path s --> t = %d\n", pathNo);
	SeqStackFree(Stack);
	ClearAdjPre(G);
}
void pathOut(int s, int t, AdjListGraph *G)
{
	int pathNo = 0;//路径序号
	int k, j;
	int path[VERTEX_MAX];
	SeqStack *Stack;
	PreNodeType *gPre_t, *gPre;//指向前驱节点类型的指针
	Stack = SeqStackInit();
	for(gPre_t = G->VNode[t].firstPre; gPre_t != NULL; gPre_t = gPre_t->nextPre )
	{//打印路径——DFS
		printf("path[%d]: ", ++pathNo);
		k = 0;  
		path[k++] = t;  printf("%d <-- ", t);
		for (j = gPre_t->pre_No; j != s; j = G->VNode[j].firstPre->pre_No)
		{
			path[k++] = j;  printf("%d <-- ", j);
			gPre = G->VNode[j].firstPre->nextPre;
			for (gPre = G->VNode[j].firstPre->nextPre; gPre != NULL; gPre = gPre->nextPre)
			{//若节点有多个前驱节点，将该节点其余前驱节点啊压入堆栈
				SeqStackPush(Stack, gPre->pre_No);
			}
		}
		path[k++] = s; printf("%d\n", s);
		while (!SeqStackIsEmpty(Stack))
		{
			SeqStackPop(Stack, &j);
			printf("path[%d]: ", ++pathNo);
			for (k = 0; k < VERTEX_MAX; k++)
			{//寻找新路径与上次路径首次不一样的节点
				if (G->isTrav[path[k]] == G->isTrav[j])
				{//与上条路径首次不一样的节点——两节点在该路径上的层次一样
					path[k] = j;
					break;//执行完该循坏块的本次循环内容之后跳出循环
				}
				else
				{//打印新路径与上次路径一样的部分
					printf("%d <-- ", path[k]);
				}
			}
			for (; j != s; j = G->VNode[j].firstPre->pre_No)
			{//打印新路径的剩余部分
				path[k++] = j;  printf("%d <-- ", j);
				gPre = G->VNode[j].firstPre->nextPre;
				for (gPre = G->VNode[j].firstPre->nextPre; gPre != NULL; gPre = gPre->nextPre)
				{//若节点有多个前驱节点，将该节点其余前驱节点啊压入堆栈
					SeqStackPush(Stack, gPre->pre_No);
				}
			}
			path[k++] = s; printf("%d\n", s);
		}
	}
	//printf("path num  of path s --> t = %d\n", pathNo);
	SeqStackFree(Stack);
	//ClearAdjPre(G);
}
/*求 s --> t 的最小跳数所有路径（路径权值均为单位值）*/
int path(int s, int t, AdjListGraph *G)
{//bfs按层次遍历改进
	int i, j;
	int pathNum = 0;    // s-->t 的(最少跳数)路径数目
	int MinLayerNum = 1;// s-->t 路径的最少跳数
	int eleNumNowLayer = 0, eleNumLastLayer = 1; 
	//用于找到最少跳数的所有路径（按层次遍历，访问完该层的最后一个元素，确保发现最少跳数的所有路径）
	EdgeNodeType *p;    //指向邻接表边类型的指针
	PreNodeType *gPre;  //指向顶点前驱顶点类型的指针
	SeqQueue *Q;        //队列指针

	Q = SeqQueueInit();
	GrafIsTravClear(G);            //清除访问标记—— set MAX_VALUE
	G->isTrav[s] = MinLayerNum++;  //标记节点层次 
	SeqQueueIn(Q, s); 
	while (!SeqQueueIsEmpty(Q))
	{
		SeqQueueOut(Q, &i); eleNumLastLayer--;
		p = G->VNode[i].firstEdge;
		while (p != NULL)
		{
			if (p->End_No == t)
				pathNum++;
			if (G->isTrav[i] < G->isTrav[p->End_No])
			{
				SeqQueueIn(Q, p->End_No); eleNumNowLayer++;
				G->isTrav[p->End_No] = MinLayerNum; //标记节点层次
				/*仿邻接表形式为节点设置其前驱节点（多个前驱节点、避免重复）*/
				gPre = G->VNode[p->End_No].firstPre;
				while (gPre != NULL)
				{//查找该节点是否已经存在前驱节点 i 
					if (i != gPre->pre_No)
					{
						gPre = gPre->nextPre;
					}
					else
					{
						break;
					}
				}
				if (gPre == NULL)
				{//该节点不存在前驱节点 i, 设置 i 为其前驱节点 
					gPre = (PreNodeType *)malloc(sizeof(PreNodeType));
					gPre->pre_No = i;
					gPre->nextPre = G->VNode[p->End_No].firstPre;
					G->VNode[p->End_No].firstPre = gPre;
				}
			}
			p = p->nextEdge;
		}
		if(eleNumLastLayer == 0)
		{//上一次压入的节点已经全部弹出 && 当前层的节点已经全部压入
			eleNumLastLayer = eleNumNowLayer;
			eleNumNowLayer = 0;
			MinLayerNum++;//节点层次+1
			if (G->VNode[t].firstPre != NULL )
			{//已经寻找到路径
				//printf("layer   of path s --> t = %d\n", MinLayerNum - 1);
				//printf("pathNum of path s --> t = %d\n", pathNum);
				pPathMatrix[getPos(s)*gatherNode.num+getPos(t)].LayerNum = MinLayerNum - 1;
				pPathMatrix[getPos(s)*gatherNode.num+getPos(t)].PathNum = pathNum;
				pPathMatrix[getPos(s)*gatherNode.num+getPos(t)].link = //MinLayerNum - 1 + 1
					(int *)malloc(pathNum*MinLayerNum*sizeof(int));//0位置存储费用
				//pathOut(s, t, G);
				pathSave(s, t, G);
				break;
			}
		}
	}/* end while (!SeqQueueIsEmpty(Q)) */
	SeqQueueFree(Q);
}
void PrintfPath(int s, int t)
{
	int i, j;
	int num = pPathMatrix[getPos(s)*gatherNode.num+getPos(t)].LayerNum + 1;
	printf("[%2d-->%2d]: path num = %d, layer = %d\n", s, t, 
		pPathMatrix[getPos(s)*gatherNode.num+getPos(t)].PathNum, pPathMatrix[getPos(s)*gatherNode.num+getPos(t)].LayerNum);
	for (i = 0; i < pPathMatrix[getPos(s)*gatherNode.num+getPos(t)].PathNum; i++)
	{
		printf("path%2d【%2d】:  ", i + 1, 
			pPathMatrix[getPos(s)*gatherNode.num+getPos(t)].link[i*num + 0]);
		for (j = 1; j < pPathMatrix[getPos(s)*gatherNode.num+getPos(t)].LayerNum; j++)
		{
			printf("%d-->", pPathMatrix[getPos(s)*gatherNode.num+getPos(t)].link[i*num+j]);
		}
		printf("%d", pPathMatrix[getPos(s)*gatherNode.num+getPos(t)].link[i*num + j]);
		printf("\n");
	}
}
void ClearAdjPre(AdjListGraph *G)
{
	int i;
	PreNodeType *gPre, *p;
	for (i = 0; i < G->VertexNum; i++)
	{
		gPre = G->VNode[i].firstPre;
		G->VNode[i].firstPre = NULL;
		while (gPre)
		{
			p = gPre;
			gPre = gPre->nextPre;
			free(p);
		}
	}
}
void OutAdjPre(AdjListGraph *G)
{
	int i;
	PreNodeType *gPre;

	for (i = 0; i < G->VertexNum; i++)
	{
		printf("顶点 %2d ", G->VNode[i].V_data.No);
		gPre = G->VNode[i].firstPre;
		while (gPre)
		{
			printf(" --> %2d", gPre->pre_No);
			gPre = gPre->nextPre;
		}
		printf("\n");
	}
}
void GrafIsTravClear(AdjListGraph *G)
{
	int j;
	for (j = 0; j<G->VertexNum; j++) //清除各顶点遍历标志 
		G->isTrav[j] = MAX_VALUE;
}
int DelSameEle(int num, int *p)
{
	int i = 1, j, k = 0;
	//for (j = 0; j < num; j++)
	//	printf(" %d ", p[j]);
	for (j = 1; j < num;)
	{
		for (k = 0; k < i; k++)
		{
			if (p[j] == p[k])
			{
				break;
			}
		}
		if (k != i) // p[j] 与集合现有元素值相同
		{
			j++;
		}
		else
		{//将 p[j] 加入集合
			p[i++] = p[j++];
		}
	}
	//printf("\n");
	//for (j = 0; j < i; j++)
	//	printf(" %d ", p[j]);
	return i;
}
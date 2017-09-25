#include <stdio.h>
#include "ShortestPath.h"
#include "MinHeap.h"
#include <Storage.h>
#include "cost.h"
#include "MustNode2Path.h"

DijkstraMatrix *DijMatrix;

void InitDijMatrix()
{//��ʼ���Ͻ�˹�����ؾ��ڵ���С���Ѿ���
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
{//��С���Ż��汾�����Ͻ�˹�����㷨
	MinHeap *pQueue;          //��С��ָ��
	ElementType ele,minNode;  //��С������Ԫ��
	int path[VERTEX_MAX];     //ĳԴ�㵽�յ㾭���Ķ���
	int tmpvertex[VERTEX_MAX];//���·�����յ㼯��
	EdgeNodeType  *pEdge;     //ָ�����Ϣ��ָ��
	int i, k;

	pQueue = MinHeapInit(G->VertexNum);
	for (i = 0; i < G->VertexNum; i++)
	{//��ʼ������
		pQueue->pos[i] = G->VertexNum + 1; //���ýڵ� i ����С�ѵ�λ�ã��±꣩
		path[i] = v0;
		tmpvertex[i] = 0; 
	}
	tmpvertex[v0] = 1; //������v0��ӵ�����U�� 
	pEdge = G->VNode[v0].firstEdge;
	while (pEdge != NULL)
	{//��ʼ��V0�����ڽӽڵ㣬�����ҵ���С����
		ele.weight = pEdge->E_data.weight;
		ele.nodeID = pEdge->End_No;
		MinHeapInsertEle(&ele, pQueue);
		pEdge = pEdge->nextEdge;
	}
	for (i = 0; i < G->VertexNum; i++)
	{
		Delete(pQueue, &minNode);
		tmpvertex[minNode.nodeID] = 1;  //������k���뼯��U
		pEdge = G->VNode[minNode.nodeID].firstEdge;
		while (pEdge != NULL)
		{//�� minNode.nodeID �ڵ��ɳ������ڵ�
			if (tmpvertex[pEdge->End_No] == 0)
			{
				if (minNode.weight + pEdge->E_data.weight <
					pQueue->elements[pQueue->pos[pEdge->End_No]].weight)
				{//�ɳڲ���
					/* �жϽڵ��Ƿ�һ���������С���� */
					if (pQueue->pos[pEdge->End_No] > G->VertexNum)
					{//���ýڵ������С����
						ele.weight = pEdge->E_data.weight;
						ele.nodeID = pEdge->End_No;
						MinHeapInsertEle(&ele, pQueue);
					}
					else
					{//�����ýڵ�����С�ѵ�λ��
						Adjust(pEdge->End_No, pQueue,
							(minNode.weight + pEdge->E_data.weight));
					}
					path[pEdge->End_No] = minNode.nodeID;
				}
			}
			pEdge = pEdge->nextEdge;
		}
	}
	
	/* ��ӡ ��� <-- Դ�� ��С����·�� */
	//PrintfMinCostPath(&tmpvertex, &path, G, v0);
	DijSave(&tmpvertex, &path, G, v0);
}
void PrintfMinCostPath(int *tmpvertex, int *path, AdjListGraph *G, int v0)
{
	int i, k;
	printf("\n�ڽӱ�ͼ��������%d������������·����(�յ�<Դ��):\n", G->VNode[v0].V_data.No);
	for (i = 0; i<G->VertexNum; i++)//������
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
			printf("%c<-%c:��·��\n", G->VNode[i].V_data.No, G->VNode[v0].V_data.No);
	}
}
void DijSave(int *tmpvertex, int *path, AdjListGraph *G, int v0)
{/* ������С s -> t */
	int i, k;
	EdgeNodeType *p;
	for (i = 0; i<gatherNode.num; i++)//������
	{
		int layer = 0;
		int link[VERTEX_MAX];
		int cost = 0;
		if (gatherNode.p[i] != v0)
		{
			if (tmpvertex[gatherNode.p[i]] == 1)
			{
				k = gatherNode.p[i]; /* ��ֹ�ڵ� t */
				while (k != v0)
				{
					link[layer++] = G->VNode[k].V_data.No;  
					//printf("%d<--", G->VNode[k].V_data.No);
					k = path[k];
				}
				link[layer++] = G->VNode[k].V_data.No; 
				//printf("%d\n", G->VNode[k].V_data.No); /* ��ʼ�ڵ� */
				
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
{/* �Ͻ�˹�����㷨�����ڽӱ����Դ��( no )���·�� */
	int weight[VERTEX_MAX];//ĳԴ�㵽����������·������
	int path[VERTEX_MAX];  //ĳԴ�㵽�յ㾭���Ķ���
	int tmpvertex[VERTEX_MAX];//���·�����յ㼯��
	int i, j, k, min;
	EdgeNodeType  *pEdge;

	for (i = 0; i<G->VertexNum; i++)
	{/* ��ʼ�������� */
		weight[i] = MAX_VALUE;
		path[i] = -1;
		tmpvertex[i] = 0; //��ʼ���յ㼯��Ϊ�� 
	}

	tmpvertex[v0] = 1; //������v0��ӵ�����U�� 
	weight[v0] = 0; //��Դ�����Ȩֵ��Ϊ0 
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
		k = v0; //Դ������� 
		for (j = 0; j < G->VertexNum; j++)
		{//��U�����в���δ�ö������СȨֵ 
			if (tmpvertex[j] == 0 && weight[j] < min)
			{
				min = weight[j];
				k = j;
			}
		}
		tmpvertex[k] = 1;//������k���뼯��U
		pEdge = G->VNode[k].firstEdge;
		while (pEdge != NULL)
		{
			if (tmpvertex[pEdge->End_No] == 0)
			{
				if (weight[k] + pEdge->E_data.weight < weight[pEdge->End_No])
				{//�и�СȨֵ��·��
					weight[pEdge->End_No] = weight[k] + pEdge->E_data.weight;
					path[pEdge->End_No] = k;
				}
			}
			pEdge = pEdge->nextEdge;
		}
	}

	/* ��ӡ ��� <-- Դ�� ��С����·�� */
	//PrintfMinCostPath(&tmpvertex, &path, G, v0);
	DijSave(&tmpvertex, &path, G, v0);
}
void PrintfDijMatrix()
{/* ��ӡ�ؾ��ڵ�Ͻ�˹�������� */
	int i, j;
	printf("\n���ؾ��ڵ�·������\n");
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
	printf("\n���ؾ��ڵ�·������\n");
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
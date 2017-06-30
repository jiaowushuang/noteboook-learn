#include <stdio.h>
#include <MustNode2Path.h>
#include <Storage.h>
#include "Joint.h"
#include "2opt.h"
#include "cost.h"
#include "ShortestPath.h"
#include "PathNodeSeqList.h"
#include "SeqQueue.h"
#include "SeqStack.h"
#include "MaxHeap.h"

int hopNum;                /*��·����С����*/
int *cost_layer;  /*��������1�� ���ؾ��ڵ�� -cost/-layer */
float rate = 1.5; /*�滻����*/ /* 1.5 - 3 */
int VneedTHnum; /*  ( MaxPassVertex - hopNum ) / rate  */
int Wcompare;     /*��������2�� �滻���ýϸߵ�·��*/
/* ȡ�ٷֱ�λ������������λ���� VneedTHnum / hopNum */

int IsMustEdge(int no1, int no2, int *weight)
{//�ж��������Ƿ�Ϊ�ؾ���
	EdgeNodeType *p = NULL;
	p = AdjGraf.VNode[no1].firstEdge;
	while (p != NULL)
	{
		if (p->End_No == no2)
		{
			*weight = p->E_data.weight;/* ��ȡ�ñߵ�Ȩֵ */

			if (p->E_data.eType == 1)
				return 1;
			else
				break;
		}
		else
		{
			p = p->nextEdge;
		}
	}
	return 0;
}
int getCost(int no1, int no2)
{
	EdgeNodeType *p = NULL;
	p = AdjGraf.VNode[no1].firstEdge;

	while (p != NULL)
	{
		if (p->End_No == no2)
		{
			return p->E_data.weight;/* ��ȡ�ñߵ�Ȩֵ */
		}
		else
		{
			p = p->nextEdge;
		}
	}
	return MAX_VALUE;
}
int Layer_3(int s, int t, int lastLayerMincost, int *link)
{/*����Ϊ3ʱ���ڵ������С����·��*/
	int minCost = lastLayerMincost; /* s->t�Ļ��� */
	EdgeNodeType  *p1;
	p1 = AdjGraf.VNode[s].firstEdge;
	while (p1 != NULL)
	{/* ���� p1 */
		if (p1->E_data.weight + getCost(p1->End_No, t) < minCost)
		{//�ɳڲ���
			minCost = p1->E_data.weight + getCost(p1->End_No, t);
			*link = p1->End_No;
			//printf("[ cost = %d ]: %d -> %d -> %d\n", minCost, s, link[0], t);
		}
		p1 = p1->nextEdge;
	}
	return minCost;
}
int Layer_4(int s, int t, int lastLayerMincost, int *link)
{
	int minCost = lastLayerMincost; /* s->t�Ļ��� */
	EdgeNodeType  *p1, *p2;
	int s_p1Cost, p1_p2Cost, p2_tCost;
	p1 = AdjGraf.VNode[s].firstEdge;/* ����ֵ�� p1 */
	while (p1 != NULL)
	{/* ���� p1 */
		s_p1Cost = p1->E_data.weight;
		if ( (s_p1Cost < minCost) && ( p1->End_No != t ) )
		{
			p2 = AdjGraf.VNode[p1->End_No].firstEdge;/* ����ֵ�� p2 */
			while (p2 != NULL)
			{/* ���� p2 */
				p1_p2Cost = p2->E_data.weight;
				if  ( ( (s_p1Cost + p1_p2Cost) < minCost) && (p2->End_No != t) )
				{
					p2_tCost = getCost(p2->End_No, t);
					if ( (s_p1Cost + p1_p2Cost + p2_tCost) < minCost )
					{//�ɳڲ���
						minCost = s_p1Cost + p1_p2Cost + p2_tCost;
						link[0] = p1->End_No;
						link[1] = p2->End_No;
						/*printf("[ cost = %d ]: %d -> %d -> %d -> %d\n", minCost, 
							s, link[0], link[1], t);*/
					}
				}
				p2 = p2->nextEdge;
			}/* ���� p1 */
		}
		p1 = p1->nextEdge;
	}/* ���� p1 */
	return minCost;
}
int Layer_5(int s, int t, int lastLayerMincost, int *link)
{
	int minCost = lastLayerMincost; /* s->t�Ļ��� */
	EdgeNodeType  *p1, *p2, *p3;
	int s_p1Cost, p1_p2Cost, p2_p3Cost, p3_tCost;

	p1 = AdjGraf.VNode[s].firstEdge; /* ����ֵ�� p1 */
	while (p1 != NULL)
	{/* ���� p1 */
		s_p1Cost = p1->E_data.weight; /* s-p1 ���� */
		if ((s_p1Cost < minCost) && (p1->End_No != t)) 
		{
			p2 = AdjGraf.VNode[p1->End_No].firstEdge; /* ����ֵ�� p2 */
			while (p2 != NULL)
			{/*���� p2 */
				p1_p2Cost = p2->E_data.weight;/* p1-p2 ���� */
				if (((s_p1Cost + p1_p2Cost) < minCost) && (p2->End_No != t))
				{
					p3 = AdjGraf.VNode[p2->End_No].firstEdge;/* ����ֵ�� p3 */
					while (p3 != NULL)
					{/*���� p3 */
						p2_p3Cost = p3->E_data.weight;/* p2-p3 ���� */
						if (((s_p1Cost + p1_p2Cost + p2_p3Cost) < minCost) && 
							(p3->End_No != t))
						{
							p3_tCost = getCost(p3->End_No, t);
							if ((s_p1Cost + p1_p2Cost + p2_p3Cost + p3_tCost) < minCost)
							{//�ɳڲ���
								minCost = s_p1Cost + p1_p2Cost + p2_p3Cost + p3_tCost;
								link[0] = p1->End_No;
								link[1] = p2->End_No;
								link[2] = p3->End_No;
								/*printf("[ cost = %d ]: %d -> %d -> %d -> %d -> %d\n", 
									minCost, s, link[0], link[1], link[2], t);*/
							}
						}
						p3 = p3->nextEdge;
					}/*���� p3 */
				}
				p2 = p2->nextEdge;
			}/*���� p2 */
		}
		p1 = p1->nextEdge;
	}/*���� p1 */
	return minCost;
}
int Layer_n(int s, int t, int cost, int n)
{
	int weight[VERTEX_MAX], pre[VERTEX_MAX];
	EdgeNodeType  *pEdge; /* ָ��ߵ�ָ��*/
	SeqQueue *Q;          /* ����ָ�� */
	int eleNumNowLayer = 0, eleNumLastLayer = 1; /* ����α��� */
	int LayerNum = 1; /* ��ǰ���� = 1*/
	int v;
	int minCost = cost;

	for (int i = 0; i<AdjGraf.VertexNum; i++)
	{/* ��ʼ�������� */
		weight[i] = MAX_VALUE;
		pre[i] = -1; 
	}
	Q = SeqQueueInit();
	weight[s] = 0;
	SeqQueueIn(Q, s); LayerNum++;    /* ��ǰ���� +1 */
	while (!SeqQueueIsEmpty(Q))
	{
		SeqQueueOut(Q, &v); eleNumLastLayer--;
		pEdge = AdjGraf.VNode[v].firstEdge;
		while (pEdge != NULL)
		{/* ������ʣ���ǰ����Ϊ LayerNum */
			/* s->...->i->pEdge->End_No  < s->t ()*/
			if ( weight[v] + pEdge->E_data.weight < minCost)
			{/* �ɳڲ��� */
				if (pEdge->End_No == t)
				{/*�ڵ�ǰ���ҵ� t */
				/* �Ƚ�ѡ���ڵ�ǰ������ s->t ���ѽ�С��·�� */
					weight[pEdge->End_No] = weight[v] + pEdge->E_data.weight;
					pre[pEdge->End_No] = v;
					minCost = weight[pEdge->End_No];
				}
				else
				{
					SeqQueueIn(Q, pEdge->End_No); eleNumNowLayer++;
					weight[pEdge->End_No] = weight[v] + pEdge->E_data.weight;
					pre[pEdge->End_No] = v;
				}
			}
			pEdge = pEdge->nextEdge;
		}
		if (eleNumLastLayer == 0) /* һ�������� */
		{//��һ��ѹ��Ľڵ��Ѿ�ȫ������ && ��ǰ��Ľڵ��Ѿ�ȫ��ѹ��
			eleNumLastLayer = eleNumNowLayer;
			eleNumNowLayer = 0;
			LayerNum++;//�ڵ���+1
			if (LayerNum > n) break;
		}
	}/* end while (!SeqQueueIsEmpty(Q)) */

	PrintfCostLayer(weight[t], &pre, n);
	SeqQueueFree(Q);
}
void PrintfCostLayer(int cost,int *pre, int n)
{
	printf("layer = %d, cost = %d\n", n, cost);
}
float getCost_Layer(int no1, int no2, int weight, MaxHeapEdgeType *maxHeap)
{//��ȡ�����ڵ�֮��
	int cost_3, cost_4, cost_5;
	float rate_3, rate_4, rate_5;
	//int weight;
	int link3, link4[2], link5[3];
	static int index;
	//if (IsMustEdge(no1, no2, &weight)) /* ��ȡ�ñߵ�Ȩֵ */
	//	return 0; /* �ñ�Ϊ�ؾ��� */

	cost_3 = Layer_3(no1, no2, weight, &link3);
	cost_4 = Layer_4(no1, no2, weight, &link4);
	cost_5 = Layer_5(no1, no2, weight, &link5);
	//printf("%2d: %d  %d  %d \n", ++index, cost_3, cost_4, cost_5);
	rate_3 = (float)(weight - cost_3);
	rate_4 = (float)(weight - cost_4) / 2;
	rate_5 = (float)(weight - cost_5) / 3;
	if ((weight == cost_3) && (weight == cost_4) && (weight == cost_5))
	{
		maxHeap->WeightChange = weight;
		maxHeap->LayerNUmChange = 2;
		maxHeap->Price = 0;
	}
	else if((rate_3 >= rate_4) && (rate_3 >= rate_5))
	{/* 3 */
		maxHeap->WeightChange = cost_3;
		maxHeap->LayerNUmChange = 3;
		maxHeap->Price = rate_3;
		maxHeap->path[0] = link3;
	}
	else if( (rate_4 >= rate_5) && (rate_4 >= rate_3))
	{/* 4 */
		maxHeap->WeightChange = cost_4;
		maxHeap->LayerNUmChange = 4;
		maxHeap->Price = rate_4;
		maxHeap->path[0] = link4[0]; maxHeap->path[1] = link4[1];
	}
	else if((rate_5 >= rate_4) && (rate_5 >= rate_3))
	{/* 5 */
		maxHeap->WeightChange = cost_5;
		maxHeap->LayerNUmChange = 5;
		maxHeap->Price = rate_5;
		maxHeap->path[0] = link5[0]; maxHeap->path[1] = link5[1]; maxHeap->path[2] = link5[2];
	}
}


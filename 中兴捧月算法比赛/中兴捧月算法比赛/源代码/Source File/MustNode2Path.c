#include <stdio.h>
#include "SeqStack.h"
#include "SeqQueue.h"
#include "Storage.h"
#include "MustNode2Path.h"

void InitGatherNode(AdjListGraph *G)
{/* �����ؾ��ڵ㼯�ϣ���ʼ����ֹ�ڵ�+�ؾ��ڵ�+�ؾ��߽ڵ㣩*/
	int i, j;

	gatherNode.num = G->MustNodeNum + 2 * G->MustEdgeNum + 2;
	gatherNode.p = (int *)malloc(gatherNode.num * sizeof(int));

	j = 0; /* ������ʼ�ڵ�+��ֹ�ڵ� */
	gatherNode.p[j++] = G->StartNode; gatherNode.p[j++] = G->EndNode;

	for (i = 1; i <= G->MustNodeNum; i++)
	{//����ؾ��ڵ�
		gatherNode.p[j++] = mustNodeLink.ListData[i].no;
	}
	for (i = 1; i <= G->MustEdgeNum; i++)
	{//����ؾ��ߵĽڵ�
		gatherNode.p[j++] = mustEdgeLink.ListData[i].no1;
		gatherNode.p[j++] = mustEdgeLink.ListData[i].no2;
	}

	/*ɾ����ͬԪ�ء����ؾ��� 1-2 1-3 1-4 */
	gatherNode.num = DelSameEle(gatherNode.num, gatherNode.p);

	//printf("\n�����бؾ��� = %d��", gatherNode.num);
	//for (i = 0; i < gatherNode.num; i++)
	//{
	//	printf(" %d ", gatherNode.p[i]);
	//}
	//printf("\n");
}
void InitPathMatrix()
{//��������ʼ�����бؾ��ڵ��·��������ģѹ��
	int i, j;
	pPathMatrix = (path2Node *)malloc(gatherNode.num * gatherNode.num * sizeof(path2Node));
	for (i = 0; i < (gatherNode.num - 1); i++)
	{//��ʼ��·�� <i,j>
		for (j = i + 1; j < gatherNode.num; j++)
		{
			path(gatherNode.p[i], gatherNode.p[j], &AdjGraf);
			//PrintfPath(gatherNode.p[i], gatherNode.p[j]);
			//printf("**********************************************************\n");
		}
	}
	for (i = 0; i < (gatherNode.num - 1); i++)
	{//����ͼ <i,j> = <j,i>
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
{/* ��ӡ�ؾ��ڵ�·������ */
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
{//��ñ��뾭���Ľڵ�Ԫ�������бؾ��㼯�������е��±�λ��
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
	int pathNo = 0;//·�����
	int k, j, i=0;
	int path[VERTEX_MAX];
	SeqStack *Stack;
	PreNodeType *gPre_t, *gPre;//ָ��ǰ���ڵ����͵�ָ��
	Stack = SeqStackInit();
	for (gPre_t = G->VNode[t].firstPre; gPre_t != NULL; gPre_t = gPre_t->nextPre)
	{//��ӡ·������DFS
		++pathNo; // printf("path[%d]: ", ++pathNo);
		k = 0;
		path[k++] = t;  //printf("%d <-- ", t);
		for (j = gPre_t->pre_No; j != s; j = G->VNode[j].firstPre->pre_No)
		{
			path[k++] = j;  //printf("%d <-- ", j);
			gPre = G->VNode[j].firstPre->nextPre;
			for (gPre = G->VNode[j].firstPre->nextPre; gPre != NULL; gPre = gPre->nextPre)
			{//���ڵ��ж��ǰ���ڵ㣬���ýڵ�����ǰ���ڵ㰡ѹ���ջ
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
			{//Ѱ����·�����ϴ�·���״β�һ���Ľڵ�
				if (G->isTrav[path[k]] == G->isTrav[j])
				{//������·���״β�һ���Ľڵ㡪�����ڵ��ڸ�·���ϵĲ��һ��
					path[k] = j;
					break;//ִ�����ѭ����ı���ѭ������֮������ѭ��
				}
				else
				{//��ӡ��·�����ϴ�·��һ���Ĳ���
					//printf("%d <-- ", path[k]);
				}
			}
			for (; j != s; j = G->VNode[j].firstPre->pre_No)
			{//��ӡ��·����ʣ�ಿ��
				path[k++] = j;  //printf("%d <-- ", j);
				gPre = G->VNode[j].firstPre->nextPre;
				for (gPre = G->VNode[j].firstPre->nextPre; gPre != NULL; gPre = gPre->nextPre)
				{//���ڵ��ж��ǰ���ڵ㣬���ýڵ�����ǰ���ڵ㰡ѹ���ջ
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
	int pathNo = 0;//·�����
	int k, j;
	int path[VERTEX_MAX];
	SeqStack *Stack;
	PreNodeType *gPre_t, *gPre;//ָ��ǰ���ڵ����͵�ָ��
	Stack = SeqStackInit();
	for(gPre_t = G->VNode[t].firstPre; gPre_t != NULL; gPre_t = gPre_t->nextPre )
	{//��ӡ·������DFS
		printf("path[%d]: ", ++pathNo);
		k = 0;  
		path[k++] = t;  printf("%d <-- ", t);
		for (j = gPre_t->pre_No; j != s; j = G->VNode[j].firstPre->pre_No)
		{
			path[k++] = j;  printf("%d <-- ", j);
			gPre = G->VNode[j].firstPre->nextPre;
			for (gPre = G->VNode[j].firstPre->nextPre; gPre != NULL; gPre = gPre->nextPre)
			{//���ڵ��ж��ǰ���ڵ㣬���ýڵ�����ǰ���ڵ㰡ѹ���ջ
				SeqStackPush(Stack, gPre->pre_No);
			}
		}
		path[k++] = s; printf("%d\n", s);
		while (!SeqStackIsEmpty(Stack))
		{
			SeqStackPop(Stack, &j);
			printf("path[%d]: ", ++pathNo);
			for (k = 0; k < VERTEX_MAX; k++)
			{//Ѱ����·�����ϴ�·���״β�һ���Ľڵ�
				if (G->isTrav[path[k]] == G->isTrav[j])
				{//������·���״β�һ���Ľڵ㡪�����ڵ��ڸ�·���ϵĲ��һ��
					path[k] = j;
					break;//ִ�����ѭ����ı���ѭ������֮������ѭ��
				}
				else
				{//��ӡ��·�����ϴ�·��һ���Ĳ���
					printf("%d <-- ", path[k]);
				}
			}
			for (; j != s; j = G->VNode[j].firstPre->pre_No)
			{//��ӡ��·����ʣ�ಿ��
				path[k++] = j;  printf("%d <-- ", j);
				gPre = G->VNode[j].firstPre->nextPre;
				for (gPre = G->VNode[j].firstPre->nextPre; gPre != NULL; gPre = gPre->nextPre)
				{//���ڵ��ж��ǰ���ڵ㣬���ýڵ�����ǰ���ڵ㰡ѹ���ջ
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
/*�� s --> t ����С��������·����·��Ȩֵ��Ϊ��λֵ��*/
int path(int s, int t, AdjListGraph *G)
{//bfs����α����Ľ�
	int i, j;
	int pathNum = 0;    // s-->t ��(��������)·����Ŀ
	int MinLayerNum = 1;// s-->t ·������������
	int eleNumNowLayer = 0, eleNumLastLayer = 1; 
	//�����ҵ���������������·��������α�����������ò�����һ��Ԫ�أ�ȷ��������������������·����
	EdgeNodeType *p;    //ָ���ڽӱ�����͵�ָ��
	PreNodeType *gPre;  //ָ�򶥵�ǰ���������͵�ָ��
	SeqQueue *Q;        //����ָ��

	Q = SeqQueueInit();
	GrafIsTravClear(G);            //������ʱ�ǡ��� set MAX_VALUE
	G->isTrav[s] = MinLayerNum++;  //��ǽڵ��� 
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
				G->isTrav[p->End_No] = MinLayerNum; //��ǽڵ���
				/*���ڽӱ���ʽΪ�ڵ�������ǰ���ڵ㣨���ǰ���ڵ㡢�����ظ���*/
				gPre = G->VNode[p->End_No].firstPre;
				while (gPre != NULL)
				{//���Ҹýڵ��Ƿ��Ѿ�����ǰ���ڵ� i 
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
				{//�ýڵ㲻����ǰ���ڵ� i, ���� i Ϊ��ǰ���ڵ� 
					gPre = (PreNodeType *)malloc(sizeof(PreNodeType));
					gPre->pre_No = i;
					gPre->nextPre = G->VNode[p->End_No].firstPre;
					G->VNode[p->End_No].firstPre = gPre;
				}
			}
			p = p->nextEdge;
		}
		if(eleNumLastLayer == 0)
		{//��һ��ѹ��Ľڵ��Ѿ�ȫ������ && ��ǰ��Ľڵ��Ѿ�ȫ��ѹ��
			eleNumLastLayer = eleNumNowLayer;
			eleNumNowLayer = 0;
			MinLayerNum++;//�ڵ���+1
			if (G->VNode[t].firstPre != NULL )
			{//�Ѿ�Ѱ�ҵ�·��
				//printf("layer   of path s --> t = %d\n", MinLayerNum - 1);
				//printf("pathNum of path s --> t = %d\n", pathNum);
				pPathMatrix[getPos(s)*gatherNode.num+getPos(t)].LayerNum = MinLayerNum - 1;
				pPathMatrix[getPos(s)*gatherNode.num+getPos(t)].PathNum = pathNum;
				pPathMatrix[getPos(s)*gatherNode.num+getPos(t)].link = //MinLayerNum - 1 + 1
					(int *)malloc(pathNum*MinLayerNum*sizeof(int));//0λ�ô洢����
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
		printf("path%2d��%2d��:  ", i + 1, 
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
		printf("���� %2d ", G->VNode[i].V_data.No);
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
	for (j = 0; j<G->VertexNum; j++) //��������������־ 
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
		if (k != i) // p[j] �뼯������Ԫ��ֵ��ͬ
		{
			j++;
		}
		else
		{//�� p[j] ���뼯��
			p[i++] = p[j++];
		}
	}
	//printf("\n");
	//for (j = 0; j < i; j++)
	//	printf(" %d ", p[j]);
	return i;
}
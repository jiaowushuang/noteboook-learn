#include <stdio.h>
#include "MinHeap.h"
#include "Storage.h"

MinHeap *MinHeapInit(int maxElements)
{//��ʼ����С��
	MinHeap *pQueue;
	if (maxElements <= 0)
	{
		printf("error: maxElements <= 0 !");
		getchar();
	}
	if (!(pQueue = (MinHeap *)malloc(sizeof(MinHeap))))
	{
		printf("������С���ڴ�ʧ�ܣ�\n");
		getchar();
		exit(0);
	}
	if (!(pQueue->pos = (int *)malloc((maxElements) * sizeof(int))))
	{
		printf("����Ԫ���ڴ�ʧ�ܣ�\n");
		getchar();
		exit(0);
	}
	if (!(pQueue->elements = (ElementType *)malloc((maxElements + 2) * sizeof(ElementType))))
	{
		printf("����Ԫ���ڴ�ʧ�ܣ�\n");
		getchar();
		exit(0);
	}
	pQueue->capacity = maxElements;
	pQueue->size = 0;
	//�����ڡ��������� capacity  size
	pQueue->elements[0].weight = -1;//������Сֵ��������������
	pQueue->elements[0].nodeID = -1;
	pQueue->elements[maxElements + 1].weight = MAX_VALUE;//�������ֵ��·��������
	pQueue->elements[maxElements + 1].nodeID = -1;
	return pQueue;
}
void MinHeapFree(MinHeap *pQueue)
{
	if (pQueue != NULL)
	{
		free(pQueue->elements);
		free(pQueue);
	}
}
int IsFull(MinHeap *pQueue)
{
	return (pQueue->size == pQueue->capacity);
}
int IsEmpty(MinHeap *pQueue)
{
	return (pQueue->size == 0);
}
int MinHeapInsertEle(ElementType *ele, MinHeap *pQueue)
{//����һ���µ�Ԫ��
	int i;
	//pQueue->elements[0].weight = -1 ������ֹ��������������
	for (i = ++(pQueue->size); ele->weight < pQueue->elements[i / 2].weight; i /= 2)
	{
		pQueue->elements[i] = pQueue->elements[i / 2]; //�³�����
		pQueue->pos[pQueue->elements[i].nodeID] = i;
	}
	pQueue->elements[i] = *ele;
	pQueue->pos[ele->nodeID] = i;
	return i; 
}
int Delete(MinHeap *pQueue,ElementType *minEle)
{//��ȡֵ��С��Ԫ�ز�ɾ���ýڵ�
	int i, child;
	ElementType tailEle;
	*minEle = pQueue->elements[1];
	pQueue->pos[pQueue->elements[1].nodeID] = pQueue->capacity + 1;
	tailEle = pQueue->elements[pQueue->size--];
	for (i = 1; i * 2 <= pQueue->size; i = child)
	{
		child = i * 2;
		if (child < pQueue->size && //������˵���ڵ����Һ���
			pQueue->elements[child].weight > pQueue->elements[child + 1].weight)
		{//ѡȡ���Һ����еĽ�Сֵ
			child++;
		}
		if (tailEle.weight < pQueue->elements[child].weight)
		{//��βԪ�� < ��ǰ�ڵ�Ľ�С�ĺ��� ֱ�����˽���֮ ��ǰ�ڵ㣬��������
			break;
		}
		else
		{//�������˲���
			pQueue->elements[i] = pQueue->elements[child]; //���˲���
			pQueue->pos[pQueue->elements[i].nodeID] = i;
		}
	}
	pQueue->elements[i] = tailEle;
	pQueue->pos[tailEle.nodeID] = i;
	return minEle->nodeID;
}
int Adjust(int v0, MinHeap *pQueue , int weight)
{//Ԫ��Ȩ�ظı䣨һ�������С����������Ԫ������С�ѵ�λ��
	int i;
	//pQueue->elements[0].weight = -1 ������ֹ��������������
	for (i = pQueue->pos[v0]; weight < pQueue->elements[i / 2].weight; i /= 2)
	{
		pQueue->elements[i] = pQueue->elements[i / 2]; //�³�����
		pQueue->pos[pQueue->elements[i].nodeID] = i;
	}
	pQueue->elements[i].weight = weight;
	pQueue->elements[i].nodeID = v0;
	pQueue->pos[v0] = i;
	return i;
}
void HeapTest(void)
{
	MinHeap *pQueue;
	ElementType ele;
	int i, j;
	int TestVal[10] = { 5,8,4,6,2,1,7,9,3,10 };
	pQueue = MinHeapInit(10);
	for (i = 0; i < 10; i++)
	{
		ele.nodeID = i;
		ele.weight = TestVal[i];
		MinHeapInsertEle(&ele, pQueue);
	}
	for (i = 0; i < 12; i++)
		printf("      %d     ", i);
	printf("\n");
	/*for (i = 0; i < 12; i++)
		printf("Node%d(%d) -> ", pQueue->elements[i].nodeID, pQueue->elements[i].weight);
	printf("\n");*/
	for (i = 0; i < 10; i++)
	{
		printf("No%d -%d(%d)  ", i, pQueue->elements[pQueue->pos[i]].nodeID, 
			pQueue->elements[pQueue->pos[i]].weight );
	}
	printf("\n");
	Adjust(7, pQueue, 0);
	for (i = 0; i < 10; i++)
	{
		Delete(pQueue, &ele);
		printf("%d(%d) -> ", ele.nodeID, ele.weight);
		printf("\n");
		for (j = 0; j < 10; j++)
		{
			printf("No%d -%d(%d)  ", j, pQueue->elements[pQueue->pos[j]].nodeID,
				pQueue->elements[pQueue->pos[j]].weight);
		}
		printf("\n");
	}
	printf("\n");
}



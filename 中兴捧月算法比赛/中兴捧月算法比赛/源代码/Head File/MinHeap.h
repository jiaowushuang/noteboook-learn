#pragma once

typedef  struct
{//��С��Ԫ������
	int nodeID;   //�ڵ���
	int weight;   //Ȩ�ء�����ʶ�ؼ���
}ElementType;
typedef struct
{//��С��
	int capacity; /*�������*/
	int size;     /*Ԫ�ظ���*/
	int *pos;     /*pos[v0]��ʾ����v0��Ԫ�������е��±�*/
	ElementType *elements; /*Ԫ�����顪����Ԫ��Ȩ����Ϣ����*/
}MinHeap;
MinHeap *MinHeapInit(int maxElements);
void MinHeapFree(MinHeap *pQueue);
int IsFull(MinHeap *pQueue);
int IsEmpty(MinHeap *pQueue);
int MinHeapInsertEle(ElementType *ele, MinHeap *pQueue);
int Delete(MinHeap *pQueue, ElementType *minEle);
int Adjust(int v0, MinHeap *pQueue, int weight);
void HeapTest(void);
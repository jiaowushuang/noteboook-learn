#pragma once

typedef  struct
{//最小堆元素类型
	int nodeID;   //节点编号
	int weight;   //权重——标识关键字
}ElementType;
typedef struct
{//最小堆
	int capacity; /*最大容量*/
	int size;     /*元素个数*/
	int *pos;     /*pos[v0]表示顶点v0在元素数组中的下标*/
	ElementType *elements; /*元素数组——按元素权重信息排序*/
}MinHeap;
MinHeap *MinHeapInit(int maxElements);
void MinHeapFree(MinHeap *pQueue);
int IsFull(MinHeap *pQueue);
int IsEmpty(MinHeap *pQueue);
int MinHeapInsertEle(ElementType *ele, MinHeap *pQueue);
int Delete(MinHeap *pQueue, ElementType *minEle);
int Adjust(int v0, MinHeap *pQueue, int weight);
void HeapTest(void);
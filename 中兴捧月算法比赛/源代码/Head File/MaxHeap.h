#pragma once

typedef struct
{//最大堆元素-边
	int No;//边起点编号
	int End_NO;//边终点编号

	int Weight;//边权重
	int LayerNum;//条数

	int WeightChange;//路径修改后边的权重
	int LayerNUmChange;//路径修改后的条数

	float Price;//性价比=(WeightChange-Weight)/(LayerNumChange-LayerNum)

	int path[3];//修改后的路径 a-b ==> a-c-d-e-b

}MaxHeapEdgeType;

typedef struct
{//最大堆
	int MaxNum;//最大容量
	int size;//当前容量
	MaxHeapEdgeType* edge;//边数组
}MaxHeapType;

MaxHeapType* MaxHeapInit(int MaxNum);
int MaxHeapIsFull(MaxHeapType* heap);

int MaxHeapAdd(MaxHeapType* heap,MaxHeapEdgeType* edge);//向堆中试图添加一条边
void MaxHeapSortByPrice(MaxHeapType* heap);

void TestMaxHeap();
void OutPrintMaxHeap(MaxHeapType* heap);
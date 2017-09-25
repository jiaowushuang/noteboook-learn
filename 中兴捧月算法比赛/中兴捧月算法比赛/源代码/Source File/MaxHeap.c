#include <stdio.h>
#include "MaxHeap.h"
#include <malloc.h>

MaxHeapType* MaxHeapInit(int MaxNum)
{
	MaxHeapType* q;
	if (MaxNum <= 0)
	{
		printf("error:MaxNum<=0\n");
	}
	if (!(q = (MaxHeapType*)malloc(sizeof(MaxHeapType))))
	{
		printf("申请最大堆内存失败");
		getchar();
		exit(0);
	}
	if (!(q->edge = (MaxHeapEdgeType*)malloc(MaxNum * sizeof(MaxHeapEdgeType))))
	{
		printf("申请最大堆边数组内存失败");
		getchar();
		exit(0);
	}
	q->MaxNum = MaxNum;
	q->size = 0;
	return q;
}

int MaxHeapIsFull(MaxHeapType* heap)
{
	if (heap->size == heap->MaxNum)
		return 1;
	return 0;
}

int GetLastMaxHeapElement(MaxHeapType* heap)
{
	//当堆按权重排序时，获取权重最小的边权重
	if (heap->size == 0)
		return -1;
	else
		return heap->edge[heap->size - 1].Weight;
}

void MaxHeapInsertByWeight(MaxHeapType* heap,MaxHeapEdgeType* edge)
{
	//对边按权重排序进行插入
	int n = heap->size;
	int i = 0;
	for (i = 0; i < n; i++)
	{
		//查找边应该插入的位置
		if (heap->edge[i].Weight < edge->Weight)
			break;
	}
	//i后面的边从后往前依次后移一位
	for (int j = n - 1; j >= i; j--)
		heap->edge[j + 1] = heap->edge[j];
	//将edge插入到对应的位置
	heap->edge[i] = *edge;
	//堆未满时,size+1
	if (heap->size < heap->MaxNum)
		heap->size++;

}

int MaxHeapAdd(MaxHeapType* heap, MaxHeapEdgeType* edge)
{
	if (!MaxHeapIsFull(heap)||GetLastMaxHeapElement(heap) < edge->Weight)
		//堆未满时或者边的权重大于当前权重最小边的权重时
	{
		MaxHeapInsertByWeight(heap, edge);
		return 1;
	}
	return 0;
}

void MaxHeapSortByPrice(MaxHeapType* heap)
{
	//冒泡排序:从大到小
	int flag = 1;
	int n = heap->size;
	while (flag)
	{
		flag = 0;//标志复位

		//性价比小的边下降
		for (int i = 0; i < n - 1; i++)
		{
			if (heap->edge[i].Price < heap->edge[i + 1].Price)
			{
				flag++;//标志+1
				MaxHeapEdgeType temp = heap->edge[i];
				heap->edge[i] = heap->edge[i + 1];
				heap->edge[i + 1] = temp;
			}
		}

		//性价比大的上升
		for (int i = n - 1; i > 0; i--)
		{
			if (heap->edge[i].Price > heap->edge[i - 1].Price)
			{
				flag++;//标志+1
				MaxHeapEdgeType temp = heap->edge[i];
				heap->edge[i] = heap->edge[i - 1];
				heap->edge[i - 1] = temp;
			}
		}
		
	}
}

void  PrintfChangeLink(MaxHeapType* heap, int i)
{
	MaxHeapEdgeType edge = heap->edge[i];

	if (edge.LayerNUmChange == 3)
	{
		printf("<%3d->%3d->%3d>\n", edge.No, edge.path[0], edge.End_NO);
	}
	else if (edge.LayerNUmChange == 4)
	{
		printf("<%3d->%3d->%3d->%3d>\n", edge.No, edge.path[0], edge.path[1], edge.End_NO);
	}
	else if (edge.LayerNUmChange == 5)
	{
		printf("<%3d->%3d->%3d->%3d->%3d>\n", 
			edge.No, edge.path[0], edge.path[1], edge.path[2], edge.End_NO);
	}
	else
	{// = 2
		printf("\n");
	}
}
void OutPrintMaxHeap(MaxHeapType* heap)
{
	int n = heap->size;
	static index = 0;
	for (int i=0; i < n; i++)
	{
		MaxHeapEdgeType edge = heap->edge[i];
		//printf("边%d<->%d的权重是%d，性价比是%f\n", edge.No, edge.End_NO, edge.Weight, edge.Price);
		printf("%2d <%3d-%3d>:[%2d %2d] [%2d %2d] %2.2f    ", ++index, edge.No, edge.End_NO, edge.Weight, edge.LayerNum, edge.WeightChange, edge.LayerNUmChange, edge.Price);
		PrintfChangeLink(heap, i);
	}
}


void TestMaxHeap()
{
	//测试一个新建的堆
	MaxHeapType* heap = MaxHeapInit(10);
	//向堆中插入边
	printf("向堆插入边");
	for (int i = 0; i < 20; i++)
	{
		MaxHeapEdgeType* edge =(MaxHeapEdgeType*)malloc(sizeof(MaxHeapEdgeType));
		edge->No = i;
		edge->End_NO = i + 1;
		if (i > 10)
		{
			edge->Weight = (int)((20-i)/ 2);
			edge->Price = (i / 2.0);
		}
		else
		{
			edge->Price = (int)((20 - i) / 2);
			edge->Weight = (i / 2.0);
		}
		printf("边%d<->%d的权重是%d，性价比是%f\n", edge->No, edge->End_NO, edge->Weight, edge->Price);
		MaxHeapAdd(heap, edge);
	}
	printf("输出插入排序后的结果\n");
	OutPrintMaxHeap(heap);
	//按性价比排序
	printf("输出性价比排序后的结果\n");
	MaxHeapSortByPrice(heap);
	OutPrintMaxHeap(heap);

	
}


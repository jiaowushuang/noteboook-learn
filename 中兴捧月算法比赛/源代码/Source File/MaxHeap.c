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
		printf("���������ڴ�ʧ��");
		getchar();
		exit(0);
	}
	if (!(q->edge = (MaxHeapEdgeType*)malloc(MaxNum * sizeof(MaxHeapEdgeType))))
	{
		printf("�������ѱ������ڴ�ʧ��");
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
	//���Ѱ�Ȩ������ʱ����ȡȨ����С�ı�Ȩ��
	if (heap->size == 0)
		return -1;
	else
		return heap->edge[heap->size - 1].Weight;
}

void MaxHeapInsertByWeight(MaxHeapType* heap,MaxHeapEdgeType* edge)
{
	//�Ա߰�Ȩ��������в���
	int n = heap->size;
	int i = 0;
	for (i = 0; i < n; i++)
	{
		//���ұ�Ӧ�ò����λ��
		if (heap->edge[i].Weight < edge->Weight)
			break;
	}
	//i����ıߴӺ���ǰ���κ���һλ
	for (int j = n - 1; j >= i; j--)
		heap->edge[j + 1] = heap->edge[j];
	//��edge���뵽��Ӧ��λ��
	heap->edge[i] = *edge;
	//��δ��ʱ,size+1
	if (heap->size < heap->MaxNum)
		heap->size++;

}

int MaxHeapAdd(MaxHeapType* heap, MaxHeapEdgeType* edge)
{
	if (!MaxHeapIsFull(heap)||GetLastMaxHeapElement(heap) < edge->Weight)
		//��δ��ʱ���߱ߵ�Ȩ�ش��ڵ�ǰȨ����С�ߵ�Ȩ��ʱ
	{
		MaxHeapInsertByWeight(heap, edge);
		return 1;
	}
	return 0;
}

void MaxHeapSortByPrice(MaxHeapType* heap)
{
	//ð������:�Ӵ�С
	int flag = 1;
	int n = heap->size;
	while (flag)
	{
		flag = 0;//��־��λ

		//�Լ۱�С�ı��½�
		for (int i = 0; i < n - 1; i++)
		{
			if (heap->edge[i].Price < heap->edge[i + 1].Price)
			{
				flag++;//��־+1
				MaxHeapEdgeType temp = heap->edge[i];
				heap->edge[i] = heap->edge[i + 1];
				heap->edge[i + 1] = temp;
			}
		}

		//�Լ۱ȴ������
		for (int i = n - 1; i > 0; i--)
		{
			if (heap->edge[i].Price > heap->edge[i - 1].Price)
			{
				flag++;//��־+1
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
		//printf("��%d<->%d��Ȩ����%d���Լ۱���%f\n", edge.No, edge.End_NO, edge.Weight, edge.Price);
		printf("%2d <%3d-%3d>:[%2d %2d] [%2d %2d] %2.2f    ", ++index, edge.No, edge.End_NO, edge.Weight, edge.LayerNum, edge.WeightChange, edge.LayerNUmChange, edge.Price);
		PrintfChangeLink(heap, i);
	}
}


void TestMaxHeap()
{
	//����һ���½��Ķ�
	MaxHeapType* heap = MaxHeapInit(10);
	//����в����
	printf("��Ѳ����");
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
		printf("��%d<->%d��Ȩ����%d���Լ۱���%f\n", edge->No, edge->End_NO, edge->Weight, edge->Price);
		MaxHeapAdd(heap, edge);
	}
	printf("������������Ľ��\n");
	OutPrintMaxHeap(heap);
	//���Լ۱�����
	printf("����Լ۱������Ľ��\n");
	MaxHeapSortByPrice(heap);
	OutPrintMaxHeap(heap);

	
}


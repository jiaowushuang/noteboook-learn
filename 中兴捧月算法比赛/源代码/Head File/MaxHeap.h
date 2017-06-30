#pragma once

typedef struct
{//����Ԫ��-��
	int No;//�������
	int End_NO;//���յ���

	int Weight;//��Ȩ��
	int LayerNum;//����

	int WeightChange;//·���޸ĺ�ߵ�Ȩ��
	int LayerNUmChange;//·���޸ĺ������

	float Price;//�Լ۱�=(WeightChange-Weight)/(LayerNumChange-LayerNum)

	int path[3];//�޸ĺ��·�� a-b ==> a-c-d-e-b

}MaxHeapEdgeType;

typedef struct
{//����
	int MaxNum;//�������
	int size;//��ǰ����
	MaxHeapEdgeType* edge;//������
}MaxHeapType;

MaxHeapType* MaxHeapInit(int MaxNum);
int MaxHeapIsFull(MaxHeapType* heap);

int MaxHeapAdd(MaxHeapType* heap,MaxHeapEdgeType* edge);//�������ͼ���һ����
void MaxHeapSortByPrice(MaxHeapType* heap);

void TestMaxHeap();
void OutPrintMaxHeap(MaxHeapType* heap);
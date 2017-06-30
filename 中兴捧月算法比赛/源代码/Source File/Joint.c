#include <stdio.h>
#include <MustNode2Path.h>
#include <Storage.h>
#include <InsertList.h>
#include "Joint.h"
#include "2opt.h"
#include "DeleteMust.h"
void ClearUsedFlag(int val)
{
	mustNodeLink.usedNum = mustNodeLink.ListLen;
	for (int i = 0; i <= mustNodeLink.ListLen; i++)
	{
		mustNodeLink.ListData[i].IsUsed = val;
	}
	mustEdgeLink.usedNum = mustEdgeLink.ListLen;
	for (int i = 0; i <= mustEdgeLink.ListLen; i++)
	{
		mustEdgeLink.ListData[i].IsUsed = val;
	}
}
void ClearInsertCost()
{
	for (int i = 0; i <= mustNodeLink.ListLen; i++)
	{
		mustNodeLink.ListData[i].InsertAddCost = -1;
	}
	mustEdgeLink.usedNum = mustEdgeLink.ListLen;
	for (int i = 0; i <= mustEdgeLink.ListLen; i++)
	{
		mustEdgeLink.ListData[i].InsertAddCost = -1;
	}
}
void InitInsertLink()
{//��ʼ���ɲ�����
	ListDataType ele;//�ɲ������ڵ�Ԫ��
	InsertLink = SeqListInit();//���ٿɲ������洢�ռ�
	ele.startNo = AdjGraf.StartNode;/* ����ͷ�ڵ��β�ڵ� */
	ele.endNo = AdjGraf.EndNode;
	ele.flag = 1;
	SeqListAdd(InsertLink, ele);
}
int AddEdge(int edge_index)
{//����һ���� no1 --> no2
	int no1 = mustEdgeLink.ListData[edge_index].no1;
	int no2 = mustEdgeLink.ListData[edge_index].no2;
	int start, end;
	int num1 = 0, num2 = 0, num3 = 0, val = MAX_VALUE;
	int pos = 1, dir = 1;
	int i, j;
	ListDataType ele;
	for (i = 1; i <= InsertLink->ListLen; i++)
	{//Ѱ�����Ų���ڵ�
		if (InsertLink->ListData[i].flag == 1)
		{//����ɲ���
			start = InsertLink->ListData[i].startNo;
			end = InsertLink->ListData[i].endNo;
			/*ԭ·��������������������������������*/
			/* start --> end */
			num1 = pPathMatrix[getPos(start)*gatherNode.num + getPos(end)].LayerNum;
			/* start --> no1 --> no2 --> end */
			num2 = pPathMatrix[getPos(start)*gatherNode.num + getPos(no1)].LayerNum +
				pPathMatrix[getPos(no2)*gatherNode.num + getPos(end)].LayerNum;
			/* start --> no2 --> no1 --> end */
			num3 = pPathMatrix[getPos(start)*gatherNode.num + getPos(no2)].LayerNum + pPathMatrix[getPos(no1)*gatherNode.num + getPos(end)].LayerNum;
			if (num2 < num3)
			{//�������/* start --> no1 --> no2 --> end */
				if ((num2 - num1) < val)
				{//Ѱ�����Ų���ڵ�
					val = num2 - num1;
					pos = i; dir = 1;
				}
			}
			else
			{//�������/* start --> no2 --> no1 --> end */
				if ((num3 - num1) < val)
				{//Ѱ�����Ų���ڵ�
					val = num3 - num1;
					pos = i; dir = 2;
				}
			}
		}/*end if*/
		if (val < 0)
		{
			val = 0;
		}
	}
	mustEdgeLink.ListData[edge_index].InsertAddCost = val;
	if (dir == 1)
	{//�������/* start --> no1 --> no2 --> end */
		start = InsertLink->ListData[pos].startNo;
		end = InsertLink->ListData[pos].endNo;
		ele.startNo = start;
		ele.endNo = no1;
		ele.flag = 1;
		SeqListInsert(InsertLink, pos, ele);
		ele.startNo = no1;
		ele.endNo = no2;
		ele.flag = 0;//�ؾ��ߣ����ɽ��в���
		SeqListInsert(InsertLink, pos + 1, ele);
		ele.startNo = no2;
		ele.endNo = end;
		ele.flag = 1;
		SeqListInsert(InsertLink, pos + 2, ele);
		
	}
	else
	{//�������/* start --> no2 --> no1 --> end */
		start = InsertLink->ListData[pos].startNo;
		end = InsertLink->ListData[pos].endNo;
		ele.startNo = start;
		ele.endNo = no2;
		ele.flag = 1;
		SeqListInsert(InsertLink, pos, ele);
		ele.startNo = no2;
		ele.endNo = no1;
		ele.flag = 0;//�ؾ��ߣ����ɽ��в���
		SeqListInsert(InsertLink, pos + 1, ele);
		ele.startNo = no1;
		ele.endNo = end;
		ele.flag = 1;
		SeqListInsert(InsertLink, pos + 2, ele);
	}
	SeqListDelete(InsertLink, pos + 3);
	return dir;
}
void AddNode(int no_index)
{//����ڵ�
	int no = mustNodeLink.ListData[no_index].no;
	int start, end;
	int num1 = 0, num2 = 0, num3 = 0, val = MAX_VALUE;
	int pos = 1, dir = 1;
	int i, j;
	ListDataType ele;
	for (i = 1; i <= InsertLink->ListLen; i++)
	{//Ѱ�����Ų����
		if (InsertLink->ListData[i].flag == 1)
		{
			start = InsertLink->ListData[i].startNo;
			end = InsertLink->ListData[i].endNo;
			/* ԭ·�������������·������ */
			/* start --> end */
			num1 = pPathMatrix[getPos(start)*gatherNode.num + getPos(end)].LayerNum;
			/* start --> no--> end */
			num2 = pPathMatrix[getPos(start)*gatherNode.num + getPos(no)].LayerNum +
				pPathMatrix[getPos(no)*gatherNode.num + getPos(end)].LayerNum;

			if ((num2 - num1) < val)
			{
				val = num2 - num1;
				pos = i;
			}
		}
	}
	mustNodeLink.ListData[no_index].InsertAddCost = val - 1;
	/* start --> no--> end */
	ele.startNo = InsertLink->ListData[pos].startNo;
	ele.endNo = no;
	ele.flag = 1;
	SeqListInsert(InsertLink, pos, ele);
	ele.startNo = no;
	ele.endNo = InsertLink->ListData[pos + 1].endNo;
	ele.flag = 1;
	SeqListInsert(InsertLink, pos + 1, ele);

	SeqListDelete(InsertLink, pos + 2);  /* start --> end */
}
int getDis(int no, EdgeLinkDataType edge)
{//��õ㵽�ߵ���С����
	int value1, value2;
	value1 = pPathMatrix[getPos(no)*gatherNode.num + getPos(edge.no1)].LayerNum;
	value2 = pPathMatrix[getPos(no)*gatherNode.num + getPos(edge.no2)].LayerNum;
	return value1 < value2 ? value1 : value2;
}
void InsertMustPass()
{//����һ���߻���һ���ڵ㡪���ڽ�+��ʡ���뷨
	int temp;
	int head, tail, no;
	
	int FlagInsertDir = 0; /* no = ͷ / β�ڵ���βԪ��*/
	head = AdjGraf.StartNode;
	tail = AdjGraf.EndNode;

	ClearUsedFlag(0); /* ���ʹ�ñ�� */
	ClearInsertCost(); /* �������ɱ�*/
	//while ((mustEdgeLink.ListLen > 0) || (mustNodeLink.ListLen > 0))
	while ((mustEdgeLink.usedNum > 0) || (mustNodeLink.usedNum > 0))
	{
		int minVal = MAX_VALUE;//������С����
		int addFlag, addIndex;

		if (FlagInsertDir == 0)	no = head;
		else	                no = tail;

		for (int i = 1; i <= mustNodeLink.ListLen; i++)
		{//��ȡ�ڵ� no �� �ؾ��ڵ�ĵ���С�����͸ñؾ��ڵ���
			if (mustNodeLink.ListData[i].IsUsed == 0)
			{
				temp = pPathMatrix[getPos(no)*gatherNode.num
					+ getPos(mustNodeLink.ListData[i].no)].LayerNum;
				if (temp < minVal)
				{
					minVal = temp;
					addFlag = 0; addIndex = i;//����ؾ��ڵ�i
				}
			}
		}
		for (int i = 1; i <= mustEdgeLink.ListLen; i++)
		{//��ȡ�ڵ� no �� �ؾ��ߵĵ���С�����͸ñؾ��߱��
			if (mustEdgeLink.ListData[i].IsUsed == 0)
			{
				temp = temp = getDis(no, mustEdgeLink.ListData[i]);
				if (temp < minVal)
				{
					minVal = temp;
					addFlag = 1; addIndex = i;//����ؾ��ڵ�i
				}
			}
		}
		if (addFlag == 0)
		{//����ڵ�
			AddNode(addIndex);
			no = mustNodeLink.ListData[addIndex].no;
			//NodeListDelete(&mustNodeLink, addIndex);/* ɾ���ýڵ� */
			mustNodeLink.ListData[addIndex].IsUsed = 1; mustNodeLink.usedNum--;
		}
		else if (addFlag == 1)
		{//�����
			int dir;//�ߵĲ��뷽��
			dir = AddEdge(addIndex);
			if (FlagInsertDir == 0)
			{/* ��ǰѡ��Ϊͷ�� */
				if (dir == 1)
				{//�������
					no = mustEdgeLink.ListData[addIndex].no2;
				}
				else
				{//�������
					no = mustEdgeLink.ListData[addIndex].no1;
				}
			}
			else
			{/* ��ǰѡ��Ϊβ�� */
				if (dir == 1)
				{//�������
					no = mustEdgeLink.ListData[addIndex].no1;
				}
				else
				{//�������
					no = mustEdgeLink.ListData[addIndex].no2;
				}
			}
			//EdgeListDelete(&mustEdgeLink, addIndex);/* ɾ���ñ� */
			mustEdgeLink.ListData[addIndex].IsUsed = 1; mustEdgeLink.usedNum--;
		}
		if (FlagInsertDir == 0)/* ��ǰѡ��Ϊͷ�� */
		{//����ͷ�����βԪ��
			head = no;
			FlagInsertDir = 1; /* ���Ĳ��뷽�� */
		}
		else/* ��ǰѡ��Ϊβ�� */
		{//����β�ڵ���βԪ��
			tail = no;
			FlagInsertDir = 0; /* ���Ĳ��뷽�� */
		}
	}/* end while()*/
}
void PrintfInsertLink()
{//��ӡ�ɲ�����
	printf("�ɲ�������");
	for (int i = 1; i <= InsertLink->ListLen; i++)
	{
		printf(" %d-%d[%d]", InsertLink->ListData[i].startNo, 
			InsertLink->ListData[i].endNo, InsertLink->ListData[i].flag);
	}
	printf("\n");
}
void getAllMustNodeLink()
{//�ɲ�������>���бؾ��ڵ��˳�򼯺�
	AllMustNodeOrderGather.num = InsertLink->ListLen;
	AllMustNodeOrderGather.p = (int *)malloc(AllMustNodeOrderGather.num * sizeof(int));
	int j = 0;
	for (int i = 1; i <= InsertLink->ListLen; i++)
	{
		if (InsertLink->ListData[i].startNo != InsertLink->ListData[i].endNo)
		{
			AllMustNodeOrderGather.p[j++] = InsertLink->ListData[i].startNo;
		}
	}
	AllMustNodeOrderGather.p[j++] = AdjGraf.EndNode;
	AllMustNodeOrderGather.num = j;
}
void PrintfOrderGather()
{//��ӡ���бؾ��ڵ�˳�򼯺�
	printf("�����бؾ��ڵ�˳�򼯺� = %d��", AllMustNodeOrderGather.num);
	for (int i = 0; i < AllMustNodeOrderGather.num; i++)
	{
		printf(" %d ", AllMustNodeOrderGather.p[i]);
	}
	printf("\n");
}
void PrintOnePath(int startNo, int endNo, gatherNodeType AllMustNodeOrderGather)
{
	int pathNum, layout; /* ·����  ���� */ 
	/* ���� = ·���� *������ + 1) ��Ԫ��Ϊ ����  */
	int selectedPath;
	int cost = MAX_VALUE;
	int* link;
	int loc_startNo = getPos(startNo); /* ��ȡ�ڵ������бؾ��ڵ㼯�ϵ��±�λ�� */
	int loc_endNo = getPos(endNo);

	if (loc_startNo < loc_endNo)
	{//�����ӡ
		pathNum = pPathMatrix[loc_startNo*gatherNode.num + loc_endNo].PathNum;
		layout = pPathMatrix[loc_startNo*gatherNode.num + loc_endNo].LayerNum;
		link = pPathMatrix[loc_startNo*gatherNode.num + loc_endNo].link;
		for (int i = 0; i < pathNum; i++)
		{//ѡ�񻨷���С��·��
			if (link[i*(layout + 1) + 0 ] < cost)
			{
				selectedPath = i;
				cost = link[i*(layout + 1) + 0];
			}
		}
		for (int i = 1; i < layout; i++)
		{// s -> 1 -> 2 -> t ����ӡ endNo
			printf("%d-->", link[selectedPath*(layout + 1) + i]);
		}
	}
	else
	{//�����ӡ
		pathNum = pPathMatrix[loc_endNo*gatherNode.num + loc_startNo].PathNum;
		layout = pPathMatrix[loc_endNo*gatherNode.num + loc_startNo].LayerNum;
		link = pPathMatrix[loc_endNo*gatherNode.num + loc_startNo].link;
		for (int i = 0; i < pathNum; i++)
		{//ѡ�񻨷���С��·��
			if (link[i*(layout + 1) + 0] < cost)
			{
				selectedPath = i;
				cost = link[i*(layout + 1) + 0];
			}
		}
		for (int i = layout; i > 1; i--)
		{// cost  t -> 2 -> 1 -> s
			printf("%d-->", link[selectedPath*(layout + 1) + i]);
		}
	}
}
void PrintPathes(gatherNodeType AllMustNodeOrderGather)
{
	int no, end_no;
	printf("·����");
	for (int i = 1; i < AllMustNodeOrderGather.num; i++)
	{
		no = AllMustNodeOrderGather.p[i - 1];
		end_no = AllMustNodeOrderGather.p[i];

		PrintOnePath(no, end_no, AllMustNodeOrderGather);
	}
	printf("%d\n", end_no);//��ӡ��ֹ�ڵ�
}
void Joint()
{
	InitInsertLink(); /* ��ʼ���ɲ����� */

	InsertMustPass(); /* ��� + ��ʡ ���� */

	//PrintfInsertLink();/* ��ӡ�ɲ����� */
	getAllMustNodeLink();/* ��ò���ӡ���бؾ��ڵ�˳���� */
	//PrintfOrderGather();
	deleteGather_1();
	//printf("\n�ڽ�+��ʡ ������ ��������·������ = %d\n", optEffect(AllMustNodeOrderGather));
	//PrintPathes(AllMustNodeOrderGather);

	opt();
	deleteGather_1();
}
void PrintfMustNode_Edge()
{
	printf("���ؾ������㣡������ ");
	for (int i = 1; i <= mustNodeLink.ListLen; i++)
	{
		printf("[%3d %d %d]", mustNodeLink.ListData[i].no, mustNodeLink.ListData[i].InsertAddCost, mustNodeLink.ListData[i].DeleteSubCost);
	}
	printf("\n");
	printf("���ؾ��߱߱߱ߣ��������� ");
	for (int i = 1; i <= mustEdgeLink.ListLen; i++)
	{
		printf("[%3d-%3d  %d %d]", mustEdgeLink.ListData[i].no1, mustEdgeLink.ListData[i].no2, mustEdgeLink.ListData[i].InsertAddCost, mustEdgeLink.ListData[i].DeleteSubCost);
	}
	printf("\n");

	getEdgeSum();
	getNodeSum();
	EdgeLinkSortByCost();
	NodeListSortByCost();

	printf("���ؾ������㣡������ ");
	for (int i = 1; i <= mustNodeLink.ListLen; i++)
	{
		printf("[%3d  %d %d %d]", mustNodeLink.ListData[i].no, 
			mustNodeLink.ListData[i].InsertAddCost, mustNodeLink.ListData[i].DeleteSubCost,
			mustNodeLink.ListData[i].costSum);
	}
	printf("\n");
	printf("���ؾ��߱߱߱ߣ��������� ");
	for (int i = 1; i <= mustEdgeLink.ListLen; i++)
	{
		printf("[%3d-%3d  %d %d %d]", mustEdgeLink.ListData[i].no1, mustEdgeLink.ListData[i].no2, mustEdgeLink.ListData[i].InsertAddCost, mustEdgeLink.ListData[i].DeleteSubCost,
			mustEdgeLink.ListData[i].costSum);
	}
	printf("\n");
}
void deleteGather_1()
{
	int i;
	for (i = 0; i < (AllMustNodeOrderGather.num - 1); i++)
	{
		if (AllMustNodeOrderGather.p[i] == AllMustNodeOrderGather.p[i + 1])
		{
			AllMustNodeOrderGather.num--;
			for (int j = i + 1; j < AllMustNodeOrderGather.num; j++)
			{
				AllMustNodeOrderGather.p[j] = AllMustNodeOrderGather.p[j + 1];
			}
		}
	}
}
void deleteGather_2()
{
	int i;
	for (i = 0; i < (AllMustNodeOrderGather_2.num - 1); i++)
	{
		if (AllMustNodeOrderGather_2.p[i] == AllMustNodeOrderGather_2.p[i + 1])
		{
			AllMustNodeOrderGather_2.num--;
			for (int j = i + 1; j < AllMustNodeOrderGather_2.num; j++)
			{
				AllMustNodeOrderGather_2.p[j] = AllMustNodeOrderGather_2.p[j + 1];
			}
		}
	}
}
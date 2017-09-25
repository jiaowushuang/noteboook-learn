#include <stdio.h>
#include "PathInit.h"
#include "Storage.h"
#include "MustNode2Path.h"
#include <malloc.h>
#include "DeleteMust.h"
#include "cost.h"
#include "Joint.h"

//extern gatherNodeType AllMustNodeOrderGather; //���б��뾭���Ľڵ�˳�򼯺�
DeleteLinkType DeleteLink;
void ClearDeleteCost()
{
	for (int i = 0; i <= mustNodeLink.ListLen; i++)
	{
		mustNodeLink.ListData[i].DeleteSubCost = 0;
	}
	mustEdgeLink.usedNum = mustEdgeLink.ListLen;
	for (int i = 0; i <= mustEdgeLink.ListLen; i++)
	{
		mustEdgeLink.ListData[i].DeleteSubCost = 0;
	}
}
void setNodeLinkSubCost(int no, int subCost)
{
	for (int i = 1; i <= mustNodeLink.ListLen; i++)
	{
		if (no == mustNodeLink.ListData[i].no)
		{
			mustNodeLink.ListData[i].DeleteSubCost = subCost;
			break;
		}
	}
}
void setEdgeLinkSubCost(int no1, int no2, int subCost)
{
	for (int i = 1; i <= mustEdgeLink.ListLen; i++)
	{
		if ((no1 == mustEdgeLink.ListData[i].no1) && (no2 == mustEdgeLink.ListData[i].no2) )
		{
			mustEdgeLink.ListData[i].DeleteSubCost = subCost;
			break;
		}
		else if ((no1 == mustEdgeLink.ListData[i].no2) && (no2 == mustEdgeLink.ListData[i].no1))
		{
			mustEdgeLink.ListData[i].DeleteSubCost = subCost;
			break;
		}
	}
}
void getDeleteLink()
{//�ɲ�������>���е�˳��ڵ㼯��
	DeleteLink.num = InsertLink->ListLen;
	DeleteLink.p = (DeleteLinkEle *)malloc(DeleteLink.num * sizeof(DeleteLinkEle));
	int j = 0;
	DeleteLink.p[0].lFlag = 0;
	for (int i = 1; i <= InsertLink->ListLen; i++)
	{/*�ɲ����������������Ա�*/
		if (InsertLink->ListData[i].startNo != InsertLink->ListData[i].endNo)
		{
			DeleteLink.p[j].no = InsertLink->ListData[i].startNo;
			if (InsertLink->ListData[i].flag == 0)
			{/*InsertLink->ListData[i]startNo -- endNo ֮�䲻�ɲ��룬�Ǳؾ���*/
				DeleteLink.p[j].rFlag = 1;/*��Ԫ������һ��Ԫ���Ǳؾ���*/
				DeleteLink.p[j + 1].lFlag = 1;
			}
			else
			{
				DeleteLink.p[j].rFlag = 0;/*��Ԫ������һ��Ԫ�ز��Ǳؾ���*/
				DeleteLink.p[j + 1].lFlag = 0;
			}
			DeleteLink.p[j].subNum = -1;
			j++;
		}
	}
	DeleteLink.p[j].no = AdjGraf.EndNode;/* ���������ֹ�ڵ� */
	DeleteLink.p[j].rFlag = 0;
	DeleteLink.p[j].subNum = -1;
	DeleteLink.num = j + 1;
}
void PrintfDeleteLink()
{//��ӡ���бؾ��ڵ�˳�򼯺�
	printf("�����бؾ��ڵ�˳�򼯺�ɾ���� %d��", DeleteLink.num);
	for (int i = 0; i < DeleteLink.num; i++)
	{
		printf(" %d(%2d)[%d %d] ", DeleteLink.p[i].no, DeleteLink.p[i].subNum,
			DeleteLink.p[i].lFlag, DeleteLink.p[i].rFlag);
	}
	printf("\n");
}
void InitNodeCutHop()
{
	int DeleteSubCost = 0;
	int last, now, next;
	for (int i = 1; i < DeleteLink.num - 1; i++)
	{
		if ((DeleteLink.p[i].lFlag == 0) && (DeleteLink.p[i].rFlag == 0))
		{/*�Ǳؾ���*/
			last = DeleteLink.p[i-1].no; now = DeleteLink.p[i].no; next = DeleteLink.p[i+1].no;
			DeleteSubCost =
				pPathMatrix[getPos(last)*gatherNode.num + getPos(now )].LayerNum +
				pPathMatrix[getPos(now )*gatherNode.num + getPos(next)].LayerNum - 1 -
				pPathMatrix[getPos(last)*gatherNode.num + getPos(next)].LayerNum ;
			DeleteLink.p[i].subNum = DeleteSubCost;
			setNodeLinkSubCost(now, DeleteSubCost);
		}
	}
}
void InitEdgeCutHop()
{
	int DeleteSubCost = 0;
	int last, no1, no2, next;

	if (DeleteLink.p[0].rFlag == 1)
	{
		no1 = DeleteLink.p[0].no; no2 = DeleteLink.p[1].no;
		if (DeleteLink.p[1].rFlag == 0)
		{
			next = DeleteLink.p[2].no;
			DeleteSubCost =
				1 +
				pPathMatrix[getPos(no2)*gatherNode.num + getPos(next)].LayerNum -
				pPathMatrix[getPos(no1)*gatherNode.num + getPos(next)].LayerNum;
			DeleteLink.p[0].subNum = DeleteSubCost;
			setEdgeLinkSubCost(no1, no2, DeleteSubCost);
		}
		else if (DeleteLink.p[1].rFlag == 1)
		{
			DeleteLink.p[0].subNum = 0;
			setEdgeLinkSubCost(no1, no2, 0);
		}
	}
	for (int i = 1; i < DeleteLink.num - 1; i++)
	{
		if (DeleteLink.p[i].rFlag == 1)
		{/*�Ǳؾ���*/
			no1 = DeleteLink.p[i].no; no2 = DeleteLink.p[i + 1].no;
			if ( (DeleteLink.p[i].lFlag ==0) && (DeleteLink.p[i+1].rFlag == 0) )
			{/*������*/
				last = DeleteLink.p[i - 1].no;
				next = DeleteLink.p[i + 2].no;
				DeleteSubCost =
					pPathMatrix[getPos(last)*gatherNode.num + getPos(no1)].LayerNum +
					pPathMatrix[getPos(no2)*gatherNode.num + getPos(next)].LayerNum -
					pPathMatrix[getPos(last)*gatherNode.num + getPos(next)].LayerNum;
				DeleteLink.p[i].subNum = DeleteSubCost;
				setEdgeLinkSubCost(no1, no2, DeleteSubCost);
			}
			else if ((DeleteLink.p[i].lFlag == 1) && (DeleteLink.p[i + 1].rFlag == 0))
			{
				next = DeleteLink.p[i + 2].no;
				DeleteSubCost =
					1 +
					pPathMatrix[getPos(no2)*gatherNode.num + getPos(next)].LayerNum -
					pPathMatrix[getPos(no1)*gatherNode.num + getPos(next)].LayerNum;
				DeleteLink.p[i].subNum = DeleteSubCost;
				setEdgeLinkSubCost(no1, no2, DeleteSubCost);
			}
			else if ((DeleteLink.p[i].lFlag == 0) && (DeleteLink.p[i + 1].rFlag == 1))
			{
				last = DeleteLink.p[i - 1].no;
				DeleteSubCost =
					pPathMatrix[getPos(last)*gatherNode.num + getPos(no1)].LayerNum +
					1 -
					pPathMatrix[getPos(last)*gatherNode.num + getPos(no2)].LayerNum;
				DeleteLink.p[i].subNum = DeleteSubCost;
				setEdgeLinkSubCost(no1, no2, DeleteSubCost);
			}
			else if ((DeleteLink.p[i].lFlag == 1) && (DeleteLink.p[i + 1].rFlag == 1))
			{
				DeleteLink.p[i].subNum = 0;
				setEdgeLinkSubCost(no1, no2, 0);
			}
		}
	}
}
void DeleteOneNode()
{

}
void DeleteMust()
{
	ClearDeleteCost();
	getDeleteLink();   /*��ʼ��ɾ����*/

	InitNodeCutHop();
	InitEdgeCutHop();
	//PrintfDeleteLink();/*��ӡɾ����*/

	getEdgeSum();
	getNodeSum();
	EdgeLinkSortByCost();
	NodeListSortByCost();
	//PrintfMustNode_Edge();
}
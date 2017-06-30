#include <stdio.h>
#include "Storage.h"

EdgeLinkType *EdgeListInit()
{//��ʼ��˳������ؾ�����
	EdgeLinkType *p;
	if (p = (EdgeLinkType *)malloc(sizeof(EdgeLinkType)))
	{
		p->ListLen = 0; //����˳�����Ϊ0
		return p;
	}
	return NULL;
}
int EdgeListLength(EdgeLinkType *SL)
{//����˳����Ԫ������ 
	return (SL->ListLen);
}
int EdgeListAdd(EdgeLinkType *SL, EdgeLinkDataType data)
{//����Ԫ�ص�˳���β��
	if (SL->ListLen >= MAXSIZE)  //˳������� 
	{
		printf("�ؾ���������˳�����������������ӽ���ˣ�\n");
		return 0;
	}
	SL->ListData[++SL->ListLen] = data;
	return 1;
}
int EdgeListInsert(EdgeLinkType *SL, int n, EdgeLinkDataType data)
{
	int i;
	if (SL->ListLen >= MAXSIZE)   //˳����������ѳ���������� 
	{
		printf("�ؾ���������˳������������ܲ�����!\n");
		return 0;             //����0��ʾ���벻�ɹ� 
	}
	if (n<1 || n>SL->ListLen)  //��������Ų���ȷ
	{
		printf("�ؾ�������������Ԫ����Ŵ��󣬲��ܲ���Ԫ�أ�\n");
		return 0;              //����0����ʾ���벻�ɹ� 
	}
	for (i = SL->ListLen; i >= n; i--)  //��˳����е���������ƶ� 
		SL->ListData[i + 1] = SL->ListData[i];
	SL->ListData[n] = data;        //������ 
	SL->ListLen++;               //˳�������������1 
	return 1;                   //���سɹ�����  
}
int EdgeListDelete(EdgeLinkType *SL, int n)
{//ɾ��˳����е�����Ԫ�� 
	int i;
	if (n<1 || n>SL->ListLen)  //ɾ��Ԫ����Ų���ȷ
	{
		printf("�ؾ���������ɾ�������Ŵ��󣬲���ɾ����㣡\n");
		return 0;              //����0����ʾɾ�����ɹ� 
	}
	for (i = n; i<SL->ListLen; i++)  //��˳����е�������ǰ�ƶ� 
		SL->ListData[i] = SL->ListData[i + 1];
	SL->ListLen--;               //˳���Ԫ��������1 
	return 1;                   //���سɹ�ɾ��  
}
void getEdgeSum()
{
	for (int i = 1; i <= mustEdgeLink.ListLen; i++)
	{
		mustEdgeLink.ListData[i].costSum =
			mustEdgeLink.ListData[i].InsertAddCost + mustEdgeLink.ListData[i].DeleteSubCost;
	}
}
void EdgeLinkSortByCost()
{
	int flag = 1;
	while (flag)
	{
		flag = 0;
		for (int i = 1; i <= mustEdgeLink.ListLen - 1; i++)
		{
			if (mustEdgeLink.ListData[i].costSum < mustEdgeLink.ListData[i + 1].costSum)
			{
				flag++;
				EdgeLinkDataType temp = mustEdgeLink.ListData[i];
				mustEdgeLink.ListData[i] = mustEdgeLink.ListData[i + 1];
				mustEdgeLink.ListData[i + 1] = temp;
			}
		}
	}
}
NodeLinkType *NodeListInit()
{//��ʼ��˳������ؾ�����
	NodeLinkType *p;
	if (p = (NodeLinkType *)malloc(sizeof(NodeLinkType)))
	{
		p->ListLen = 0;     //����˳�����Ϊ0
		return p;
	}
	return NULL;
}
int NodeListLength(NodeLinkType *SL)
{//����˳����Ԫ������ 
	return (SL->ListLen);
}
int NodeListAdd(NodeLinkType *SL, NodeLinkDataType data)
{//����Ԫ�ص�˳���β��
	if (SL->ListLen >= MAXSIZE)
	{
		printf("�ؾ���������˳�����������������ӽ���ˣ�\n");
		return 0;
	}
	SL->ListData[++SL->ListLen] = data;
	return 1;
}
int NodeListInsert(NodeLinkType *SL, int n, NodeLinkDataType data)
{
	int i;
	if (SL->ListLen >= MAXSIZE)   //˳����������ѳ���������� 
	{
		printf("�ؾ���������˳������������ܲ�����!\n");
		return 0;             //����0��ʾ���벻�ɹ� 
	}
	if (n<1 || n>SL->ListLen )  //��������Ų���ȷ
	{
		printf("�ؾ�������������Ԫ����Ŵ��󣬲��ܲ���Ԫ�أ�\n");
		return 0;              //����0����ʾ���벻�ɹ� 
	}
	for (i = SL->ListLen; i >= n; i--)  //��˳����е���������ƶ� 
		SL->ListData[i + 1] = SL->ListData[i];
	SL->ListData[n] = data;        //������ 
	SL->ListLen++;               //˳�������������1 
	return 1;                   //���سɹ�����  
}
int NodeListDelete(NodeLinkType *SL, int n)
{//ɾ��˳����е�����Ԫ�� 
	int i;
	if (n<1 || n>SL->ListLen)  //ɾ��Ԫ����Ų���ȷ
	{
		printf("�ؾ���������ɾ�������Ŵ��󣬲���ɾ����㣡\n");
		return 0;              //����0����ʾɾ�����ɹ� 
	}
	for (i = n; i<SL->ListLen; i++)  //��˳����е�������ǰ�ƶ� 
		SL->ListData[i] = SL->ListData[i + 1];
	SL->ListLen--;               //˳���Ԫ��������1 
	return 1;                   //���سɹ�ɾ��  
}
int getNodeListElePos(NodeLinkType *SL, NodeLinkDataType data)
{//���Ԫ�������Ա��е�λ��
	int i;
	for (i = 1; i <= SL->ListLen; i++)
	{
		if (data.no == SL->ListData[i].no)
			return i;
	}
	return 0;//δ�ҵ�������
}
void getNodeSum()
{
	for (int i = 1; i <= mustNodeLink.ListLen; i++)
	{
		mustNodeLink.ListData[i].costSum =
			mustNodeLink.ListData[i].DeleteSubCost + mustNodeLink.ListData[i].InsertAddCost;
	}
}
void NodeListSortByCost()
{
	int flag = 1;
	while (flag)
	{
		flag = 0;
		for (int i = 1; i <= mustNodeLink.ListLen - 1; i++)
		{
			if (mustNodeLink.ListData[i].costSum < mustNodeLink.ListData[i + 1].costSum)
			{
				flag++;
				NodeLinkDataType temp = mustNodeLink.ListData[i];
				mustNodeLink.ListData[i] = mustNodeLink.ListData[i + 1];
				mustNodeLink.ListData[i + 1] = temp;
			}
		}

		//for (int i = mustNodeLink.ListLen; i > 1; i--)
		//{
		//	if (mustNodeLink.ListData[i].costSum > mustNodeLink.ListData[i - 1].costSum)
		//	{
		//		flag++;
		//		NodeLinkDataType temp = mustNodeLink.ListData[i];
		//		mustNodeLink.ListData[i] = mustNodeLink.ListData[i - 1];
		//		mustNodeLink.ListData[i - 1] = temp;
		//	}
		//}
	}
}
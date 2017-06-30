#pragma once
//�ؾ�����
//�ؾ��ڵ���
#define MAXSIZE 400  //�������Ա����󳤶�

typedef struct
{//�ؾ�����Ԫ����������
	int no1;
	int no2;
	int costSum;
	int InsertAddCost;/*����ʱ���ӵĳɱ�*/
	int DeleteSubCost;/*ɾ��ʱ��С�ĳɱ�*/
	int IsUsed;/* �Ƿ��Ѿ�ʹ�ù� */
}EdgeLinkDataType;
typedef struct
{//�ؾ�����˳���ṹ��
	EdgeLinkDataType  ListData[MAXSIZE + 1]; 
	int				  sum;
	int			      ListLen;/*Ԫ���ܸ���*/
	int               usedNum;
	int               endIndex;
}EdgeLinkType;

typedef struct
{
	int no;
	int costSum;
	int InsertAddCost;/*����ʱ���ӵĳɱ�*/
	int DeleteSubCost;/*ɾ��ʱ��С�ĳɱ�*/
	int IsUsed;/* �Ƿ��Ѿ�ʹ�ù� */
}NodeLinkDataType;
typedef struct
{//�ؾ�����˳���ṹ��
	NodeLinkDataType  ListData[MAXSIZE + 1];  //�ڵ���Ԫ����������
	int				  sum;
	int	              ListLen;
	int               usedNum;
	int               endIndex;
}NodeLinkType;

EdgeLinkType *EdgeListInit();
int EdgeListLength(EdgeLinkType *SL);
int EdgeListAdd(EdgeLinkType *SL, EdgeLinkDataType data);
int EdgeListInsert(EdgeLinkType *SL, int n, EdgeLinkDataType data);
int EdgeListDelete(EdgeLinkType *SL, int n);
void EdgeLinkSortByCost();
void getEdgeSum();
NodeLinkType *NodeListInit();
int NodeListLength(NodeLinkType *SL);
int NodeListAdd(NodeLinkType *SL, NodeLinkDataType data);
int NodeListInsert(NodeLinkType *SL, int n, NodeLinkDataType data);
int NodeListDelete(NodeLinkType *SL, int n);
int getNodeListElePos(NodeLinkType *SL, NodeLinkDataType data);
void NodeListSortByCost();
void getNodeSum();
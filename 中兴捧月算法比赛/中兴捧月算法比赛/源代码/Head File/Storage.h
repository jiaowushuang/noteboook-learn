#pragma once
#include "link.h"
#include <InsertList.h>
#define VERTEX_MAX  500      //ͼ����󶥵���   
#define MAX_VALUE   32767  //0x7FFF ���ֵ(����Ϊһ���������) 
#define FilePath "E:\\ZTE/TestData/test1.txt"  //�����ļ�·��

typedef struct {  //������Ϣ
	int  No;    //����ı��/ID�� 0,1,2,3......(��洢λ�ö�Ӧ)
	// MatrixG->verteies[No].No = No; AdjG->VNode[No].V_data.No = No;
	int  vType; //��������
}VertexType;
typedef struct
{
	int weight;  //��Ȩֵ
	int eType;   //������
}EDGE_Info;

typedef struct EdgeNodeType {
	int End_No;         //�ú�/���յ��Ӧ�Ķ�����
	EDGE_Info E_data;   //�ߵ�������Ϣ����Ȩֵ+����
	struct EdgeNodeType *nextEdge;
}EdgeNodeType;
typedef struct PreNodeType {
	int pre_No;  //ǰ���ڵ��
	struct PreNodeType *nextPre;
}PreNodeType;
typedef struct {
	VertexType V_data;      //����������Ϣ��������ID+��������
	PreNodeType *firstPre; 
	EdgeNodeType *firstEdge;
}VertexNodeType;
typedef struct {
	VertexNodeType VNode[VERTEX_MAX];  //��ڵ�--��������
	int isTrav[VERTEX_MAX]; //������־ 
	int VertexNum;			//�������� 
	int EdgeNum;			//������ 
	int StartNode, EndNode; //��ʼ�ڵ㡢��ֹ�ڵ�
	int MustNodeNum, MustEdgeNum, NoPassingEdgeNum; //�ؾ��ڵ������ؾ�����
	int MaxHop;             //��ֵ���������
	int GraphType;			//ͼ������(0:����ͼ��1:����ͼ)  
}AdjListGraph;

typedef struct
{//���бؾ��㼯��=��ʼ�ڵ�+��ֹ�ڵ�+�ؾ��ڵ�+�ؾ��߽ڵ�
	int *p;
	int num;
}gatherNodeType;
typedef struct
{
	int LayerNum;  //��С����
	int PathNum;   //·����
	int minCostIndex; //��ͬ��������С����·���±�
	int minCost;
	int *link;     // = path[PathNum][LayerNum+1]
				   /*        0    1  2    3  4    LayerNum
				   path[0] cost0, s, N1, N2, N3, ... t;
				   path[1] cost1, s, N1, N2, N3, ... t;
				   */
}path2Node;

extern AdjListGraph AdjGraf;       //�ڽӱ�
extern EdgeLinkType mustEdgeLink;  //�ؾ�����//�ؾ��ڵ���
extern NodeLinkType mustNodeLink;  //�ؾ��ڵ���
extern gatherNodeType gatherNode;  //���бؾ��ڵ㼯��
extern gatherNodeType AllMustNodeOrderGather; //���б��뾭���Ľڵ�˳�򼯺�
extern gatherNodeType AllMustNodeOrderGather_2;
extern path2Node *pPathMatrix;     //�ؾ��ڵ�֮���·������
extern SeqListType *InsertLink;    /* ����ɲ����� */

void CreateAdjList(AdjListGraph *G);
void DeleteRepeatMustNode(AdjListGraph* G);
void DeleteNoPassingEdge(int no, int end_no, AdjListGraph *G);
void OutAdjList(AdjListGraph *G);
void SetMustEdge(AdjListGraph *G);

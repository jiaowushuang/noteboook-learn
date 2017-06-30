#include <stdio.h>
#include "Storage.h"
/*�����ļ�˵��
ͼ������ ������� �ߵĸ���
��1��ʼ�ڵ� ��1��ֹ�ڵ� Ȩֵ
��2��ʼ�ڵ� ��2��ֹ�ڵ� Ȩֵ
��...���߽�ͼ��
�ؾ��ڵ���� �ؾ��߸���
��ʼ�ڵ� ��ֹ�ڵ�
�ؾ��ڵ�1,2,3...
�ؾ���1
�ؾ���2
...
*/

AdjListGraph AdjGraf;       //�ڽӱ�
EdgeLinkType mustEdgeLink;  //�ؾ��ڵ���
NodeLinkType mustNodeLink;  //�ؾ�����
gatherNodeType gatherNode;  //���б��뾭���Ľڵ㼯��
gatherNodeType AllMustNodeOrderGather; //���б��뾭���Ľڵ�˳�򼯺�
gatherNodeType AllMustNodeOrderGather_2;
path2Node *pPathMatrix;     //�ؾ��ڵ�֮���·������
SeqListType *InsertLink;    /* ����ɲ����� */

extern char buf[1024];
void CreateAdjList(AdjListGraph *G)
{//���ļ�����ͼ�����ڽӱ�
	FILE *fp;
	int error;
	int start, end, weight;
	int i, j;

	EdgeNodeType *pointEdgeNode;//�ڽӱ������ָ��
	EdgeLinkDataType edge; //�ؾ�����Ԫ����������
	NodeLinkDataType node; //�ؾ�����Ԫ����������

	for (i = 0; i < VERTEX_MAX; i++)
	{//Ϊ�ڵ��ţ�����ʼֵ
		G->VNode[i].V_data.No = i;     
		G->VNode[i].V_data.vType = 0;  //�ڵ����ͣ��ؾ��ڵ㡢�ؾ��߽ڵ㡢��ͨ�ڵ㣩
		G->VNode[i].firstPre = NULL;   //��һ��ǰ���ڵ㣬ѹ����ģʱ�õ�
		G->VNode[i].firstEdge = NULL;  
	}
	//if (error = fopen_s(&fp, FilePath, "r"))
	if (error = fopen_s(&fp, buf, "r"))
	{
		printf("���ļ����� error = %d\r\n", error);
		getchar();
		printf("�س��˳���ǰ����");
		getchar();
		exit(0);
	}
	fscanf_s(fp, "%d %d %d %d", &G->GraphType, &G->VertexNum, &G->EdgeNum, &G->MaxHop);
	/*printf("ͼ������= %d  �������= %d  �ߵĸ���= %d\n",
								G->GraphType, G->VertexNum, G->EdgeNum);*/

	for (i = 0; i < G->EdgeNum; i++)
	{//���ߣ���ʼ�㡢��ֹ�㡢Ȩֵ����ͼ
		fscanf_s(fp, "%d %d %d", &start, &end, &weight);
		//printf("%d--->%d Ȩֵ=%d\n", start, end, weight);
		pointEdgeNode = (EdgeNodeType *)malloc(sizeof(EdgeNodeType));
		pointEdgeNode->End_No = end;
		pointEdgeNode->E_data.weight = weight;
		pointEdgeNode->E_data.eType = 0;//�ߵ����ͣ��ؾ��ߡ��Ǳؾ��ߣ�
		pointEdgeNode->nextEdge = G->VNode[start].firstEdge;
		G->VNode[start].firstEdge = pointEdgeNode;
		/* ���ӹ�ϵ A --> A-D --> A-C --> A-B
		A --> NULL
		A --> A-B   A-B --> NULL
		A --> A-C   A-C --> A-B   A-B --> NULL
		A --> A-D   A-D --> A-C   A-C --> A-B   A-B --> NULL
		*/
		if (G->GraphType == 0)
		{//����ͼ
			pointEdgeNode = (EdgeNodeType *)malloc(sizeof(EdgeNodeType));
			pointEdgeNode->End_No = start;
			pointEdgeNode->E_data.weight = weight;
			pointEdgeNode->E_data.eType = 0;//�ߵ����ͣ��ؾ��ߡ��Ǳؾ��ߣ�
			pointEdgeNode->nextEdge = G->VNode[end].firstEdge;
			G->VNode[end].firstEdge = pointEdgeNode;
		}
	}

	fscanf_s(fp, "%d %d %d", &G->MustNodeNum, &G->MustEdgeNum, &G->NoPassingEdgeNum);
	//printf("�ؾ��ڵ���= %d  �ؾ�����= %d\n", G->MustNodeNum, G->MustEdgeNum);
	fscanf_s(fp, "%d %d", &G->StartNode, &G->EndNode);
	//printf("��ʼ�ڵ�= %d  ��ֹ�ڵ�= %d\n", G->StartNode, G->EndNode);

	for (i = 0; i < G->MustNodeNum; i++)
	{//�����ؾ�����
		fscanf_s(fp, "%d", &node.no);
		node.DeleteSubCost = 0; node.InsertAddCost = 0; node.IsUsed = 0;
		NodeListAdd(&mustNodeLink, node);
		G->VNode[node.no].V_data.vType = 1; /* ���ýڵ����� 1 �ؾ���*/
	}
	for (i = 0; i < G->MustEdgeNum; i++)
	{//�����ؾ�����
		fscanf_s(fp, "%d %d", &edge.no1, &edge.no2);
		edge.DeleteSubCost = 0; edge.InsertAddCost = 0; edge.IsUsed = 0;
		EdgeListAdd(&mustEdgeLink, edge);
	}

	DeleteRepeatMustNode(G); /* ɾ���ڱؾ������Ѿ����ֵ� �ظ��ؾ��ڵ� */

	for (i = 0; i < G->NoPassingEdgeNum; i++)
	{//���ڽӱ���ɾ����ֹͨ��·��
		fscanf_s(fp, "%d %d", &start,  &end);
		DeleteNoPassingEdge(start, end, G);//����ɾ��
		DeleteNoPassingEdge(end, start, G);//����ɾ��
	}
	
	fclose(fp);

	SetMustEdge(G);/* ���ñؾ�·����־ */
}
void DeleteRepeatMustNode(AdjListGraph* G)
{//ɾ���ڱؾ��������Ѿ����ڵıؾ��ڵ�����Ԫ��
//�ؾ��ڵ��Ǳؾ��ߵĽڵ�֮һ
	NodeLinkDataType node;
	EdgeLinkDataType p;
	for (int i = 1; i <= G->MustEdgeNum; i++)
	{//�����ؾ���
		p = mustEdgeLink.ListData[i];
		for (int j = 1; j <= mustNodeLink.ListLen; j++)
		{//�����ؾ��ڵ�
			node = mustNodeLink.ListData[j];
			if (node.no == p.no1 || node.no == p.no2)
			{
				NodeListDelete(&mustNodeLink, j);
				//j--;  /* j-- ��ֹ�ظ��ڵ������ break �ؾ��ڵ����ڲ�Ԫ�����ظ� */
				break;
			}
		}
	}
	G->MustNodeNum = mustNodeLink.ListLen;
}
void DeleteNoPassingEdge(int no, int end_no, AdjListGraph *G)
{//���ڽӱ���ɾ�������Ծ����ı�
	EdgeNodeType *p;
	p = G->VNode[no].firstEdge;
	if (p->End_No == end_no)
	{
		G->VNode[no].firstEdge = p->nextEdge;
	}
	else
	{
		EdgeNodeType* q = p;
		p = p->nextEdge;
		while (p != NULL)
		{
			if (p->End_No == end_no)
			{
				q->nextEdge = p->nextEdge;
				break;
			}
			q = p;
			p = p->nextEdge;
		}
	}
}
void SetMustEdge(AdjListGraph *G)
{/* ���ڽӱ� ���ñؾ��� ��־ */
	EdgeNodeType *p = NULL;
	int no1, no2;
	for (int i = 1; i <= mustEdgeLink.ListLen; i++)
	{//�����ؾ��ڵ���
		no1 = mustEdgeLink.ListData[i].no1;
		no2 = mustEdgeLink.ListData[i].no2;
		p = G->VNode[no1].firstEdge; 
		while ( p != NULL )
		{/* ���� no1 -> no2 Ϊ�ؾ��� */
			if (p->End_No == no2)
			{
				p->E_data.eType = 1;
				break;
			}
			else
				p = p->nextEdge;
		}

		p = G->VNode[no2].firstEdge;
		while (p != NULL)
		{/* ���� no2 -> no1 Ϊ�ؾ��� */
			if (p->End_No == no1)
			{
				p->E_data.eType = 1;
				break;
			}
			else
				p = p->nextEdge;
		}
	}
}
void OutAdjList(AdjListGraph *G)
{
	int i;
	EdgeNodeType *pointEdgeNode;

	printf("��ͼ������= %d  �������= %d  �ߵĸ���= %d��\n", G->GraphType, G->VertexNum, G->EdgeNum);

	//for (i = 0; i < G->VertexNum; i++)
	//{//��ӡ�ڽӱ�
	//	printf("���� %2d ", G->VNode[i].V_data.No);
	//	pointEdgeNode = G->VNode[i].firstEdge;
	//	while (pointEdgeNode)
	//	{
	//		printf(" -> %2d[%2d -%d] ", pointEdgeNode->End_No, 
	//			pointEdgeNode->E_data.weight, pointEdgeNode->E_data.eType);
	//		pointEdgeNode = pointEdgeNode->nextEdge;
	//	}
	//	printf("\n");
	//}

	printf("����ʼ�ڵ�= %d  ��ֹ�ڵ�= %d��\n", G->StartNode, G->EndNode);
	printf("���ؾ��ڵ���= %d  �ؾ�����= %d  ��ֹͨ�б��� = %d ��ֵ = %d��\n", G->MustNodeNum, 
		G->MustEdgeNum, G->NoPassingEdgeNum, G->MaxHop);

	printf("���ؾ��㡿 ");
	for (i = 1; i <= mustNodeLink.ListLen; i++)
	{
		printf(" %d ", mustNodeLink.ListData[i].no);
	}
	printf("\n");
	printf("���ؾ��ߡ� ");
	for (i = 1; i <= mustEdgeLink.ListLen; i++)
	{
		printf(" %d-%d ", mustEdgeLink.ListData[i].no1, mustEdgeLink.ListData[i].no2);
	}
	printf("\n");
}
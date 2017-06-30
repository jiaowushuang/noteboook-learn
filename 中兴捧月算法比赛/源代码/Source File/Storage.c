#include <stdio.h>
#include "Storage.h"
/*测试文件说明
图的类型 顶点个数 边的个数
边1起始节点 边1终止节点 权值
边2起始节点 边2终止节点 权值
（...按边建图）
必经节点个数 必经边个数
起始节点 终止节点
必经节点1,2,3...
必经边1
必经边2
...
*/

AdjListGraph AdjGraf;       //邻接表
EdgeLinkType mustEdgeLink;  //必经节点链
NodeLinkType mustNodeLink;  //必经边链
gatherNodeType gatherNode;  //所有必须经过的节点集合
gatherNodeType AllMustNodeOrderGather; //所有必须经过的节点顺序集合
gatherNodeType AllMustNodeOrderGather_2;
path2Node *pPathMatrix;     //必经节点之间的路径矩阵
SeqListType *InsertLink;    /* 定义可插入链 */

extern char buf[1024];
void CreateAdjList(AdjListGraph *G)
{//读文件创建图——邻接表
	FILE *fp;
	int error;
	int start, end, weight;
	int i, j;

	EdgeNodeType *pointEdgeNode;//邻接表边类型指针
	EdgeLinkDataType edge; //必经边链元素数据类型
	NodeLinkDataType node; //必经点链元素数据类型

	for (i = 0; i < VERTEX_MAX; i++)
	{//为节点标号，赋初始值
		G->VNode[i].V_data.No = i;     
		G->VNode[i].V_data.vType = 0;  //节点类型（必经节点、必经边节点、普通节点）
		G->VNode[i].firstPre = NULL;   //第一个前驱节点，压缩规模时用到
		G->VNode[i].firstEdge = NULL;  
	}
	//if (error = fopen_s(&fp, FilePath, "r"))
	if (error = fopen_s(&fp, buf, "r"))
	{
		printf("打开文件错误 error = %d\r\n", error);
		getchar();
		printf("回车退出当前测试");
		getchar();
		exit(0);
	}
	fscanf_s(fp, "%d %d %d %d", &G->GraphType, &G->VertexNum, &G->EdgeNum, &G->MaxHop);
	/*printf("图的种类= %d  顶点个数= %d  边的个数= %d\n",
								G->GraphType, G->VertexNum, G->EdgeNum);*/

	for (i = 0; i < G->EdgeNum; i++)
	{//按边（起始点、终止点、权值）建图
		fscanf_s(fp, "%d %d %d", &start, &end, &weight);
		//printf("%d--->%d 权值=%d\n", start, end, weight);
		pointEdgeNode = (EdgeNodeType *)malloc(sizeof(EdgeNodeType));
		pointEdgeNode->End_No = end;
		pointEdgeNode->E_data.weight = weight;
		pointEdgeNode->E_data.eType = 0;//边的类型（必经边、非必经边）
		pointEdgeNode->nextEdge = G->VNode[start].firstEdge;
		G->VNode[start].firstEdge = pointEdgeNode;
		/* 链接关系 A --> A-D --> A-C --> A-B
		A --> NULL
		A --> A-B   A-B --> NULL
		A --> A-C   A-C --> A-B   A-B --> NULL
		A --> A-D   A-D --> A-C   A-C --> A-B   A-B --> NULL
		*/
		if (G->GraphType == 0)
		{//无向图
			pointEdgeNode = (EdgeNodeType *)malloc(sizeof(EdgeNodeType));
			pointEdgeNode->End_No = start;
			pointEdgeNode->E_data.weight = weight;
			pointEdgeNode->E_data.eType = 0;//边的类型（必经边、非必经边）
			pointEdgeNode->nextEdge = G->VNode[end].firstEdge;
			G->VNode[end].firstEdge = pointEdgeNode;
		}
	}

	fscanf_s(fp, "%d %d %d", &G->MustNodeNum, &G->MustEdgeNum, &G->NoPassingEdgeNum);
	//printf("必经节点数= %d  必经边数= %d\n", G->MustNodeNum, G->MustEdgeNum);
	fscanf_s(fp, "%d %d", &G->StartNode, &G->EndNode);
	//printf("起始节点= %d  终止节点= %d\n", G->StartNode, G->EndNode);

	for (i = 0; i < G->MustNodeNum; i++)
	{//创建必经点链
		fscanf_s(fp, "%d", &node.no);
		node.DeleteSubCost = 0; node.InsertAddCost = 0; node.IsUsed = 0;
		NodeListAdd(&mustNodeLink, node);
		G->VNode[node.no].V_data.vType = 1; /* 设置节点类型 1 必经点*/
	}
	for (i = 0; i < G->MustEdgeNum; i++)
	{//创建必经边链
		fscanf_s(fp, "%d %d", &edge.no1, &edge.no2);
		edge.DeleteSubCost = 0; edge.InsertAddCost = 0; edge.IsUsed = 0;
		EdgeListAdd(&mustEdgeLink, edge);
	}

	DeleteRepeatMustNode(G); /* 删除在必经边中已经出现的 重复必经节点 */

	for (i = 0; i < G->NoPassingEdgeNum; i++)
	{//在邻接表中删除禁止通行路径
		fscanf_s(fp, "%d %d", &start,  &end);
		DeleteNoPassingEdge(start, end, G);//正向删除
		DeleteNoPassingEdge(end, start, G);//反向删除
	}
	
	fclose(fp);

	SetMustEdge(G);/* 设置必经路径标志 */
}
void DeleteRepeatMustNode(AdjListGraph* G)
{//删除在必经边链中已经存在的必经节点链的元素
//必经节点是必经边的节点之一
	NodeLinkDataType node;
	EdgeLinkDataType p;
	for (int i = 1; i <= G->MustEdgeNum; i++)
	{//遍历必经边
		p = mustEdgeLink.ListData[i];
		for (int j = 1; j <= mustNodeLink.ListLen; j++)
		{//遍历必经节点
			node = mustNodeLink.ListData[j];
			if (node.no == p.no1 || node.no == p.no2)
			{
				NodeListDelete(&mustNodeLink, j);
				//j--;  /* j-- 防止重复节点情况， break 必经节点链内部元素无重复 */
				break;
			}
		}
	}
	G->MustNodeNum = mustNodeLink.ListLen;
}
void DeleteNoPassingEdge(int no, int end_no, AdjListGraph *G)
{//在邻接表中删除不可以经过的边
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
{/* 在邻接表 设置必经边 标志 */
	EdgeNodeType *p = NULL;
	int no1, no2;
	for (int i = 1; i <= mustEdgeLink.ListLen; i++)
	{//遍历必经节点链
		no1 = mustEdgeLink.ListData[i].no1;
		no2 = mustEdgeLink.ListData[i].no2;
		p = G->VNode[no1].firstEdge; 
		while ( p != NULL )
		{/* 设置 no1 -> no2 为必经边 */
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
		{/* 设置 no2 -> no1 为必经边 */
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

	printf("【图的种类= %d  顶点个数= %d  边的个数= %d】\n", G->GraphType, G->VertexNum, G->EdgeNum);

	//for (i = 0; i < G->VertexNum; i++)
	//{//打印邻接表
	//	printf("顶点 %2d ", G->VNode[i].V_data.No);
	//	pointEdgeNode = G->VNode[i].firstEdge;
	//	while (pointEdgeNode)
	//	{
	//		printf(" -> %2d[%2d -%d] ", pointEdgeNode->End_No, 
	//			pointEdgeNode->E_data.weight, pointEdgeNode->E_data.eType);
	//		pointEdgeNode = pointEdgeNode->nextEdge;
	//	}
	//	printf("\n");
	//}

	printf("【起始节点= %d  终止节点= %d】\n", G->StartNode, G->EndNode);
	printf("【必经节点数= %d  必经边数= %d  禁止通行边数 = %d 阈值 = %d】\n", G->MustNodeNum, 
		G->MustEdgeNum, G->NoPassingEdgeNum, G->MaxHop);

	printf("【必经点】 ");
	for (i = 1; i <= mustNodeLink.ListLen; i++)
	{
		printf(" %d ", mustNodeLink.ListData[i].no);
	}
	printf("\n");
	printf("【必经边】 ");
	for (i = 1; i <= mustEdgeLink.ListLen; i++)
	{
		printf(" %d-%d ", mustEdgeLink.ListData[i].no1, mustEdgeLink.ListData[i].no2);
	}
	printf("\n");
}
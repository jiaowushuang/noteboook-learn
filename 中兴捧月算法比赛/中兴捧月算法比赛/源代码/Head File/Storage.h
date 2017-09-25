#pragma once
#include "link.h"
#include <InsertList.h>
#define VERTEX_MAX  500      //图的最大顶点数   
#define MAX_VALUE   32767  //0x7FFF 最大值(可设为一个最大整数) 
#define FilePath "E:\\ZTE/TestData/test1.txt"  //测试文件路径

typedef struct {  //顶点信息
	int  No;    //顶点的编号/ID号 0,1,2,3......(与存储位置对应)
	// MatrixG->verteies[No].No = No; AdjG->VNode[No].V_data.No = No;
	int  vType; //顶点类型
}VertexType;
typedef struct
{
	int weight;  //边权值
	int eType;   //边类型
}EDGE_Info;

typedef struct EdgeNodeType {
	int End_No;         //该狐/边终点对应的顶点编号
	EDGE_Info E_data;   //边的所有信息——权值+类型
	struct EdgeNodeType *nextEdge;
}EdgeNodeType;
typedef struct PreNodeType {
	int pre_No;  //前驱节点号
	struct PreNodeType *nextPre;
}PreNodeType;
typedef struct {
	VertexType V_data;      //顶点所有信息——顶点ID+顶点类型
	PreNodeType *firstPre; 
	EdgeNodeType *firstEdge;
}VertexNodeType;
typedef struct {
	VertexNodeType VNode[VERTEX_MAX];  //表节点--顶点数组
	int isTrav[VERTEX_MAX]; //遍历标志 
	int VertexNum;			//顶点数量 
	int EdgeNum;			//边数量 
	int StartNode, EndNode; //起始节点、终止节点
	int MustNodeNum, MustEdgeNum, NoPassingEdgeNum; //必经节点数、必经边数
	int MaxHop;             //阈值，最大跳数
	int GraphType;			//图的类型(0:无向图，1:有向图)  
}AdjListGraph;

typedef struct
{//所有必经点集合=起始节点+终止节点+必经节点+必经边节点
	int *p;
	int num;
}gatherNodeType;
typedef struct
{
	int LayerNum;  //最小跳数
	int PathNum;   //路径数
	int minCostIndex; //相同跳数的最小费用路径下标
	int minCost;
	int *link;     // = path[PathNum][LayerNum+1]
				   /*        0    1  2    3  4    LayerNum
				   path[0] cost0, s, N1, N2, N3, ... t;
				   path[1] cost1, s, N1, N2, N3, ... t;
				   */
}path2Node;

extern AdjListGraph AdjGraf;       //邻接表
extern EdgeLinkType mustEdgeLink;  //必经边链//必经节点链
extern NodeLinkType mustNodeLink;  //必经节点链
extern gatherNodeType gatherNode;  //所有必经节点集合
extern gatherNodeType AllMustNodeOrderGather; //所有必须经过的节点顺序集合
extern gatherNodeType AllMustNodeOrderGather_2;
extern path2Node *pPathMatrix;     //必经节点之间的路径矩阵
extern SeqListType *InsertLink;    /* 定义可插入链 */

void CreateAdjList(AdjListGraph *G);
void DeleteRepeatMustNode(AdjListGraph* G);
void DeleteNoPassingEdge(int no, int end_no, AdjListGraph *G);
void OutAdjList(AdjListGraph *G);
void SetMustEdge(AdjListGraph *G);

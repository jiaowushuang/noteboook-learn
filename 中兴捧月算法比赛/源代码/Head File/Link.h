#pragma once
//必经边链
//必经节点链
#define MAXSIZE 400  //定义线性表的最大长度

typedef struct
{//必经边链元素数据类型
	int no1;
	int no2;
	int costSum;
	int InsertAddCost;/*插入时增加的成本*/
	int DeleteSubCost;/*删除时减小的成本*/
	int IsUsed;/* 是否已经使用过 */
}EdgeLinkDataType;
typedef struct
{//必经边链顺序表结构体
	EdgeLinkDataType  ListData[MAXSIZE + 1]; 
	int				  sum;
	int			      ListLen;/*元素总个数*/
	int               usedNum;
	int               endIndex;
}EdgeLinkType;

typedef struct
{
	int no;
	int costSum;
	int InsertAddCost;/*插入时增加的成本*/
	int DeleteSubCost;/*删除时减小的成本*/
	int IsUsed;/* 是否已经使用过 */
}NodeLinkDataType;
typedef struct
{//必经点链顺序表结构体
	NodeLinkDataType  ListData[MAXSIZE + 1];  //节点链元素数据类型
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
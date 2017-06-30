#pragma once

typedef struct {
	int no;    /* 节点编号 */
	int subNum;
	int lFlag; /* 与上一个节点是否构成必经边 */
	int rFlag; /* 与下一个节点是否构成必经边 */
			   // lFlag == 0 && rFlag == 0 必经节点 
}DeleteLinkEle;
typedef struct {
	DeleteLinkEle *p;
	int num;
}DeleteLinkType;

extern DeleteLinkType DeleteLink;
void setNodeLinkSubCost(int no, int subCost);
void getDeleteLink();
void PrintfDeleteLink();
void DeleteOneNode();
void DeleteMust();

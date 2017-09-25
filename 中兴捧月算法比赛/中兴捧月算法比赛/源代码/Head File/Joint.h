#pragma once
#include <InsertList.h>

void InitInsertLink();
int AddEdge(int edge_index);
void AddNode(int no_index);
void Joint();
int getDis(int no, EdgeLinkDataType edge);
void InsertMustPass();
void PrintfInsertLink();
void getAllMustNodeLink();
void PrintfOrderGather();
void PrintPathes(gatherNodeType AllMustNodeOrderGather);
void PrintOnePath(int no, int end_no, gatherNodeType AllMustNodeOrderGather);
void PrintfMustNode_Edge();
void deleteGather_1();
void deleteGather_2();

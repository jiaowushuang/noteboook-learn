#pragma once
#include "PathNodeSeqList.h"
#include "MaxHeap.h"

void PrintfPathNodeList();
void ListAndHeapInit(PathNodeType* list,MaxHeapType* heap);
void Test(int hop);
void CostOpt();
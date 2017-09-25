#pragma once
#include "Storage.h"

void PrintfPath(int s, int t);
void GrafIsTravClear(AdjListGraph *G);
void pathOut(int s, int t, AdjListGraph *G);
void pathSave(int s, int t, AdjListGraph *G);
int path(int s, int t, AdjListGraph *G);
void ClearAdjPre(AdjListGraph *G);
void InitGatherNode(AdjListGraph *G);
int getPos(int no);
void InitPathMatrix();
void PathMatrixLayer();
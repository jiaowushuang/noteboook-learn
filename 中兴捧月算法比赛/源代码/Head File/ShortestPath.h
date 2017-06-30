#pragma once
#include "storage.h"
typedef struct
{
	int LayerNum;
	int cost;
	int *link;
}DijkstraMatrix;

extern DijkstraMatrix *DijMatrix;

void InitDijMatrix();
void PrintfMinCostPath(int *tmpvertex, int *path, AdjListGraph *G, int v0);
void DijkstraHeap(AdjListGraph *G, int v0);
void DijSave(int *tmpvertex, int *path, AdjListGraph *G, int v0);
void DijkstraAdj(AdjListGraph *G, int v0);
void PrintfDijMatrix();
void PrintfDiffer();
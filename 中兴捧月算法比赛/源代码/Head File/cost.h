#pragma once
#include "MaxHeap.h"
int IsMustEdge(int no1, int no2, int *weight);
int getCost(int no1, int no2);
int Layer_3(int s, int t, int lastLayerMincost, int *link);
int Layer_4(int s, int t, int lastLayerMincost, int *link);
int Layer_5(int s, int t, int lastLayerMincost, int *link);
int Layer_n(int s, int t, int cost, int n);
float getCost_Layer(int no1, int no2, int weight, MaxHeapEdgeType *maxHeap);
void PrintfCostLayer(int cost, int *pre, int n);



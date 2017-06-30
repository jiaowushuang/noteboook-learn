#pragma once


typedef struct    //����˳���ṹ
{
	int  MaxNum;  //���ɾ����Ľڵ���
	int	 ListLen;    //˳����Ѵ�������� 
	int* ListData;  //����˳��������
}PathNodeType;

PathNodeType *PathNodeInit(int MaxNum);
int PathNodeLength(PathNodeType *SL);
int PathNodeAdd(PathNodeType *SL, int data);
int PathNodeInsert(PathNodeType *SL, int n, int data);
int PathNodeDelete(PathNodeType *SL, int n);
int *PathNodeFindByNum(PathNodeType *SL, int n);
int PathNodeFind(PathNodeType *SL, int no1, int no2);
#include "PathNodeSeqList.h"
#include <stdio.h>

PathNodeType *PathNodeInit(int MaxNum)
{//��ʼ��˳���
	PathNodeType *p;
	if (MaxNum <= 0)
	{
		printf("˳������ֵ���ò�����\n");
		getchar();
		exit(0);

	}
	if (!(p = (PathNodeType *)malloc(sizeof(PathNodeType)))) //�����ڴ� 
	{
		printf("����˳����ڴ�ʧ��\n");
		getchar();
		exit(0);
	}
	if (!(p->ListData = (int*)malloc(MaxNum * sizeof(int))))
	{
		printf("����˳���ڵ������ڴ�ʧ��\n");
		getchar();
		exit(0);

	}
	p->ListLen = 0;     //��ʼ��ʱ������˳�����Ϊ0
	p->MaxNum = MaxNum;
	return p;
}
int PathNodeLength(PathNodeType *SL)
{//����˳����Ԫ������ 
	return (SL->ListLen);
}
int PathNodeAdd(PathNodeType *SL, int data)
{//����Ԫ�ص�˳���β��
	if (SL->ListLen >= SL->MaxNum)  //˳������� 
	{
		printf("˳�����������������ӽ���ˣ�\n");
		return 0;
	}
	SL->ListData[++SL->ListLen] = data;
	return 1;
}
int PathNodeInsert(PathNodeType *SL, int n, int data)
{
	int i;
	if (SL->ListLen >= SL->MaxNum)   //˳����������ѳ���������� 
	{
		printf("˳������������ܲ�����!\n");
		return 0;             //����0��ʾ���벻�ɹ� 
	}
	if (n<1 || n>SL->ListLen)  //��������Ų���ȷ
	{
		printf("����Ԫ����Ŵ��󣬲��ܲ���Ԫ�أ�\n");
		return 0;              //����0����ʾ���벻�ɹ� 
	}
	for (i = SL->ListLen; i >= n; i--)  //��˳����е���������ƶ� 
		SL->ListData[i + 1] = SL->ListData[i];
	SL->ListData[n] = data;        //������ 
	SL->ListLen++;               //˳�������������1 
	return 1;                   //���سɹ�����  
}
int PathNodeDelete(PathNodeType *SL, int n)
{//ɾ��˳����е�����Ԫ�� 
	int i;
	if (n<1 || n>SL->ListLen)  //ɾ��Ԫ����Ų���ȷ
	{
		printf("ɾ�������Ŵ��󣬲���ɾ����㣡\n");
		return 0;              //����0����ʾɾ�����ɹ� 
	}
	for (i = n; i<SL->ListLen; i++)  //��˳����е�������ǰ�ƶ� 
		SL->ListData[i] = SL->ListData[i + 1];
	SL->ListLen--;               //˳���Ԫ��������1 
	return 1;                   //���سɹ�ɾ��  
}

//note:���ظ�Ԫ�����ڵ�ַ���ɶ����Ա��д�Ԫ�ؽ��ж�-д����
int *PathNodeFindByNum(PathNodeType *SL, int n)
{//������ŷ�������Ԫ��
	if (n<1 || n>SL->ListLen + 1)  //Ԫ����Ų���ȷ
	{
		printf("�����Ŵ��󣬲��ܷ��ؽ�㣡\n");
		return NULL;              //����0����ʾ���ɹ� 
	}
	return &(SL->ListData[n]);
}
int PathNodeFind(PathNodeType *SL, int no1, int no2)
{/* Ѱ��Ԫ����� */
	int i;
	for (i = 1; i <= SL->ListLen; i++)
		if (SL->ListData[i] == no1)  //����ҵ������� 
		{
			if (SL->ListData[i+1] == no2)
				return i;        //���ؽ����� 
		}
	return 0;  //��������û���ҵ����򷵻�0 
}
/* 
note:����0λ��Ϊ�գ�����Ȼ˳��1,2,3...����
note:���Ա�Ļ�����������
1-��ʼ��
2-��ȡ���Ա���/Ԫ�ظ���
3-���ӽڵ�
4-����ڵ�
5-ɾ���ڵ�
6-��ȡ���е�i��Ԫ�ء���/д
 -��ȡ���е�i��Ԫ�ء�ֻ��
7-�ؼ��ֲ�ѯ
8-��ȡi��ǰ��Ԫ��
9-��ȡi�ĺ��Ԫ��
10-�ÿձ�
11-�ͷű�
12-�жϱ��Ƿ�Ϊ��
note:Zhangximing 2017.3.27
*/

#include <stdio.h>
#include "InsertList.h"

SeqListType *SeqListInit() 
{//��ʼ��˳���
	SeqListType *p;
	if (p = (SeqListType *)malloc(sizeof(SeqListType))) //�����ڴ� 
	{
		p->ListLen = 0;     //��ʼ��ʱ������˳�����Ϊ0
		return p;
	}
	return NULL;
}
int SeqListLength(SeqListType *SL)
{//����˳����Ԫ������ 
	return (SL->ListLen);
}
int SeqListAdd(SeqListType *SL, ListDataType data)
{//����Ԫ�ص�˳���β��
	if (SL->ListLen >= MAXSIZE)  //˳������� 
	{
		printf("˳�����������������ӽ���ˣ�\n");
		return 0;
	}
	SL->ListData[++SL->ListLen] = data;
	return 1;
}
int SeqListInsert(SeqListType *SL, int n, ListDataType data)
{
	int i;
	if (SL->ListLen >= MAXSIZE)   //˳����������ѳ���������� 
	{
		printf("˳������������ܲ�����!\n");
		return 0;             //����0��ʾ���벻�ɹ� 
	}
	if (n<1 || n>SL->ListLen )  //��������Ų���ȷ
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
int SeqListDelete(SeqListType *SL, int n)
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
ListDataType *SeqListFindByNum(SeqListType *SL, int n)
{//������ŷ�������Ԫ��
	if (n<1 || n>SL->ListLen + 1)  //Ԫ����Ų���ȷ
	{
		printf("�����Ŵ��󣬲��ܷ��ؽ�㣡\n");
		return NULL;              //����0����ʾ���ɹ� 
	}
	return &(SL->ListData[n]);
}
//int SeqListFindByCont(SeqListType *SL, char *key)  //���ؼ��ֲ�ѯ��� 
//{
//	int i;
//	for (i = 1; i <= SL->ListLen; i++)
//		if (strcmp(SL->ListData[i].key, key) == 0)  //����ҵ������� 
//			return i;        //���ؽ����� 
//	return 0;  //��������û���ҵ����򷵻�0 
//}

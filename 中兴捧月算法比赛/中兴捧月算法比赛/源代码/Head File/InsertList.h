#pragma once
#define MAXSIZE 400  //�������Ա����󳤶�
typedef struct
{
	int startNo;
	int endNo;
	int flag; /* �Ƿ�ɲ����� */
}ListDataType;
typedef struct    //����˳���ṹ
{
	ListDataType  ListData[MAXSIZE + 1]; //����˳�������� 
	int			  ListLen;              //˳����Ѵ��� ������ 
}SeqListType;
SeqListType *SeqListInit(); //��ʼ��˳���
int SeqListLength(SeqListType *SL);  //����˳����Ԫ������ 
int SeqListAdd(SeqListType *SL, ListDataType data); //��˳��������Ԫ�� 
int SeqListInsert(SeqListType *SL, int n, ListDataType data); //��˳����в���Ԫ�� 
int SeqListDelete(SeqListType *SL, int n);  //ɾ��˳����еľ�Ԫ�� 
ListDataType *SeqListFindByNum(SeqListType *SL, int n);  //������ŷ���Ԫ��
//int SeqListFindByCont(SeqListType *SL, char *key); //���ؼ��ֲ��� 
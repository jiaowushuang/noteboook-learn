#pragma once

#define QUEUE_MAXSIZE (4000+1) //���е�������� 

typedef int SeqQueueDataType;

typedef struct
{
	SeqQueueDataType Data[QUEUE_MAXSIZE]; //������
	volatile int head; //��ͷָ��
	volatile int tail; //��βָ��
}SeqQueue; //���нṹ


//���в������� 
SeqQueue *SeqQueueInit(); //��ʼ��һ������   
int SeqQueueIsEmpty(SeqQueue *Q); //�ж϶����Ƿ��   
int SeqQueueIsFull(SeqQueue *Q);
void SeqQueueFree(SeqQueue *Q);
void SeqQueueClear(SeqQueue *Q);
int SeqQueueIn(SeqQueue *q, int n); //��һ��Ԫ�������   
int SeqQueueOut(SeqQueue *q, int *ch); //��һ��Ԫ�س�����  
void SeqQueueTest(void);
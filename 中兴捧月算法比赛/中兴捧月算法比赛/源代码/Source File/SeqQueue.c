#include <stdio.h>
#include "SeqQueue.h"

SeqQueue *SeqQueueInit()    //���г�ʼ��  
{
	SeqQueue *Q;
	if (Q = (SeqQueue *)malloc(sizeof(SeqQueue))) //��������ڴ�
	{
		Q->head = Q->tail = 0;
		return Q;
	}
	return NULL;
}
int SeqQueueIsEmpty(SeqQueue *Q)   //�ж϶����Ƿ��ѿգ����շ���1,���򷵻�0 
{
	return (Q->head == Q->tail);
}
int SeqQueueIsFull(SeqQueue *Q)
{
	return ( (Q->tail + 1) % QUEUE_MAXSIZE == Q->head);
}
void SeqQueueFree(SeqQueue *Q)
{
	if (Q)
		free(Q);
}
void SeqQueueClear(SeqQueue *Q)
{
	Q->head = Q->tail = 0;
}
int SeqQueueIn(SeqQueue *Q, int ch)   //����У��ɹ�����1��ʧ�ܷ���0   
{
	if (SeqQueueIsFull(Q)) //���������� 
	{
		printf("����������\r\n");
		return 0;  //���ش���;
	}
	Q->Data[Q->tail] = ch; //������ch����� 
	Q->tail = ( (Q->tail + 1) % QUEUE_MAXSIZE); //������βָ�� 
	return 1; //�ɹ�������1 
}
int SeqQueueOut(SeqQueue *Q, int *ch)   //������,�ɹ�����1������ch���ظ�Ԫ��ֵ��ʧ�ܷ���0  
{
	int temp;
	if (SeqQueueIsEmpty(Q)) //������Ϊ�� 
	{
		printf("����Ϊ��/r/n");
		return 0; //���ش��� 
	}
	temp = Q->Data[Q->head];
	*ch = Q->Data[Q->head]; //���ض���Ԫ�� 
	Q->head = ( (Q->head + 1) % QUEUE_MAXSIZE); //��������ָ�� 
	return 1; //�ɹ������У�����1   
}
void SeqQueueTest(void)
{
	SeqQueue *Q;
	SeqQueueDataType Value;
	printf("SeqQueue Test!\r\n");

	Q = SeqQueueInit();
	printf("Is SeqQueue empty %d \r\n", SeqQueueIsEmpty(Q));
	printf("Is SeqQueue full %d \r\n", SeqQueueIsFull(Q));

	SeqQueueIn(Q, 10);
	printf("Q->head = %d,  Q->tail = %d \r\n", Q->head, Q->tail);
	SeqQueueIn(Q, 11);
	printf("Q->head = %d,  Q->tail = %d \r\n", Q->head, Q->tail);

	if (SeqQueueOut(Q, &Value))
	{
		printf("Ԫ�س��� = [ %d ]\n", Value);
		printf("Q->head = %d,  Q->tail = %d \r\n", Q->head, Q->tail);
	}

	SeqQueueIn(Q, 12);
	printf("Q->head = %d,  Q->tail = %d \r\n", Q->head, Q->tail);
	SeqQueueIn(Q, 13);
	printf("Q->head = %d,  Q->tail = %d \r\n", Q->head, Q->tail);
	SeqQueueIn(Q, 147);
	printf("Q->head = %d,  Q->tail = %d \r\n", Q->head, Q->tail);

	printf("Is SeqQueue empty %d \r\n", SeqQueueIsEmpty(Q));
	printf("Is SeqQueue full %d \r\n", SeqQueueIsFull(Q));
	while (!SeqQueueIsEmpty(Q))
	{
		if (SeqQueueOut(Q, &Value))
		{
			printf("Ԫ�س��� = [ %d ]\n", Value);
			printf("Q->head = %d,  Q->tail = %d \r\n", Q->head, Q->tail);
		}
	}
	printf("Is SeqQueue empty %d \r\n", SeqQueueIsEmpty(Q));
	printf("Is SeqQueue full %d \r\n", SeqQueueIsFull(Q));

	getchar();
}
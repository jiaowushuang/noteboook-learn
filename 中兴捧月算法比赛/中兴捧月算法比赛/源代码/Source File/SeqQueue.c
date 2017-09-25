#include <stdio.h>
#include "SeqQueue.h"

SeqQueue *SeqQueueInit()    //队列初始化  
{
	SeqQueue *Q;
	if (Q = (SeqQueue *)malloc(sizeof(SeqQueue))) //申请队列内存
	{
		Q->head = Q->tail = 0;
		return Q;
	}
	return NULL;
}
int SeqQueueIsEmpty(SeqQueue *Q)   //判断队列是否已空，若空返回1,否则返回0 
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
int SeqQueueIn(SeqQueue *Q, int ch)   //入队列，成功返回1，失败返回0   
{
	if (SeqQueueIsFull(Q)) //若队列已满 
	{
		printf("队列已满！\r\n");
		return 0;  //返回错误;
	}
	Q->Data[Q->tail] = ch; //将数据ch入队列 
	Q->tail = ( (Q->tail + 1) % QUEUE_MAXSIZE); //调整队尾指针 
	return 1; //成功，返回1 
}
int SeqQueueOut(SeqQueue *Q, int *ch)   //出队列,成功返回1，并用ch返回该元素值，失败返回0  
{
	int temp;
	if (SeqQueueIsEmpty(Q)) //若队列为空 
	{
		printf("队列为空/r/n");
		return 0; //返回错误 
	}
	temp = Q->Data[Q->head];
	*ch = Q->Data[Q->head]; //返回队首元素 
	Q->head = ( (Q->head + 1) % QUEUE_MAXSIZE); //调整队首指针 
	return 1; //成功出队列，返回1   
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
		printf("元素出队 = [ %d ]\n", Value);
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
			printf("元素出队 = [ %d ]\n", Value);
			printf("Q->head = %d,  Q->tail = %d \r\n", Q->head, Q->tail);
		}
	}
	printf("Is SeqQueue empty %d \r\n", SeqQueueIsEmpty(Q));
	printf("Is SeqQueue full %d \r\n", SeqQueueIsFull(Q));

	getchar();
}
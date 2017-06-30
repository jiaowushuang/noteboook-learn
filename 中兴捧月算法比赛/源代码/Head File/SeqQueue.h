#pragma once

#define QUEUE_MAXSIZE (4000+1) //队列的最大容量 

typedef int SeqQueueDataType;

typedef struct
{
	SeqQueueDataType Data[QUEUE_MAXSIZE]; //数据域
	volatile int head; //队头指针
	volatile int tail; //队尾指针
}SeqQueue; //队列结构


//队列操作函数 
SeqQueue *SeqQueueInit(); //初始化一个队列   
int SeqQueueIsEmpty(SeqQueue *Q); //判断队列是否空   
int SeqQueueIsFull(SeqQueue *Q);
void SeqQueueFree(SeqQueue *Q);
void SeqQueueClear(SeqQueue *Q);
int SeqQueueIn(SeqQueue *q, int n); //将一个元素入队列   
int SeqQueueOut(SeqQueue *q, int *ch); //将一个元素出队列  
void SeqQueueTest(void);
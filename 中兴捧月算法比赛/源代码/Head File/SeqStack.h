#pragma once

#define SIZE 500

typedef int SeqStackDataType;

typedef struct stack
{
	SeqStackDataType data[SIZE]; //����Ԫ�� 
	int top; //ջ�� 
}SeqStack;

SeqStack *SeqStackInit();
int SeqStackIsEmpty(SeqStack *s);
void SeqStackFree(SeqStack *s);
void SeqStackClear(SeqStack *s);
int SeqStackIsFull(SeqStack *s);
int SeqStackPush(SeqStack *s, SeqStackDataType data);
int SeqStackPop(SeqStack *s, SeqStackDataType *val);
int SeqStackPeek(SeqStack *s, SeqStackDataType *val);

void SeqStackTest(void);
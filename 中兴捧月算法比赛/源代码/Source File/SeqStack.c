#include <stdio.h>
#include "SeqStack.h"

SeqStack *SeqStackInit()
{
	SeqStack *p;
	if (p = (SeqStack *)malloc(sizeof(SeqStack))) //申请栈内存 
	{
		p->top = -1; //设置栈顶为0 
		return p;//返回指向栈的指针 
	}
	return NULL;
}
int SeqStackIsEmpty(SeqStack *s) //判断栈是否为空 
{
	return(s->top == -1);
}
void SeqStackFree(SeqStack *s) //释放栈所占用空间 
{
	if (s)
		free(s);
}
void SeqStackClear(SeqStack *s)  //清空栈 
{
	s->top = -1;
}
int SeqStackIsFull(SeqStack *s) //判断栈是否已满
{
	return(s->top == (SIZE - 1) );
}
int SeqStackPush(SeqStack *s, SeqStackDataType data) //入栈操作 
{
	if (SeqStackIsFull(s) )
	{
		printf("栈溢出!\n");
		return 0;
	}
	s->data[++s->top] = data;//将元素入栈
	return 1;
}
int SeqStackPop(SeqStack *s, SeqStackDataType *val) //出栈操作 
{
	if (SeqStackIsEmpty(s) )
	{
		printf("栈为空！");
		return 0;
		//exit(0);
	}
	*val = s->data[s->top--];
	return 1;
}
int SeqStackPeek(SeqStack *s, SeqStackDataType *val) //读栈顶数据
{
	if (SeqStackIsEmpty(s))
	{
		printf("栈为空！");
		return 0;
		//exit(0);
	}
	*val = s->data[s->top];
	return 1;
}
void SeqStackTest(void)
{
	SeqStack *S;
	SeqStackDataType val;
	printf("SeqStack Test!\r\n");

	S = SeqStackInit();
	printf("Is SeqStack empty %d \r\n", SeqStackIsEmpty(S));
	printf("Is SeqStack full %d \r\n", SeqStackIsFull(S));
	SeqStackPush(S, 10);
	SeqStackPush(S, 11);
	SeqStackPush(S, 12);
	SeqStackPush(S, 13);
	SeqStackPush(S, 14);
	SeqStackPush(S, 15);
	SeqStackPush(S, 16);
	SeqStackPush(S, 17);
	SeqStackPush(S, 18);
	SeqStackPush(S, 19);
	SeqStackPush(S, 20);
	printf("Is SeqStack empty %d \r\n", SeqStackIsEmpty(S));
	printf("Is SeqStack full %d \r\n", SeqStackIsFull(S));
	while (!SeqStackIsEmpty(S))
	{
		if(SeqStackPop(S, &val))
			printf("元素出栈 = [ %d ]\n", val);
	}
	printf("Is SeqStack empty %d \r\n", SeqStackIsEmpty(S));
	printf("Is SeqStack full %d \r\n", SeqStackIsFull(S));

	getchar();
}
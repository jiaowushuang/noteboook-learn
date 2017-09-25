#include <stdio.h>
#include "SeqStack.h"

SeqStack *SeqStackInit()
{
	SeqStack *p;
	if (p = (SeqStack *)malloc(sizeof(SeqStack))) //����ջ�ڴ� 
	{
		p->top = -1; //����ջ��Ϊ0 
		return p;//����ָ��ջ��ָ�� 
	}
	return NULL;
}
int SeqStackIsEmpty(SeqStack *s) //�ж�ջ�Ƿ�Ϊ�� 
{
	return(s->top == -1);
}
void SeqStackFree(SeqStack *s) //�ͷ�ջ��ռ�ÿռ� 
{
	if (s)
		free(s);
}
void SeqStackClear(SeqStack *s)  //���ջ 
{
	s->top = -1;
}
int SeqStackIsFull(SeqStack *s) //�ж�ջ�Ƿ�����
{
	return(s->top == (SIZE - 1) );
}
int SeqStackPush(SeqStack *s, SeqStackDataType data) //��ջ���� 
{
	if (SeqStackIsFull(s) )
	{
		printf("ջ���!\n");
		return 0;
	}
	s->data[++s->top] = data;//��Ԫ����ջ
	return 1;
}
int SeqStackPop(SeqStack *s, SeqStackDataType *val) //��ջ���� 
{
	if (SeqStackIsEmpty(s) )
	{
		printf("ջΪ�գ�");
		return 0;
		//exit(0);
	}
	*val = s->data[s->top--];
	return 1;
}
int SeqStackPeek(SeqStack *s, SeqStackDataType *val) //��ջ������
{
	if (SeqStackIsEmpty(s))
	{
		printf("ջΪ�գ�");
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
			printf("Ԫ�س�ջ = [ %d ]\n", val);
	}
	printf("Is SeqStack empty %d \r\n", SeqStackIsEmpty(S));
	printf("Is SeqStack full %d \r\n", SeqStackIsFull(S));

	getchar();
}
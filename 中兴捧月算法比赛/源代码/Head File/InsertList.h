#pragma once
#define MAXSIZE 400  //定义线性表的最大长度
typedef struct
{
	int startNo;
	int endNo;
	int flag; /* 是否可插入标记 */
}ListDataType;
typedef struct    //定义顺序表结构
{
	ListDataType  ListData[MAXSIZE + 1]; //保存顺序表的数组 
	int			  ListLen;              //顺序表已存结点 的数量 
}SeqListType;
SeqListType *SeqListInit(); //初始化顺序表
int SeqListLength(SeqListType *SL);  //返回顺序表的元素数量 
int SeqListAdd(SeqListType *SL, ListDataType data); //向顺序表中添加元素 
int SeqListInsert(SeqListType *SL, int n, ListDataType data); //向顺序表中插入元素 
int SeqListDelete(SeqListType *SL, int n);  //删除顺序表中的据元素 
ListDataType *SeqListFindByNum(SeqListType *SL, int n);  //根据序号返回元素
//int SeqListFindByCont(SeqListType *SL, char *key); //按关键字查找 
#pragma once

typedef struct {
	int no;    /* �ڵ��� */
	int subNum;
	int lFlag; /* ����һ���ڵ��Ƿ񹹳ɱؾ��� */
	int rFlag; /* ����һ���ڵ��Ƿ񹹳ɱؾ��� */
			   // lFlag == 0 && rFlag == 0 �ؾ��ڵ� 
}DeleteLinkEle;
typedef struct {
	DeleteLinkEle *p;
	int num;
}DeleteLinkType;

extern DeleteLinkType DeleteLink;
void setNodeLinkSubCost(int no, int subCost);
void getDeleteLink();
void PrintfDeleteLink();
void DeleteOneNode();
void DeleteMust();

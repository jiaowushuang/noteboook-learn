#include <stdio.h>
#include "Storage.h"
#include "MustNode2Path.h"
#include <time.h>
#include <windows.h>
#include <stdio.h>
#include "PathInit.h"
#include "DeleteMust.h"
#include "out1.h"
#include<string.h>
clock_t start, finish;

char buf[1024];

void main(void)
{
	int i, j;
	int link[5];
	char fileName[21] = {'\0'};

	while (1)
	{
		getcwd(buf, sizeof(buf));
		printf("����������ļ���:");
		scanf_s("%s", fileName, 20);
		//printf("%s\n", fileName);
		strcat_s(buf, 1024, "/TestData/");
		strcat_s(buf, 1024, fileName);
		printf("��ǰ�����ļ�����·��: %s\n", buf);

		FILE *fp;
		int error;
		if (error = fopen_s(&fp, buf, "r"))
		{
			printf("���ļ����� error = %d\r\n", error);
			getchar();
			printf("���������ļ�Ӧ����TestData�ļ����У��ļ��б������ִ���ļ�����ͬĿ¼��\n");
		}
		else
		{//���ļ��ɹ�
			fclose(fp);
			break;
		}
	}

	CreateAdjList(&AdjGraf);
	OutAdjList(&AdjGraf);
	InitGatherNode(&AdjGraf); //��ʼ�����б��뾭���ڵ�
	InitPathMatrix();         //ѹ��ͼ����ʼ�����뾭���ڵ�֮���·��
	jlu_out();

	printf("���룺0-�˳�");
	while (1)
	{
		int index = 1;
		fflush(stdin);//������뻺���� 
		scanf_s("%d", &index);
		if (index == 0)
		{
			exit(0);
		}
	}
}
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
		printf("请输入测试文件名:");
		scanf_s("%s", fileName, 20);
		//printf("%s\n", fileName);
		strcat_s(buf, 1024, "/TestData/");
		strcat_s(buf, 1024, fileName);
		printf("当前测试文件完整路径: %s\n", buf);

		FILE *fp;
		int error;
		if (error = fopen_s(&fp, buf, "r"))
		{
			printf("打开文件错误 error = %d\r\n", error);
			getchar();
			printf("测试用例文件应放在TestData文件夹中，文件夹保持与可执行文件在相同目录下\n");
		}
		else
		{//打开文件成功
			fclose(fp);
			break;
		}
	}

	CreateAdjList(&AdjGraf);
	OutAdjList(&AdjGraf);
	InitGatherNode(&AdjGraf); //初始化所有必须经过节点
	InitPathMatrix();         //压缩图，初始化必须经过节点之间的路径
	jlu_out();

	printf("输入：0-退出");
	while (1)
	{
		int index = 1;
		fflush(stdin);//清空输入缓冲区 
		scanf_s("%d", &index);
		if (index == 0)
		{
			exit(0);
		}
	}
}
#include <stdio.h>
#include "Storage.h"
#include "MustNode2Path.h"
#include <time.h>
#include <windows.h>
#include <stdio.h>
#include "PathInit.h"
#include "DeleteMust.h"
#include "out1.h"
#include "jlu.h"
int getOneCost(int startNo, int endNo)
{
	int pathNum, layout; /* 路径数  跳数 */
						 /* 矩阵 = 路径数 *（跳数 + 1) 首元素为 花费  */
	int selectedPath;
	int cost = MAX_VALUE;
	int* link;
	int loc_startNo = getPos(startNo); /* 获取节点在所有必经节点集合的下标位置 */
	int loc_endNo = getPos(endNo);

	if (loc_startNo < loc_endNo)
	{//正向打印
		pathNum = pPathMatrix[loc_startNo*gatherNode.num + loc_endNo].PathNum;
		layout = pPathMatrix[loc_startNo*gatherNode.num + loc_endNo].LayerNum;
		link = pPathMatrix[loc_startNo*gatherNode.num + loc_endNo].link;
		for (int i = 0; i < pathNum; i++)
		{//选择花费最小的路径
			if (link[i*(layout + 1) + 0] < cost)
			{
				selectedPath = i;
				cost = link[i*(layout + 1) + 0];
			}
		}
	}
	else
	{//反向打印
		pathNum = pPathMatrix[loc_endNo*gatherNode.num + loc_startNo].PathNum;
		layout = pPathMatrix[loc_endNo*gatherNode.num + loc_startNo].LayerNum;
		link = pPathMatrix[loc_endNo*gatherNode.num + loc_startNo].link;
		for (int i = 0; i < pathNum; i++)
		{//选择花费最小的路径
			if (link[i*(layout + 1) + 0] < cost)
			{
				selectedPath = i;
				cost = link[i*(layout + 1) + 0];
			}
		}
	}
	//if (cost == MAX_VALUE)
	//{
	//	getchar();
	//}
	return cost;
}
int getCostFromMustOrdeLink(gatherNodeType AllMustNodeOrderGather)
{
	int no, end_no;
	int cost_sum = 0;
	for (int i = 1; i < AllMustNodeOrderGather.num; i++)
	{
		no = AllMustNodeOrderGather.p[i - 1];
		end_no = AllMustNodeOrderGather.p[i];
		cost_sum += getOneCost(no, end_no);
	}
	return cost_sum;
}
void jlu_out()
{
	int hop_2opt;
	Joint();/* 双向邻近 + 节省插入 + 2-opt 操作 */
	hop_2opt = optEffect(AllMustNodeOrderGather);
	printf("通过所有必经点、边最少需要经过 %d 个节点, 阈值 = %d\n", hop_2opt, AdjGraf.MaxHop);
	//最优解
	if (hop_2opt == AdjGraf.MaxHop)
	{
		printf("有解：输出最优路径：路径总跳数 <= 阈值条件下的最小花费路径\n");
		printf("\n【最优路径：经过节点数 = %d, 花费 = %d】\n", hop_2opt,
			getCostFromMustOrdeLink(AllMustNodeOrderGather));
		PrintPathes(AllMustNodeOrderGather);
	}
	//有解——最小跳数参考路径——费用优化最优解
	else if (hop_2opt < AdjGraf.MaxHop)
	{
		printf("有解：输出参考路径：路径总跳数最小条件下的最小花费路径\n");
		printf("      输出最优路径：路径总跳数 <= 阈值条件下的最小花费路径\n");
		printf("\n【参考路径：经过节点数 = %d, 花费 = %d】\n", hop_2opt,
			getCostFromMustOrdeLink(AllMustNodeOrderGather));
		PrintPathes(AllMustNodeOrderGather);
		Test(hop_2opt);  /* 费用优化 */

		//printf("最优路径：经过节点数 = %d, 花费 = %d\n");
	}
	//无解——约束条件优先级输出
	else
	{
		printf("无解，输出约束条件在不同优先级排列情况下的次优解\n");
		DeleteMust();/* 获得删除成本*/
		Out();
		printf("\n【 6、约束条件优先级：跳数 < 必经边 / 必经点】——经过节点数 = %3d， 花费 = %d, 不经过的必经点数 = %3d, 不经过的必经边数 = %3d \n", hop_2opt,
			getCostFromMustOrdeLink(AllMustNodeOrderGather), 0, 0);
		SelectOneAllPath();
	}
}

void SelectOneAllPath()
{
	int index = 0;
	/*printf("输入0，退出当前测试\n");
	printf("输入次优解序号(1-6),查看对应约束条件优先级下次优解完整路径\n");*/
	while (1)
	{
		printf("\n【0:退出测试，1-6:输出对应约束条件优先级排序下次优解完整路径】请输入参数：");
		fflush(stdin);//清空输入缓冲区 
		scanf_s("%d", &index);
		switch (index)
		{
		case 1:out_1_path(); break;
		case 2:out_2_path(); break;
		case 3:out_3_path(); break;
		case 4:out_4_path(); break;
		case 5:out_5_path(); break;
		case 6:out_6_path(); break;
		case 0:exit(0); break;
		default:printf("输出参数错误，请重新输入: ");
		}
	}
}
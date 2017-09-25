#include <stdio.h>
#include "Storage.h"
#include "2opt.h"
/*对必经节点顺序集合进行优化
extern gatherNodeType AllMustNodeOrderGather; //所有必须经过的节点顺序集合
s  1  2  3  4  5  6  7  e
s  1  5  4  3  2  6  7  e  <opt1,opt2> = <2,5>
s  1  2  3  7  6  5  4  e  <opt1,opt2> = <4,7>
下标操作
*/

int AllHopCount;

int IsOpt(int opt1_Index, int opt2_Index)
{//判断交换序列 opt1 -> ... -> opt2 为 opt2 -> ... -> opt1 后最小跳数是否减小
	int pre_opt1_Index, next_opt2_Index; /* opt1前驱节点 opt2后继节点 */
	int yuanCost = 0, nowCost = 0;   /* 交换前后的路径跳数 */
	int s, t;
	pre_opt1_Index = opt1_Index - 1; next_opt2_Index = opt2_Index + 1;

	if (IsBreakEdge(opt1_Index, opt2_Index))
		return 0; /* 该 opt 操作会打破边，放弃  */
	/* yuanCost = pre_opt1 > a > b > c > next_opt2 */
	for (int i = pre_opt1_Index; i < next_opt2_Index; i++)
	{
		/* 在所有必经节点顺序链中获得 当前操作的 s-->t */
		s = AllMustNodeOrderGather.p[i]; t = AllMustNodeOrderGather.p[i + 1];
		/* 在所有必经节点初始化链中获得 s-->t 的相关信息*/
		yuanCost += (pPathMatrix[getPos(s)*gatherNode.num + getPos(t)].LayerNum - 1);
	}
	yuanCost++;

	/* nowCost = pre_opt1 > c > b > a > next_opt2 */
	s = AllMustNodeOrderGather.p[pre_opt1_Index];
	for (int i = 1; i < next_opt2_Index - pre_opt1_Index; i++)
	{
		/* 在所有必经节点顺序链中获得 当前操作的 s-->t */
		t = AllMustNodeOrderGather.p[next_opt2_Index - i];
		/* 在所有必经节点初始化链中获得 s-->t 的相关信息*/
		nowCost += (pPathMatrix[getPos(s)*gatherNode.num + getPos(t)].LayerNum - 1);
		s = t;
	}
	t = AllMustNodeOrderGather.p[next_opt2_Index];
	nowCost += (pPathMatrix[getPos(s)*gatherNode.num + getPos(t)].LayerNum - 1);
	nowCost++;

	if (nowCost < yuanCost)
		return 1;//需要交换
	else
		return 0;//不需要交换
}
int Exchange(int opt1_Index, int opt2_Index)
{//交换序列 
//偶：opt1 -> a -> b -> opt2     opt2 -> b -> a -> opt1
//奇：opt1 -> a -> opt2          opt2 ->  a -> opt1
//偶：4 -> 5 -> 6 -> 7     7 -> 6 -> 5 -> 4   交换2次  7-4 6-5 
//奇：3 -> 4 -> 5          5 -> 4 -> 3        交换1次  3-5
	int times = (opt2_Index - opt1_Index + 1) / 2; //需要交换的次数
	int head = opt1_Index, tail = opt2_Index;
	static int index = 0;
	for (int i = 0; i < times; i++)
	{
		int temp;
		temp = AllMustNodeOrderGather.p[head];
		AllMustNodeOrderGather.p[head] = AllMustNodeOrderGather.p[tail];
		AllMustNodeOrderGather.p[tail] = temp;
		head++; tail--;
	}
	//printf("\n交换%d-->%d\n", AllMustNodeOrderGather.p[opt1_Index], AllMustNodeOrderGather.p[opt2_Index]);
	//printf("优化次数 = %d\n", ++index);
}
int opt()
{
	for (int k = 2; k<AllMustNodeOrderGather.num; k++)
		for (int i = 1; i < AllMustNodeOrderGather.num - k; i++)
		{//2-opt优化
			if (IsOpt(i, i + k - 1)) Exchange(i, i + k - 1);
		}
	//printf("\n邻近+节省+ 2-opt 操作——路径跳数 = %d\n", optEffect(AllMustNodeOrderGather));
	//PrintPathes(AllMustNodeOrderGather);
}
int optEffect(gatherNodeType AllMustNodeOrderGather)
{
	int hopCount = 0;
	int s, t;
	for (int i = 0; i < AllMustNodeOrderGather.num - 1; i++)
	{// s -> 1 -> 2 -> e (i 不可以等于终止节点)
		/* 在所有必经节点顺序链中获得 当前操作的 s-->t */
		s = AllMustNodeOrderGather.p[i]; t = AllMustNodeOrderGather.p[i + 1];
		/* 在所有必经节点初始化链中获得 s-->t 的相关信息*/
		hopCount += (pPathMatrix[getPos(s)*gatherNode.num + getPos(t)].LayerNum - 1);
	}
	hopCount++;
	//printf("链路最小跳数 = %d\n", hopCount);
	return hopCount;
}

int IsBreakEdge(int opt1_Index, int opt2_Index)
{//判断 opt 操作是否会打破必经边 
/* pre_opt1 - opt1 或者 opt2 - next_opt2 是否为必经边 */
/* pre_opt1 > opt1 > a > b > c > opt2 > next_opt2 */
	EdgeNodeType *p = NULL;
	int opt1, opt2;
	int pre_opt1, next_opt2;   /* opt1前驱节点 opt2后继节点 */
	opt1 = AllMustNodeOrderGather.p[opt1_Index];
	opt2 = AllMustNodeOrderGather.p[opt2_Index];
	pre_opt1 = AllMustNodeOrderGather.p[opt1_Index - 1];
	next_opt2 = AllMustNodeOrderGather.p[opt2_Index + 1];

	p = AdjGraf.VNode[pre_opt1].firstEdge;
	while (p != NULL)
	{/* pre_opt1 - opt1 */
		if (p->End_No == opt1)
		{
			if (p->E_data.eType == 1)
				return 1;
			else
				break;
		}
		else
		{
			p = p->nextEdge;
		}
	}

	p = AdjGraf.VNode[opt2].firstEdge;
	while (p != NULL)
	{/* opt2 - next_opt2 */
		if (p->End_No == next_opt2)
		{
			if (p->E_data.eType == 1)
				return 1;
			else
				break;
		}
		else
		{
			p = p->nextEdge;
		}
	}


	return 0;
}


int IsOpt_2(int opt1_Index, int opt2_Index)
{//判断交换序列 opt1 -> ... -> opt2 为 opt2 -> ... -> opt1 后最小跳数是否减小
	int pre_opt1_Index, next_opt2_Index; /* opt1前驱节点 opt2后继节点 */
	int yuanCost = 0, nowCost = 0;   /* 交换前后的路径跳数 */
	int s, t;
	pre_opt1_Index = opt1_Index - 1; next_opt2_Index = opt2_Index + 1;

	if (IsBreakEdge_2(opt1_Index, opt2_Index))
		return 0; /* 该 opt 操作会打破边，放弃  */
				  /* yuanCost = pre_opt1 > a > b > c > next_opt2 */
	for (int i = pre_opt1_Index; i < next_opt2_Index; i++)
	{
		/* 在所有必经节点顺序链中获得 当前操作的 s-->t */
		s = AllMustNodeOrderGather_2.p[i]; t = AllMustNodeOrderGather_2.p[i + 1];
		/* 在所有必经节点初始化链中获得 s-->t 的相关信息*/
		yuanCost += (pPathMatrix[getPos(s)*gatherNode.num + getPos(t)].LayerNum - 1);
	}
	yuanCost++;

	/* nowCost = pre_opt1 > c > b > a > next_opt2 */
	s = AllMustNodeOrderGather_2.p[pre_opt1_Index];
	for (int i = 1; i < next_opt2_Index - pre_opt1_Index; i++)
	{
		/* 在所有必经节点顺序链中获得 当前操作的 s-->t */
		t = AllMustNodeOrderGather_2.p[next_opt2_Index - i];
		/* 在所有必经节点初始化链中获得 s-->t 的相关信息*/
		nowCost += (pPathMatrix[getPos(s)*gatherNode.num + getPos(t)].LayerNum - 1);
		s = t;
	}
	t = AllMustNodeOrderGather_2.p[next_opt2_Index];
	nowCost += (pPathMatrix[getPos(s)*gatherNode.num + getPos(t)].LayerNum - 1);
	nowCost++;

	if (nowCost < yuanCost)
		return 1;//需要交换
	else
		return 0;//不需要交换
}
int Exchange_2(int opt1_Index, int opt2_Index)
{//交换序列 
 //偶：opt1 -> a -> b -> opt2     opt2 -> b -> a -> opt1
 //奇：opt1 -> a -> opt2          opt2 ->  a -> opt1
 //偶：4 -> 5 -> 6 -> 7     7 -> 6 -> 5 -> 4   交换2次  7-4 6-5 
 //奇：3 -> 4 -> 5          5 -> 4 -> 3        交换1次  3-5
	int times = (opt2_Index - opt1_Index + 1) / 2; //需要交换的次数
	int head = opt1_Index, tail = opt2_Index;
	static int index = 0;
	for (int i = 0; i < times; i++)
	{
		int temp;
		temp = AllMustNodeOrderGather_2.p[head];
		AllMustNodeOrderGather_2.p[head] = AllMustNodeOrderGather_2.p[tail];
		AllMustNodeOrderGather_2.p[tail] = temp;
		head++; tail--;
	}
	//printf("\n交换%d-->%d\n", AllMustNodeOrderGather.p[opt1_Index], AllMustNodeOrderGather.p[opt2_Index]);
	//printf("优化次数 = %d\n", ++index);
}
int opt_2()
{
	for (int k = 2; k<AllMustNodeOrderGather_2.num; k++)
		for (int i = 1; i < AllMustNodeOrderGather_2.num - k; i++)
		{//2-opt优化
			if (IsOpt_2(i, i + k - 1)) Exchange_2(i, i + k - 1);
		}
	//printf("\n邻近+节省+ 2-opt 操作——路径跳数 = %d\n", optEffect(AllMustNodeOrderGather));
	//PrintPathes(AllMustNodeOrderGather);
}

int IsBreakEdge_2(int opt1_Index, int opt2_Index)
{//判断 opt 操作是否会打破必经边 
 /* pre_opt1 - opt1 或者 opt2 - next_opt2 是否为必经边 */
 /* pre_opt1 > opt1 > a > b > c > opt2 > next_opt2 */
	EdgeNodeType *p = NULL;
	int opt1, opt2;
	int pre_opt1, next_opt2;   /* opt1前驱节点 opt2后继节点 */
	opt1 = AllMustNodeOrderGather_2.p[opt1_Index];
	opt2 = AllMustNodeOrderGather_2.p[opt2_Index];
	pre_opt1 = AllMustNodeOrderGather_2.p[opt1_Index - 1];
	next_opt2 = AllMustNodeOrderGather_2.p[opt2_Index + 1];

	p = AdjGraf.VNode[pre_opt1].firstEdge;
	while (p != NULL)
	{/* pre_opt1 - opt1 */
		if (p->End_No == opt1)
		{
			if (p->E_data.eType == 1)
				return 1;
			else
				break;
		}
		else
		{
			p = p->nextEdge;
		}
	}

	p = AdjGraf.VNode[opt2].firstEdge;
	while (p != NULL)
	{/* opt2 - next_opt2 */
		if (p->End_No == next_opt2)
		{
			if (p->E_data.eType == 1)
				return 1;
			else
				break;
		}
		else
		{
			p = p->nextEdge;
		}
	}


	return 0;
}
#include <stdio.h>
#include "Storage.h"
#include "2opt.h"
/*�Աؾ��ڵ�˳�򼯺Ͻ����Ż�
extern gatherNodeType AllMustNodeOrderGather; //���б��뾭���Ľڵ�˳�򼯺�
s  1  2  3  4  5  6  7  e
s  1  5  4  3  2  6  7  e  <opt1,opt2> = <2,5>
s  1  2  3  7  6  5  4  e  <opt1,opt2> = <4,7>
�±����
*/

int AllHopCount;

int IsOpt(int opt1_Index, int opt2_Index)
{//�жϽ������� opt1 -> ... -> opt2 Ϊ opt2 -> ... -> opt1 ����С�����Ƿ��С
	int pre_opt1_Index, next_opt2_Index; /* opt1ǰ���ڵ� opt2��̽ڵ� */
	int yuanCost = 0, nowCost = 0;   /* ����ǰ���·������ */
	int s, t;
	pre_opt1_Index = opt1_Index - 1; next_opt2_Index = opt2_Index + 1;

	if (IsBreakEdge(opt1_Index, opt2_Index))
		return 0; /* �� opt ��������Ʊߣ�����  */
	/* yuanCost = pre_opt1 > a > b > c > next_opt2 */
	for (int i = pre_opt1_Index; i < next_opt2_Index; i++)
	{
		/* �����бؾ��ڵ�˳�����л�� ��ǰ������ s-->t */
		s = AllMustNodeOrderGather.p[i]; t = AllMustNodeOrderGather.p[i + 1];
		/* �����бؾ��ڵ��ʼ�����л�� s-->t �������Ϣ*/
		yuanCost += (pPathMatrix[getPos(s)*gatherNode.num + getPos(t)].LayerNum - 1);
	}
	yuanCost++;

	/* nowCost = pre_opt1 > c > b > a > next_opt2 */
	s = AllMustNodeOrderGather.p[pre_opt1_Index];
	for (int i = 1; i < next_opt2_Index - pre_opt1_Index; i++)
	{
		/* �����бؾ��ڵ�˳�����л�� ��ǰ������ s-->t */
		t = AllMustNodeOrderGather.p[next_opt2_Index - i];
		/* �����бؾ��ڵ��ʼ�����л�� s-->t �������Ϣ*/
		nowCost += (pPathMatrix[getPos(s)*gatherNode.num + getPos(t)].LayerNum - 1);
		s = t;
	}
	t = AllMustNodeOrderGather.p[next_opt2_Index];
	nowCost += (pPathMatrix[getPos(s)*gatherNode.num + getPos(t)].LayerNum - 1);
	nowCost++;

	if (nowCost < yuanCost)
		return 1;//��Ҫ����
	else
		return 0;//����Ҫ����
}
int Exchange(int opt1_Index, int opt2_Index)
{//�������� 
//ż��opt1 -> a -> b -> opt2     opt2 -> b -> a -> opt1
//�棺opt1 -> a -> opt2          opt2 ->  a -> opt1
//ż��4 -> 5 -> 6 -> 7     7 -> 6 -> 5 -> 4   ����2��  7-4 6-5 
//�棺3 -> 4 -> 5          5 -> 4 -> 3        ����1��  3-5
	int times = (opt2_Index - opt1_Index + 1) / 2; //��Ҫ�����Ĵ���
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
	//printf("\n����%d-->%d\n", AllMustNodeOrderGather.p[opt1_Index], AllMustNodeOrderGather.p[opt2_Index]);
	//printf("�Ż����� = %d\n", ++index);
}
int opt()
{
	for (int k = 2; k<AllMustNodeOrderGather.num; k++)
		for (int i = 1; i < AllMustNodeOrderGather.num - k; i++)
		{//2-opt�Ż�
			if (IsOpt(i, i + k - 1)) Exchange(i, i + k - 1);
		}
	//printf("\n�ڽ�+��ʡ+ 2-opt ��������·������ = %d\n", optEffect(AllMustNodeOrderGather));
	//PrintPathes(AllMustNodeOrderGather);
}
int optEffect(gatherNodeType AllMustNodeOrderGather)
{
	int hopCount = 0;
	int s, t;
	for (int i = 0; i < AllMustNodeOrderGather.num - 1; i++)
	{// s -> 1 -> 2 -> e (i �����Ե�����ֹ�ڵ�)
		/* �����бؾ��ڵ�˳�����л�� ��ǰ������ s-->t */
		s = AllMustNodeOrderGather.p[i]; t = AllMustNodeOrderGather.p[i + 1];
		/* �����бؾ��ڵ��ʼ�����л�� s-->t �������Ϣ*/
		hopCount += (pPathMatrix[getPos(s)*gatherNode.num + getPos(t)].LayerNum - 1);
	}
	hopCount++;
	//printf("��·��С���� = %d\n", hopCount);
	return hopCount;
}

int IsBreakEdge(int opt1_Index, int opt2_Index)
{//�ж� opt �����Ƿ����Ʊؾ��� 
/* pre_opt1 - opt1 ���� opt2 - next_opt2 �Ƿ�Ϊ�ؾ��� */
/* pre_opt1 > opt1 > a > b > c > opt2 > next_opt2 */
	EdgeNodeType *p = NULL;
	int opt1, opt2;
	int pre_opt1, next_opt2;   /* opt1ǰ���ڵ� opt2��̽ڵ� */
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
{//�жϽ������� opt1 -> ... -> opt2 Ϊ opt2 -> ... -> opt1 ����С�����Ƿ��С
	int pre_opt1_Index, next_opt2_Index; /* opt1ǰ���ڵ� opt2��̽ڵ� */
	int yuanCost = 0, nowCost = 0;   /* ����ǰ���·������ */
	int s, t;
	pre_opt1_Index = opt1_Index - 1; next_opt2_Index = opt2_Index + 1;

	if (IsBreakEdge_2(opt1_Index, opt2_Index))
		return 0; /* �� opt ��������Ʊߣ�����  */
				  /* yuanCost = pre_opt1 > a > b > c > next_opt2 */
	for (int i = pre_opt1_Index; i < next_opt2_Index; i++)
	{
		/* �����бؾ��ڵ�˳�����л�� ��ǰ������ s-->t */
		s = AllMustNodeOrderGather_2.p[i]; t = AllMustNodeOrderGather_2.p[i + 1];
		/* �����бؾ��ڵ��ʼ�����л�� s-->t �������Ϣ*/
		yuanCost += (pPathMatrix[getPos(s)*gatherNode.num + getPos(t)].LayerNum - 1);
	}
	yuanCost++;

	/* nowCost = pre_opt1 > c > b > a > next_opt2 */
	s = AllMustNodeOrderGather_2.p[pre_opt1_Index];
	for (int i = 1; i < next_opt2_Index - pre_opt1_Index; i++)
	{
		/* �����бؾ��ڵ�˳�����л�� ��ǰ������ s-->t */
		t = AllMustNodeOrderGather_2.p[next_opt2_Index - i];
		/* �����бؾ��ڵ��ʼ�����л�� s-->t �������Ϣ*/
		nowCost += (pPathMatrix[getPos(s)*gatherNode.num + getPos(t)].LayerNum - 1);
		s = t;
	}
	t = AllMustNodeOrderGather_2.p[next_opt2_Index];
	nowCost += (pPathMatrix[getPos(s)*gatherNode.num + getPos(t)].LayerNum - 1);
	nowCost++;

	if (nowCost < yuanCost)
		return 1;//��Ҫ����
	else
		return 0;//����Ҫ����
}
int Exchange_2(int opt1_Index, int opt2_Index)
{//�������� 
 //ż��opt1 -> a -> b -> opt2     opt2 -> b -> a -> opt1
 //�棺opt1 -> a -> opt2          opt2 ->  a -> opt1
 //ż��4 -> 5 -> 6 -> 7     7 -> 6 -> 5 -> 4   ����2��  7-4 6-5 
 //�棺3 -> 4 -> 5          5 -> 4 -> 3        ����1��  3-5
	int times = (opt2_Index - opt1_Index + 1) / 2; //��Ҫ�����Ĵ���
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
	//printf("\n����%d-->%d\n", AllMustNodeOrderGather.p[opt1_Index], AllMustNodeOrderGather.p[opt2_Index]);
	//printf("�Ż����� = %d\n", ++index);
}
int opt_2()
{
	for (int k = 2; k<AllMustNodeOrderGather_2.num; k++)
		for (int i = 1; i < AllMustNodeOrderGather_2.num - k; i++)
		{//2-opt�Ż�
			if (IsOpt_2(i, i + k - 1)) Exchange_2(i, i + k - 1);
		}
	//printf("\n�ڽ�+��ʡ+ 2-opt ��������·������ = %d\n", optEffect(AllMustNodeOrderGather));
	//PrintPathes(AllMustNodeOrderGather);
}

int IsBreakEdge_2(int opt1_Index, int opt2_Index)
{//�ж� opt �����Ƿ����Ʊؾ��� 
 /* pre_opt1 - opt1 ���� opt2 - next_opt2 �Ƿ�Ϊ�ؾ��� */
 /* pre_opt1 > opt1 > a > b > c > opt2 > next_opt2 */
	EdgeNodeType *p = NULL;
	int opt1, opt2;
	int pre_opt1, next_opt2;   /* opt1ǰ���ڵ� opt2��̽ڵ� */
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
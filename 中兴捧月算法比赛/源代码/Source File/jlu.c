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
	int pathNum, layout; /* ·����  ���� */
						 /* ���� = ·���� *������ + 1) ��Ԫ��Ϊ ����  */
	int selectedPath;
	int cost = MAX_VALUE;
	int* link;
	int loc_startNo = getPos(startNo); /* ��ȡ�ڵ������бؾ��ڵ㼯�ϵ��±�λ�� */
	int loc_endNo = getPos(endNo);

	if (loc_startNo < loc_endNo)
	{//�����ӡ
		pathNum = pPathMatrix[loc_startNo*gatherNode.num + loc_endNo].PathNum;
		layout = pPathMatrix[loc_startNo*gatherNode.num + loc_endNo].LayerNum;
		link = pPathMatrix[loc_startNo*gatherNode.num + loc_endNo].link;
		for (int i = 0; i < pathNum; i++)
		{//ѡ�񻨷���С��·��
			if (link[i*(layout + 1) + 0] < cost)
			{
				selectedPath = i;
				cost = link[i*(layout + 1) + 0];
			}
		}
	}
	else
	{//�����ӡ
		pathNum = pPathMatrix[loc_endNo*gatherNode.num + loc_startNo].PathNum;
		layout = pPathMatrix[loc_endNo*gatherNode.num + loc_startNo].LayerNum;
		link = pPathMatrix[loc_endNo*gatherNode.num + loc_startNo].link;
		for (int i = 0; i < pathNum; i++)
		{//ѡ�񻨷���С��·��
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
	Joint();/* ˫���ڽ� + ��ʡ���� + 2-opt ���� */
	hop_2opt = optEffect(AllMustNodeOrderGather);
	printf("ͨ�����бؾ��㡢��������Ҫ���� %d ���ڵ�, ��ֵ = %d\n", hop_2opt, AdjGraf.MaxHop);
	//���Ž�
	if (hop_2opt == AdjGraf.MaxHop)
	{
		printf("�н⣺�������·����·�������� <= ��ֵ�����µ���С����·��\n");
		printf("\n������·���������ڵ��� = %d, ���� = %d��\n", hop_2opt,
			getCostFromMustOrdeLink(AllMustNodeOrderGather));
		PrintPathes(AllMustNodeOrderGather);
	}
	//�н⡪����С�����ο�·�����������Ż����Ž�
	else if (hop_2opt < AdjGraf.MaxHop)
	{
		printf("�н⣺����ο�·����·����������С�����µ���С����·��\n");
		printf("      �������·����·�������� <= ��ֵ�����µ���С����·��\n");
		printf("\n���ο�·���������ڵ��� = %d, ���� = %d��\n", hop_2opt,
			getCostFromMustOrdeLink(AllMustNodeOrderGather));
		PrintPathes(AllMustNodeOrderGather);
		Test(hop_2opt);  /* �����Ż� */

		//printf("����·���������ڵ��� = %d, ���� = %d\n");
	}
	//�޽⡪��Լ���������ȼ����
	else
	{
		printf("�޽⣬���Լ�������ڲ�ͬ���ȼ���������µĴ��Ž�\n");
		DeleteMust();/* ���ɾ���ɱ�*/
		Out();
		printf("\n�� 6��Լ���������ȼ������� < �ؾ��� / �ؾ��㡿���������ڵ��� = %3d�� ���� = %d, �������ıؾ����� = %3d, �������ıؾ����� = %3d \n", hop_2opt,
			getCostFromMustOrdeLink(AllMustNodeOrderGather), 0, 0);
		SelectOneAllPath();
	}
}

void SelectOneAllPath()
{
	int index = 0;
	/*printf("����0���˳���ǰ����\n");
	printf("������Ž����(1-6),�鿴��ӦԼ���������ȼ��´��Ž�����·��\n");*/
	while (1)
	{
		printf("\n��0:�˳����ԣ�1-6:�����ӦԼ���������ȼ������´��Ž�����·���������������");
		fflush(stdin);//������뻺���� 
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
		default:printf("���������������������: ");
		}
	}
}
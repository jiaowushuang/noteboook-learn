#include"Storage.h"
#include"Link.h"
#include "2opt.h"
#include "Joint.h"


int getKey(int k)
{
	int add = 2*k;
	if (k < 10)
		add += 15;
	else if (k < 20)
		add += 10;
	else if (k < 30)
		add += 5;
	return add;
}
//Լ���������ȼ����ؾ��� < ���� < �ؾ���
void Set_1_Used(int val)
{
	int hopNow = optEffect(AllMustNodeOrderGather);
	int yuzhi_hop;
	int sum = 0;
	mustNodeLink.endIndex = mustNodeLink.ListLen;
	yuzhi_hop = (hopNow - AdjGraf.MaxHop);
	yuzhi_hop = getKey(yuzhi_hop);
	//yuzhi_hop = hopNow - AdjGraf.MaxHop;
	for (int i = 1; i <= mustNodeLink.ListLen; i++)
	{
		sum += mustNodeLink.ListData[i].costSum;
		//sum += mustNodeLink.ListData[i].DeleteSubCost;
		mustNodeLink.ListData[i].IsUsed = val;
		if (sum >= yuzhi_hop)
		{
			mustNodeLink.endIndex = i;
			break;
		}
	}
	mustNodeLink.usedNum = mustNodeLink.ListLen - mustNodeLink.endIndex;

	//mustEdgeLink.endIndex = 0;
	//mustEdgeLink.usedNum = mustEdgeLink.ListData;
}
//Լ���������ȼ����ؾ��� < ���� < �ؾ���
void Set_2_Used(int val)
{
	int hopNow = optEffect(AllMustNodeOrderGather);
	int yuzhi_hop;
	int sum = 0;
	mustEdgeLink.endIndex = mustEdgeLink.ListLen;
	yuzhi_hop = (hopNow - AdjGraf.MaxHop);
	yuzhi_hop = getKey(yuzhi_hop);
	//yuzhi_hop = hopNow - AdjGraf.MaxHop;
	for (int i = 1; i <= mustEdgeLink.ListLen; i++)
	{
		sum += mustEdgeLink.ListData[i].costSum;
		//sum += mustEdgeLink.ListData[i].DeleteSubCost;
		mustEdgeLink.ListData[i].IsUsed = val;
		if (sum >= yuzhi_hop)
		{
			mustEdgeLink.endIndex = i;
			break;
		}
	}
	mustEdgeLink.usedNum = mustEdgeLink.ListLen - mustEdgeLink.endIndex;

	//mustNodeLink.endIndex = 0;
	//mustNodeLink.usedNum = mustNodeLink.ListData;
}
//Լ���������ȼ����ؾ��� = �ؾ��� < ����
void Set_3_Used(int val)
{
	int hopNow = optEffect(AllMustNodeOrderGather);
	int yuzhi_hop;
	int sum = 0;
	int max1, max2;
	int index = 0;
	mustNodeLink.endIndex = 0;  mustEdgeLink.endIndex = 0;
	yuzhi_hop = (hopNow - AdjGraf.MaxHop);
	yuzhi_hop = getKey(yuzhi_hop);
	//yuzhi_hop = hopNow - AdjGraf.MaxHop;
	while (!((mustNodeLink.endIndex >= mustNodeLink.ListLen) && 
		(mustEdgeLink.endIndex >= mustEdgeLink.ListLen)))
	{
		if (mustNodeLink.endIndex == mustNodeLink.ListLen)
			max1 = 0;
		else
			max1 = mustNodeLink.ListData[mustNodeLink.endIndex+1].costSum;
		if (mustEdgeLink.endIndex == mustEdgeLink.ListLen)
			max2 = 0;
		else
			max2 = mustEdgeLink.ListData[mustEdgeLink.endIndex+1].costSum;
		if (max1 > max2)
		{//ѡ��ɾ��һ���ؾ���
			sum += max1;
			mustNodeLink.endIndex++;
			mustNodeLink.ListData[mustNodeLink.endIndex].IsUsed = val;
		}
		else if (max1 < max2)
		{//ѡ��ɾ��һ���ؾ���
			sum += max2;
			mustEdgeLink.endIndex++;
			mustEdgeLink.ListData[mustEdgeLink.endIndex].IsUsed = val;
		}
		else if (max1 == max2)
		{
			if (max1 != 0)
			{
				sum += max1;
				mustNodeLink.endIndex++;
				mustNodeLink.ListData[mustNodeLink.endIndex].IsUsed = val;

				sum += max2;
				mustEdgeLink.endIndex++;
				mustEdgeLink.ListData[mustEdgeLink.endIndex].IsUsed = val;
			}
			else
			{
				break;
			}
		}
		if (sum >= yuzhi_hop)
		{
			break;
		}
		if ((max1 == 0) && (max2 == 0))
		{
			break;
		}
		//printf("%3d %3d %3d %3d mustNodeLink.endIndex = %d,  mustEdgeLink.endIndex = %d\n",++index, sum, max1, max2,  
		//	mustNodeLink.endIndex, mustEdgeLink.endIndex);
	}
	mustNodeLink.usedNum = mustNodeLink.ListLen - mustNodeLink.endIndex;
	mustEdgeLink.usedNum = mustEdgeLink.ListLen - mustEdgeLink.endIndex;
}
//Լ���������ȼ����ؾ��� < �ؾ��� < ����
void Set_4_Used(int val)
{
	//�ؾ��㡶�ؾ��ߡ�����
	int maxLayer = AdjGraf.MaxHop;
	int nowLayer = optEffect(AllMustNodeOrderGather);
	int sum = 0;
	int n;
	n = (nowLayer - AdjGraf.MaxHop);
	n = getKey(n);
	int i = 0;
	int sumInsert = 0;
	int sumDelete = 0;

	mustNodeLink.endIndex = mustNodeLink.ListLen;
	mustEdgeLink.endIndex = mustEdgeLink.ListLen;

	for (i = 1; i <= mustNodeLink.ListLen&&sum<n; i++)
	{

		sum += mustNodeLink.ListData[i].costSum;
		mustNodeLink.ListData[i].IsUsed = val;
		if (sum >= n)
		{
			mustNodeLink.endIndex = i;
			break;
		}

	}
	if (i > mustNodeLink.ListLen)
	{
		int temp = (n - sum) / 2;
		for (i = 1; i <= mustEdgeLink.ListLen && (sum <= n || sumDelete <= temp || sumInsert <= temp); i++)
		{
			sumDelete += mustEdgeLink.ListData[i].DeleteSubCost;
			sumInsert += mustEdgeLink.ListData[i].InsertAddCost;
			sum += mustEdgeLink.ListData[i].costSum;
			mustEdgeLink.ListData[i].IsUsed = val;
			if (sum >n&&sumDelete >temp&&sumInsert>temp)
			{
				mustEdgeLink.endIndex = i;
				break;
			}

		}

	}
	mustNodeLink.usedNum = mustNodeLink.ListLen - mustNodeLink.endIndex;
	mustEdgeLink.usedNum = mustEdgeLink.ListLen - mustEdgeLink.endIndex;

}
//Լ���������ȼ����ؾ��� < �ؾ��� < ����
void Set_5_Used(int val)
{
	//�ؾ��ߡ��ؾ��㡶����
	int maxLayer = AdjGraf.MaxHop;
	int nowLayer = optEffect(AllMustNodeOrderGather);
	int sum = 0;
	int n;
	n = (nowLayer - AdjGraf.MaxHop);
	n = getKey(n);
	int i = 0;
	mustNodeLink.endIndex = mustNodeLink.ListLen;
	mustEdgeLink.endIndex = mustEdgeLink.ListLen;
	int sumInsert = 0;
	int sumDelete = 0;
	for (i = 1; i <= mustEdgeLink.ListLen && (sum <= n || sumDelete <= (n / 2) || sumInsert <= (n / 2)); i++)
	{
		sumInsert += mustEdgeLink.ListData[i].InsertAddCost;
		sumDelete += mustEdgeLink.ListData[i].DeleteSubCost;
		sum += mustEdgeLink.ListData[i].costSum;
		mustEdgeLink.ListData[i].IsUsed = val;
		if (sum >n&&sumDelete>(n / 2) && sumInsert>(n / 2))
		{
			mustEdgeLink.endIndex = i;
			break;
		}

	}
	if (i > mustEdgeLink.ListLen)
	{
		for (i = 1; i <= mustNodeLink.ListLen&&sum <= n; i++)
		{

			sum += mustNodeLink.ListData[i].costSum;
			mustNodeLink.ListData[i].IsUsed = val;
			if (sum > n)
			{
				mustNodeLink.endIndex = i;
				break;
			}

		}

	}
	mustNodeLink.usedNum = mustNodeLink.ListLen - mustNodeLink.endIndex;
	mustEdgeLink.usedNum = mustEdgeLink.ListLen - mustEdgeLink.endIndex;

}
void InsertNoDelete()
{//����һ���߻���һ���ڵ㡪���ڽ�+��ʡ���뷨
	int temp;
	int head, tail, no;

	int FlagInsertDir = 0; /* no = ͷ / β�ڵ���βԪ��*/
	head = AdjGraf.StartNode;
	tail = AdjGraf.EndNode;

	while ((mustEdgeLink.usedNum > 0) || (mustNodeLink.usedNum > 0))
	{
		int minVal = MAX_VALUE;//������С����
		int addFlag, addIndex;

		if (FlagInsertDir == 0)	no = head;
		else	                no = tail;

		for (int i = 1; i <= mustNodeLink.ListLen; i++)
		{//��ȡ�ڵ� no �� �ؾ��ڵ�ĵ���С�����͸ñؾ��ڵ���
			if (mustNodeLink.ListData[i].IsUsed == 0)
			{
				temp = pPathMatrix[getPos(no)*gatherNode.num
					+ getPos(mustNodeLink.ListData[i].no)].LayerNum;
				if (temp < minVal)
				{
					minVal = temp;
					addFlag = 0; addIndex = i;//����ؾ��ڵ�i
				}
			}
		}
		for (int i = 1; i <= mustEdgeLink.ListLen; i++)
		{//��ȡ�ڵ� no �� �ؾ��ߵĵ���С�����͸ñؾ��߱��
			if (mustEdgeLink.ListData[i].IsUsed == 0)
			{
				temp = temp = getDis(no, mustEdgeLink.ListData[i]);
				if (temp < minVal)
				{
					minVal = temp;
					addFlag = 1; addIndex = i;//����ؾ��ڵ�i
				}
			}
		}
		if (addFlag == 0)
		{//����ڵ�
			AddNode(addIndex);
			no = mustNodeLink.ListData[addIndex].no;
			//NodeListDelete(&mustNodeLink, addIndex);/* ɾ���ýڵ� */
			mustNodeLink.ListData[addIndex].IsUsed = 1; mustNodeLink.usedNum--;
		}
		else if (addFlag == 1)
		{//�����
			int dir;//�ߵĲ��뷽��
			dir = AddEdge(addIndex);
			if (FlagInsertDir == 0)
			{/* ��ǰѡ��Ϊͷ�� */
				if (dir == 1)
				{//�������
					no = mustEdgeLink.ListData[addIndex].no2;
				}
				else
				{//�������
					no = mustEdgeLink.ListData[addIndex].no1;
				}
			}
			else
			{/* ��ǰѡ��Ϊβ�� */
				if (dir == 1)
				{//�������
					no = mustEdgeLink.ListData[addIndex].no1;
				}
				else
				{//�������
					no = mustEdgeLink.ListData[addIndex].no2;
				}
			}
			//EdgeListDelete(&mustEdgeLink, addIndex);/* ɾ���ñ� */
			mustEdgeLink.ListData[addIndex].IsUsed = 1; mustEdgeLink.usedNum--;
		}
		if (FlagInsertDir == 0)/* ��ǰѡ��Ϊͷ�� */
		{//����ͷ�����βԪ��
			head = no;
			FlagInsertDir = 1; /* ���Ĳ��뷽�� */
		}
		else/* ��ǰѡ��Ϊβ�� */
		{//����β�ڵ���βԪ��
			tail = no;
			FlagInsertDir = 0; /* ���Ĳ��뷽�� */
		}
	}/* end while()*/
}
void RClearUsedFlag(int val)
{
	mustNodeLink.usedNum = mustNodeLink.ListLen;
	mustNodeLink.endIndex = 0;
	for (int i = 0; i <= mustNodeLink.ListLen; i++)
	{
		mustNodeLink.ListData[i].IsUsed = val;
	}
	mustEdgeLink.usedNum = mustEdgeLink.ListLen;
	mustEdgeLink.endIndex = 0;
	for (int i = 0; i <= mustEdgeLink.ListLen; i++)
	{
		mustEdgeLink.ListData[i].IsUsed = val;
	}
}
void RInitInsertLink()
{
	InsertLink->ListLen = 0;
	ListDataType ele;//�ɲ������ڵ�Ԫ��
	ele.startNo = AdjGraf.StartNode;/* ����ͷ�ڵ��β�ڵ� */
	ele.endNo = AdjGraf.EndNode;
	ele.flag = 1;
	SeqListAdd(InsertLink, ele);
}
void getNewAllMustNodeLink()
{//�ɲ�������>���бؾ��ڵ��˳�򼯺�
	int j = 0;
	for (int i = 1; i <= InsertLink->ListLen; i++)
	{
		if (InsertLink->ListData[i].startNo != InsertLink->ListData[i].endNo)
		{
			AllMustNodeOrderGather_2.p[j++] = InsertLink->ListData[i].startNo;
		}
	}
	AllMustNodeOrderGather_2.p[j++] = AdjGraf.EndNode;
	AllMustNodeOrderGather_2.num = j;

	deleteGather_2();
}
void DeleteAndPrint()
{
	AllMustNodeOrderGather_2.num = InsertLink->ListLen;
	AllMustNodeOrderGather_2.p = (int *)malloc(AllMustNodeOrderGather.num * sizeof(int));

	RInitInsertLink(); /*�ɲ��������³�ʼ��*/
	RClearUsedFlag(0);
	Set_1_Used(2); /*����ɾ��һЩ��ı��*/
	InsertNoDelete();
	getNewAllMustNodeLink();/* ��ò���ӡ���бؾ��ڵ�˳���� */
	while ((optEffect(AllMustNodeOrderGather_2) - 1) > 0)
	{
		int temp;
		AddNode(mustNodeLink.endIndex);
		temp = mustNodeLink.ListData[mustNodeLink.endIndex].InsertAddCost + 
			optEffect(AllMustNodeOrderGather_2);
		if (temp <= AdjGraf.MaxHop)
		{
			mustNodeLink.endIndex--;
			getNewAllMustNodeLink();
		}
		else
		{
			break;
		}
	}
	printf("\nɾ��һЩ�������ٴβ��롪��·������ = %d\n", optEffect(AllMustNodeOrderGather_2));
	PrintPathes(AllMustNodeOrderGather_2);

	RInitInsertLink();
	RClearUsedFlag(0);
	Set_2_Used(2);/* ����ɾ��һЩ�߱�� */
	InsertNoDelete();
	getNewAllMustNodeLink();/* ��ò���ӡ���бؾ��ڵ�˳���� */
	while ((optEffect(AllMustNodeOrderGather_2) - 1) > 0)
	{
		int temp;
		AddEdge(mustEdgeLink.endIndex);
		temp = mustEdgeLink.ListData[mustEdgeLink.endIndex].InsertAddCost +
			optEffect(AllMustNodeOrderGather_2);
		if (temp <= AdjGraf.MaxHop)
		{
			mustEdgeLink.endIndex--;
			getNewAllMustNodeLink();
		}
		else
		{
			break;
		}
	}
	printf("\nɾ��һЩ���ٴβ��롪��·������ = %d\n", optEffect(AllMustNodeOrderGather_2));
	PrintPathes(AllMustNodeOrderGather_2);
}
//Լ���������ȼ����ؾ��� < ���� < �ؾ���
void out_1()
{//�ؾ��� < ���� < �ؾ���
	RInitInsertLink(); /*�ɲ��������³�ʼ��*/
	RClearUsedFlag(0);
	Set_1_Used(2); /*����ɾ��һЩ��ı��*/
	InsertNoDelete();
	getNewAllMustNodeLink();/* ��ò���ӡ���бؾ��ڵ�˳���� */
	while ( optEffect(AllMustNodeOrderGather_2) < AdjGraf.MaxHop )
	{
		int temp;
		AddNode(mustNodeLink.endIndex);
		temp = mustNodeLink.ListData[mustNodeLink.endIndex].InsertAddCost +
			optEffect(AllMustNodeOrderGather_2);
		if (temp <= AdjGraf.MaxHop)
		{
			mustNodeLink.endIndex--;
			getNewAllMustNodeLink();
		}
		else
		{
			break;
		}
	}
	opt_2();
	deleteGather_2();

	printf("\n�� 1��Լ���������ȼ����ؾ��� < ���� < �ؾ��ߡ����������ڵ��� = %3d�� ���� = %d, �������ıؾ����� = %3d, �������ıؾ����� = %3d \n", optEffect(AllMustNodeOrderGather_2), 
		getCostFromMustOrdeLink(AllMustNodeOrderGather_2), mustNodeLink.endIndex, mustEdgeLink.endIndex);
	//PrintPathes(AllMustNodeOrderGather_2);
}
//Լ���������ȼ����ؾ��� < ���� < �ؾ���
void out_2()
{//�ؾ��� < ���� < �ؾ���
	RInitInsertLink();
	RClearUsedFlag(0);
	Set_2_Used(2);/* ����ɾ��һЩ�߱�� */
	InsertNoDelete();
	getNewAllMustNodeLink();/* ��ò���ӡ���бؾ��ڵ�˳���� */

	while (optEffect(AllMustNodeOrderGather_2) < AdjGraf.MaxHop)
	{
		int temp;
		AddEdge(mustEdgeLink.endIndex);
		temp = mustEdgeLink.ListData[mustEdgeLink.endIndex].InsertAddCost +
			optEffect(AllMustNodeOrderGather_2);
		if (temp <= AdjGraf.MaxHop)
		{
			mustEdgeLink.endIndex--;
			getNewAllMustNodeLink();
		}
		else
		{
			break;
		}
	}
	opt_2();
	deleteGather_2();

	printf("\n�� 2��Լ���������ȼ����ؾ��� < ���� < �ؾ��㡿���������ڵ��� = %3d�� ���� = %d, �������ıؾ����� = %3d, �������ıؾ����� = %3d \n", optEffect(AllMustNodeOrderGather_2), 
		getCostFromMustOrdeLink(AllMustNodeOrderGather_2), mustNodeLink.endIndex, mustEdgeLink.endIndex);
	//PrintPathes(AllMustNodeOrderGather_2);
}
//Լ���������ȼ����ؾ��� = �ؾ��� < ����
void out_3()
{//�ؾ��� < ���� < �ؾ���
	RInitInsertLink(); /*�ɲ��������³�ʼ��*/
	RClearUsedFlag(0);
	Set_3_Used(2); /*����ɾ��һЩ��ı��*/
	//Set_2_Used(2);
	InsertNoDelete();
	getNewAllMustNodeLink();/* ��ò���ӡ���бؾ��ڵ�˳���� */

	//printf("3 �����Ѿ�ɾ���㡢��ǰ����%d\n", optEffect(AllMustNodeOrderGather_2));
	while (optEffect(AllMustNodeOrderGather_2) < AdjGraf.MaxHop)
	{
		int temp,temp1,temp2;
		if ((mustNodeLink.endIndex > 0) && (mustEdgeLink.endIndex > 0))
		{
			if (mustNodeLink.ListData[mustNodeLink.endIndex].costSum <
				mustEdgeLink.ListData[mustEdgeLink.endIndex].costSum)
			{//����ڵ�
				AddNode(mustNodeLink.endIndex);
				temp1 = mustNodeLink.ListData[mustNodeLink.endIndex].InsertAddCost;
				temp = temp1 + optEffect(AllMustNodeOrderGather_2);
				if (temp <= AdjGraf.MaxHop)
				{
					mustNodeLink.endIndex--;
					getNewAllMustNodeLink();
				}
				else
				{
					break;
				}
			}
			else
			{//�����
				AddEdge(mustEdgeLink.endIndex);
				temp2 = mustEdgeLink.ListData[mustEdgeLink.endIndex].InsertAddCost;
				temp = temp2 + optEffect(AllMustNodeOrderGather_2);
				if (temp <= AdjGraf.MaxHop)
				{
					mustEdgeLink.endIndex--;
					getNewAllMustNodeLink();
				}
				else
				{
					break;
				}
			}
		}
		else if (mustNodeLink.endIndex > 0)
		{//����ڵ�
			AddNode(mustNodeLink.endIndex);
			temp1 = mustNodeLink.ListData[mustNodeLink.endIndex].InsertAddCost;
			temp = temp1 + optEffect(AllMustNodeOrderGather_2);
			if (temp <= AdjGraf.MaxHop)
			{
				mustNodeLink.endIndex--;
				getNewAllMustNodeLink();
			}
			else
			{
				break;
			}
		}
		else if (mustEdgeLink.endIndex > 0)
		{
			//�����
			AddEdge(mustEdgeLink.endIndex);
			temp2 = mustEdgeLink.ListData[mustEdgeLink.endIndex].InsertAddCost;
			temp = temp2 + optEffect(AllMustNodeOrderGather_2);
			if (temp <= AdjGraf.MaxHop)
			{
				mustEdgeLink.endIndex--;
				getNewAllMustNodeLink();
			}
			else
			{
				break;
			}
		}
		else
		{
			break;
		}
	}
	opt_2();
	deleteGather_2();

	printf("\n�� 3��Լ���������ȼ����ؾ��� = �ؾ��� < ���������������ڵ��� = %3d�� ���� = %d, �������ıؾ����� = %3d, �������ıؾ����� = %3d \n", optEffect(AllMustNodeOrderGather_2), 
		getCostFromMustOrdeLink(AllMustNodeOrderGather_2), mustNodeLink.endIndex, mustEdgeLink.endIndex);
	//PrintPathes(AllMustNodeOrderGather_2);
}
//Լ���������ȼ����ؾ��� < �ؾ��� < ����
void out_4()
{//�ؾ��㡶�ؾ��ߡ�����
	RInitInsertLink();
	RClearUsedFlag(0);
	Set_4_Used(2);/* ����ɾ��һЩ�߱�� */
	InsertNoDelete();
	getNewAllMustNodeLink();/* ��ò���ӡ���бؾ��ڵ�˳���� */

	//printf("\n�ȵ��� ����ǰ= %d\n", optEffect(AllMustNodeOrderGather_2));

	while (optEffect(AllMustNodeOrderGather_2) < AdjGraf.MaxHop)
	{
		int temp;
		if (mustEdgeLink.endIndex > 0)
		{
			AddEdge(mustEdgeLink.endIndex);
			temp = mustEdgeLink.ListData[mustEdgeLink.endIndex].InsertAddCost +
				optEffect(AllMustNodeOrderGather_2);
			if (temp <= AdjGraf.MaxHop)
			{
				mustEdgeLink.endIndex--;
				getNewAllMustNodeLink();
			}
			else
			{
				break;
			}

		}
		else
		{
			AddNode(mustNodeLink.endIndex);
			temp = mustNodeLink.ListData[mustNodeLink.endIndex].InsertAddCost +
				optEffect(AllMustNodeOrderGather_2);
			if (temp <= AdjGraf.MaxHop)
			{
				mustNodeLink.endIndex--;
				getNewAllMustNodeLink();
			}
			else
			{
				break;
			}

		}
		//	printf("\n�ȵ��� = %d\n", optEffect(AllMustNodeOrderGather_2));

	}
	opt_2();
	deleteGather_2();

	printf("\n�� 4��Լ���������ȼ����ؾ��� < �ؾ��� < ���������������ڵ��� = %3d�� ���� = %d, �������ıؾ����� = %3d, �������ıؾ����� = %3d \n", optEffect(AllMustNodeOrderGather_2), 
		getCostFromMustOrdeLink(AllMustNodeOrderGather_2), mustNodeLink.endIndex, mustEdgeLink.endIndex);
	//PrintPathes(AllMustNodeOrderGather_2);
}
//Լ���������ȼ����ؾ��� < �ؾ��� < ����
void out_5()
{//�ؾ��ߡ��ؾ��㡶����
	RInitInsertLink();
	RClearUsedFlag(0);
	Set_5_Used(2);/* ����ɾ��һЩ�߱�� */
	InsertNoDelete();
	getNewAllMustNodeLink();/* ��ò���ӡ���бؾ��ڵ�˳���� */

	//printf("\n�ȱߺ�� ����ǰ = %d\n", optEffect(AllMustNodeOrderGather_2));

	while (optEffect(AllMustNodeOrderGather_2) < AdjGraf.MaxHop)
	{
		int temp;
		if (mustNodeLink.endIndex > 0)
		{
			AddNode(mustNodeLink.endIndex);
			temp = mustNodeLink.ListData[mustNodeLink.endIndex].InsertAddCost +
				optEffect(AllMustNodeOrderGather_2);
			if (temp <= AdjGraf.MaxHop)
			{
				mustNodeLink.endIndex--;
				getNewAllMustNodeLink();
			}
			else
			{
				break;
			}
		}
		else
		{
			AddEdge(mustEdgeLink.endIndex);
			temp = mustEdgeLink.ListData[mustEdgeLink.endIndex].InsertAddCost +
				optEffect(AllMustNodeOrderGather_2);
			if (temp <= AdjGraf.MaxHop)
			{
				mustEdgeLink.endIndex--;
				getNewAllMustNodeLink();
			}
			else
			{
				break;
			}

		}
		//		printf("\n�ȱߺ�� = %d\n", optEffect(AllMustNodeOrderGather_2));
	}
	opt_2();
	deleteGather_2();

	printf("\n�� 5��Լ���������ȼ����ؾ��� < �ؾ��� < ���������������ڵ��� = %3d�� ���� = %d, �������ıؾ����� = %3d, �������ıؾ����� = %3d \n", optEffect(AllMustNodeOrderGather_2), 
		getCostFromMustOrdeLink(AllMustNodeOrderGather_2), mustNodeLink.endIndex, mustEdgeLink.endIndex);
	//PrintPathes(AllMustNodeOrderGather_2);
}
void Out()
{
	AllMustNodeOrderGather_2.num = InsertLink->ListLen;
	AllMustNodeOrderGather_2.p = (int *)malloc(AllMustNodeOrderGather.num * sizeof(int));

	out_1();
	out_2();
	out_3();
	out_4();
	out_5();
}
void shuchu_node()
{
	if (mustNodeLink.endIndex > 0)
	{
		printf("û�о����ıؾ��㣺");
		for (int i = 1; i <= mustNodeLink.endIndex; i++)
		{
			printf(" %d ", mustNodeLink.ListData[i].no);
		}
		printf("\n");
	}
}
void shuchu_edge()
{
	if (mustEdgeLink.endIndex > 0)
	{
		printf("û�о����ıؾ��ߣ�");
		for (int i = 1; i <= mustEdgeLink.endIndex; i++)
		{
			printf(" %d-%d ", mustEdgeLink.ListData[i].no1, mustEdgeLink.ListData[i].no2);
		}
		printf("\n");
	}
}
//Լ���������ȼ����ؾ��� < ���� < �ؾ���
void out_1_path()
{//�ؾ��� < ���� < �ؾ���
	RInitInsertLink(); /*�ɲ��������³�ʼ��*/
	RClearUsedFlag(0);
	Set_1_Used(2); /*����ɾ��һЩ��ı��*/
	InsertNoDelete();
	getNewAllMustNodeLink();/* ��ò���ӡ���бؾ��ڵ�˳���� */
	while (optEffect(AllMustNodeOrderGather_2) < AdjGraf.MaxHop)
	{
		int temp;
		AddNode(mustNodeLink.endIndex);
		temp = mustNodeLink.ListData[mustNodeLink.endIndex].InsertAddCost +
			optEffect(AllMustNodeOrderGather_2);
		if (temp <= AdjGraf.MaxHop)
		{
			mustNodeLink.endIndex--;
			getNewAllMustNodeLink();
		}
		else
		{
			break;
		}
	}
	opt_2();
	deleteGather_2();
	
	printf("\n�� 1��Լ���������ȼ����ؾ��� < ���� < �ؾ��ߡ����������ڵ��� = %3d�� ���� = %d, �������ıؾ����� = %3d, �������ıؾ����� = %3d \n", optEffect(AllMustNodeOrderGather_2),
		getCostFromMustOrdeLink(AllMustNodeOrderGather_2), mustNodeLink.endIndex, mustEdgeLink.endIndex);

	shuchu_node();
	PrintPathes(AllMustNodeOrderGather_2);
}
//Լ���������ȼ����ؾ��� < ���� < �ؾ���
void out_2_path()
{//�ؾ��� < ���� < �ؾ���
	RInitInsertLink();
	RClearUsedFlag(0);
	Set_2_Used(2);/* ����ɾ��һЩ�߱�� */
	InsertNoDelete();
	getNewAllMustNodeLink();/* ��ò���ӡ���бؾ��ڵ�˳���� */
	while (optEffect(AllMustNodeOrderGather_2) < AdjGraf.MaxHop)
	{
		int temp;
		AddEdge(mustEdgeLink.endIndex);
		temp = mustEdgeLink.ListData[mustEdgeLink.endIndex].InsertAddCost +
			optEffect(AllMustNodeOrderGather_2);
		if (temp <= AdjGraf.MaxHop)
		{
			mustEdgeLink.endIndex--;
			getNewAllMustNodeLink();
		}
		else
		{
			break;
		}
	}
	opt_2();
	deleteGather_2();
	
	printf("\n�� 2��Լ���������ȼ����ؾ��� < ���� < �ؾ��㡿���������ڵ��� = %3d�� ���� = %d, �������ıؾ����� = %3d, �������ıؾ����� = %3d \n", optEffect(AllMustNodeOrderGather_2),
		getCostFromMustOrdeLink(AllMustNodeOrderGather_2), mustNodeLink.endIndex, mustEdgeLink.endIndex);
	shuchu_edge();
	PrintPathes(AllMustNodeOrderGather_2);
}
//Լ���������ȼ����ؾ��� = �ؾ��� < ����
void out_3_path()
{//�ؾ��� < ���� < �ؾ���
	RInitInsertLink(); /*�ɲ��������³�ʼ��*/
	RClearUsedFlag(0);
	Set_3_Used(2); /*����ɾ��һЩ��ı��*/
				   //Set_2_Used(2);
	InsertNoDelete();
	getNewAllMustNodeLink();/* ��ò���ӡ���бؾ��ڵ�˳���� */
							//printf("3 �����Ѿ�ɾ���㡢��ǰ����%d\n", optEffect(AllMustNodeOrderGather_2));
	while (optEffect(AllMustNodeOrderGather_2) < AdjGraf.MaxHop)
	{
		int temp, temp1, temp2;
		if ((mustNodeLink.endIndex > 0) && (mustEdgeLink.endIndex > 0))
		{
			if (mustNodeLink.ListData[mustNodeLink.endIndex].costSum <
				mustEdgeLink.ListData[mustEdgeLink.endIndex].costSum)
			{//����ڵ�
				AddNode(mustNodeLink.endIndex);
				temp1 = mustNodeLink.ListData[mustNodeLink.endIndex].InsertAddCost;
				temp = temp1 + optEffect(AllMustNodeOrderGather_2);
				if (temp <= AdjGraf.MaxHop)
				{
					mustNodeLink.endIndex--;
					getNewAllMustNodeLink();
				}
				else
				{
					break;
				}
			}
			else
			{//�����
				AddEdge(mustEdgeLink.endIndex);
				temp2 = mustEdgeLink.ListData[mustEdgeLink.endIndex].InsertAddCost;
				temp = temp2 + optEffect(AllMustNodeOrderGather_2);
				if (temp <= AdjGraf.MaxHop)
				{
					mustEdgeLink.endIndex--;
					getNewAllMustNodeLink();
				}
				else
				{
					break;
				}
			}
		}
		else if (mustNodeLink.endIndex > 0)
		{//����ڵ�
			AddNode(mustNodeLink.endIndex);
			temp1 = mustNodeLink.ListData[mustNodeLink.endIndex].InsertAddCost;
			temp = temp1 + optEffect(AllMustNodeOrderGather_2);
			if (temp <= AdjGraf.MaxHop)
			{
				mustNodeLink.endIndex--;
				getNewAllMustNodeLink();
			}
			else
			{
				break;
			}
		}
		else if (mustEdgeLink.endIndex > 0)
		{
			//�����
			AddEdge(mustEdgeLink.endIndex);
			temp2 = mustEdgeLink.ListData[mustEdgeLink.endIndex].InsertAddCost;
			temp = temp2 + optEffect(AllMustNodeOrderGather_2);
			if (temp <= AdjGraf.MaxHop)
			{
				mustEdgeLink.endIndex--;
				getNewAllMustNodeLink();
			}
			else
			{
				break;
			}
		}
		else
		{
			break;
		}
	}
	opt_2();
	deleteGather_2();
	
	printf("\n�� 3��Լ���������ȼ����ؾ��� = �ؾ��� < ���������������ڵ��� = %3d�� ���� = %d, �������ıؾ����� = %3d, �������ıؾ����� = %3d \n", optEffect(AllMustNodeOrderGather_2),
		getCostFromMustOrdeLink(AllMustNodeOrderGather_2), mustNodeLink.endIndex, mustEdgeLink.endIndex);
	shuchu_node();
	shuchu_edge();
	PrintPathes(AllMustNodeOrderGather_2);
}
//Լ���������ȼ����ؾ��� < �ؾ��� < ����
void out_4_path()
{//�ؾ��㡶�ؾ��ߡ�����
	RInitInsertLink();
	RClearUsedFlag(0);
	Set_4_Used(2);/* ����ɾ��һЩ�߱�� */
	InsertNoDelete();
	getNewAllMustNodeLink();/* ��ò���ӡ���бؾ��ڵ�˳���� */
							//printf("\n�ȵ��� ����ǰ= %d\n", optEffect(AllMustNodeOrderGather_2));

	while (optEffect(AllMustNodeOrderGather_2) < AdjGraf.MaxHop)
	{
		int temp;
		if (mustEdgeLink.endIndex > 0)
		{
			AddEdge(mustEdgeLink.endIndex);
			temp = mustEdgeLink.ListData[mustEdgeLink.endIndex].InsertAddCost +
				optEffect(AllMustNodeOrderGather_2);
			if (temp <= AdjGraf.MaxHop)
			{
				mustEdgeLink.endIndex--;
				getNewAllMustNodeLink();
			}
			else
			{
				break;
			}

		}
		else
		{
			AddNode(mustNodeLink.endIndex);
			temp = mustNodeLink.ListData[mustNodeLink.endIndex].InsertAddCost +
				optEffect(AllMustNodeOrderGather_2);
			if (temp <= AdjGraf.MaxHop)
			{
				mustNodeLink.endIndex--;
				getNewAllMustNodeLink();
			}
			else
			{
				break;
			}

		}
		//	printf("\n�ȵ��� = %d\n", optEffect(AllMustNodeOrderGather_2));

	}
	opt_2();
	deleteGather_2();
	
	printf("\n�� 4��Լ���������ȼ����ؾ��� < �ؾ��� < ���������������ڵ��� = %3d�� ���� = %d, �������ıؾ����� = %3d, �������ıؾ����� = %3d \n", optEffect(AllMustNodeOrderGather_2),
		getCostFromMustOrdeLink(AllMustNodeOrderGather_2), mustNodeLink.endIndex, mustEdgeLink.endIndex);
	shuchu_node();
	shuchu_edge();
	PrintPathes(AllMustNodeOrderGather_2);
}
//Լ���������ȼ����ؾ��� < �ؾ��� < ����
void out_5_path()
{//�ؾ��ߡ��ؾ��㡶����
	RInitInsertLink();
	RClearUsedFlag(0);
	Set_5_Used(2);/* ����ɾ��һЩ�߱�� */
	InsertNoDelete();
	getNewAllMustNodeLink();/* ��ò���ӡ���бؾ��ڵ�˳���� */
							//printf("\n�ȱߺ�� ����ǰ = %d\n", optEffect(AllMustNodeOrderGather_2));

	while (optEffect(AllMustNodeOrderGather_2) < AdjGraf.MaxHop)
	{
		int temp;
		if (mustNodeLink.endIndex > 0)
		{
			AddNode(mustNodeLink.endIndex);
			temp = mustNodeLink.ListData[mustNodeLink.endIndex].InsertAddCost +
				optEffect(AllMustNodeOrderGather_2);
			if (temp <= AdjGraf.MaxHop)
			{
				mustNodeLink.endIndex--;
				getNewAllMustNodeLink();
			}
			else
			{
				break;
			}
		}
		else
		{
			AddEdge(mustEdgeLink.endIndex);
			temp = mustEdgeLink.ListData[mustEdgeLink.endIndex].InsertAddCost +
				optEffect(AllMustNodeOrderGather_2);
			if (temp <= AdjGraf.MaxHop)
			{
				mustEdgeLink.endIndex--;
				getNewAllMustNodeLink();
			}
			else
			{
				break;
			}

		}
		//		printf("\n�ȱߺ�� = %d\n", optEffect(AllMustNodeOrderGather_2));
	}
	opt_2();
	deleteGather_2();
	
	printf("\n�� 5��Լ���������ȼ����ؾ��� < �ؾ��� < ���������������ڵ��� = %3d�� ���� = %d, �������ıؾ����� = %3d, �������ıؾ����� = %3d \n", optEffect(AllMustNodeOrderGather_2),
		getCostFromMustOrdeLink(AllMustNodeOrderGather_2), mustNodeLink.endIndex, mustEdgeLink.endIndex);
	shuchu_node();
	shuchu_edge();
	PrintPathes(AllMustNodeOrderGather_2);
}
void out_6_path()
{
	int hop_2opt = optEffect(AllMustNodeOrderGather);
	printf("\n�� 6��Լ���������ȼ������� < �ؾ��� / �ؾ��㡿���������ڵ��� = %3d�� ���� = %d, �������ıؾ����� = %3d, �������ıؾ����� = %3d \n", hop_2opt,
		getCostFromMustOrdeLink(AllMustNodeOrderGather), 0, 0);
	PrintPathes(AllMustNodeOrderGather);
}
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
//约束条件优先级：必经点 < 跳数 < 必经边
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
//约束条件优先级：必经边 < 跳数 < 必经点
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
//约束条件优先级：必经边 = 必经点 < 跳数
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
		{//选择删除一个必经点
			sum += max1;
			mustNodeLink.endIndex++;
			mustNodeLink.ListData[mustNodeLink.endIndex].IsUsed = val;
		}
		else if (max1 < max2)
		{//选择删除一条必经边
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
//约束条件优先级：必经点 < 必经边 < 跳数
void Set_4_Used(int val)
{
	//必经点《必经边《跳数
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
//约束条件优先级：必经边 < 必经点 < 跳数
void Set_5_Used(int val)
{
	//必经边《必经点《跳数
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
{//插入一条边或者一个节点——邻近+节省插入法
	int temp;
	int head, tail, no;

	int FlagInsertDir = 0; /* no = 头 / 尾节点链尾元素*/
	head = AdjGraf.StartNode;
	tail = AdjGraf.EndNode;

	while ((mustEdgeLink.usedNum > 0) || (mustNodeLink.usedNum > 0))
	{
		int minVal = MAX_VALUE;//保存最小跳数
		int addFlag, addIndex;

		if (FlagInsertDir == 0)	no = head;
		else	                no = tail;

		for (int i = 1; i <= mustNodeLink.ListLen; i++)
		{//获取节点 no 到 必经节点的的最小跳数和该必经节点编号
			if (mustNodeLink.ListData[i].IsUsed == 0)
			{
				temp = pPathMatrix[getPos(no)*gatherNode.num
					+ getPos(mustNodeLink.ListData[i].no)].LayerNum;
				if (temp < minVal)
				{
					minVal = temp;
					addFlag = 0; addIndex = i;//加入必经节点i
				}
			}
		}
		for (int i = 1; i <= mustEdgeLink.ListLen; i++)
		{//获取节点 no 到 必经边的的最小跳数和该必经边编号
			if (mustEdgeLink.ListData[i].IsUsed == 0)
			{
				temp = temp = getDis(no, mustEdgeLink.ListData[i]);
				if (temp < minVal)
				{
					minVal = temp;
					addFlag = 1; addIndex = i;//加入必经节点i
				}
			}
		}
		if (addFlag == 0)
		{//加入节点
			AddNode(addIndex);
			no = mustNodeLink.ListData[addIndex].no;
			//NodeListDelete(&mustNodeLink, addIndex);/* 删除该节点 */
			mustNodeLink.ListData[addIndex].IsUsed = 1; mustNodeLink.usedNum--;
		}
		else if (addFlag == 1)
		{//加入边
			int dir;//边的插入方向
			dir = AddEdge(addIndex);
			if (FlagInsertDir == 0)
			{/* 当前选择为头链 */
				if (dir == 1)
				{//正向插入
					no = mustEdgeLink.ListData[addIndex].no2;
				}
				else
				{//反向插入
					no = mustEdgeLink.ListData[addIndex].no1;
				}
			}
			else
			{/* 当前选择为尾链 */
				if (dir == 1)
				{//正向插入
					no = mustEdgeLink.ListData[addIndex].no1;
				}
				else
				{//反向插入
					no = mustEdgeLink.ListData[addIndex].no2;
				}
			}
			//EdgeListDelete(&mustEdgeLink, addIndex);/* 删除该边 */
			mustEdgeLink.ListData[addIndex].IsUsed = 1; mustEdgeLink.usedNum--;
		}
		if (FlagInsertDir == 0)/* 当前选择为头链 */
		{//更新头结点链尾元素
			head = no;
			FlagInsertDir = 1; /* 更改插入方向 */
		}
		else/* 当前选择为尾链 */
		{//更新尾节点链尾元素
			tail = no;
			FlagInsertDir = 0; /* 更改插入方向 */
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
	ListDataType ele;//可插入链节点元素
	ele.startNo = AdjGraf.StartNode;/* 加入头节点和尾节点 */
	ele.endNo = AdjGraf.EndNode;
	ele.flag = 1;
	SeqListAdd(InsertLink, ele);
}
void getNewAllMustNodeLink()
{//可插入链—>所有必经节点的顺序集合
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

	RInitInsertLink(); /*可插入链重新初始化*/
	RClearUsedFlag(0);
	Set_1_Used(2); /*设置删除一些点的标记*/
	InsertNoDelete();
	getNewAllMustNodeLink();/* 获得并打印所有必经节点顺序链 */
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
	printf("\n删除一些点点点点点再次插入——路径跳数 = %d\n", optEffect(AllMustNodeOrderGather_2));
	PrintPathes(AllMustNodeOrderGather_2);

	RInitInsertLink();
	RClearUsedFlag(0);
	Set_2_Used(2);/* 设置删除一些边标记 */
	InsertNoDelete();
	getNewAllMustNodeLink();/* 获得并打印所有必经节点顺序链 */
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
	printf("\n删除一些边再次插入——路径跳数 = %d\n", optEffect(AllMustNodeOrderGather_2));
	PrintPathes(AllMustNodeOrderGather_2);
}
//约束条件优先级：必经点 < 跳数 < 必经边
void out_1()
{//必经点 < 跳数 < 必经边
	RInitInsertLink(); /*可插入链重新初始化*/
	RClearUsedFlag(0);
	Set_1_Used(2); /*设置删除一些点的标记*/
	InsertNoDelete();
	getNewAllMustNodeLink();/* 获得并打印所有必经节点顺序链 */
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

	printf("\n【 1、约束条件优先级：必经点 < 跳数 < 必经边】——经过节点数 = %3d， 花费 = %d, 不经过的必经点数 = %3d, 不经过的必经边数 = %3d \n", optEffect(AllMustNodeOrderGather_2), 
		getCostFromMustOrdeLink(AllMustNodeOrderGather_2), mustNodeLink.endIndex, mustEdgeLink.endIndex);
	//PrintPathes(AllMustNodeOrderGather_2);
}
//约束条件优先级：必经边 < 跳数 < 必经点
void out_2()
{//必经边 < 跳数 < 必经点
	RInitInsertLink();
	RClearUsedFlag(0);
	Set_2_Used(2);/* 设置删除一些边标记 */
	InsertNoDelete();
	getNewAllMustNodeLink();/* 获得并打印所有必经节点顺序链 */

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

	printf("\n【 2、约束条件优先级：必经边 < 跳数 < 必经点】——经过节点数 = %3d， 花费 = %d, 不经过的必经点数 = %3d, 不经过的必经边数 = %3d \n", optEffect(AllMustNodeOrderGather_2), 
		getCostFromMustOrdeLink(AllMustNodeOrderGather_2), mustNodeLink.endIndex, mustEdgeLink.endIndex);
	//PrintPathes(AllMustNodeOrderGather_2);
}
//约束条件优先级：必经边 = 必经点 < 跳数
void out_3()
{//必经点 < 跳数 < 必经边
	RInitInsertLink(); /*可插入链重新初始化*/
	RClearUsedFlag(0);
	Set_3_Used(2); /*设置删除一些点的标记*/
	//Set_2_Used(2);
	InsertNoDelete();
	getNewAllMustNodeLink();/* 获得并打印所有必经节点顺序链 */

	//printf("3 加入已经删除点、边前——%d\n", optEffect(AllMustNodeOrderGather_2));
	while (optEffect(AllMustNodeOrderGather_2) < AdjGraf.MaxHop)
	{
		int temp,temp1,temp2;
		if ((mustNodeLink.endIndex > 0) && (mustEdgeLink.endIndex > 0))
		{
			if (mustNodeLink.ListData[mustNodeLink.endIndex].costSum <
				mustEdgeLink.ListData[mustEdgeLink.endIndex].costSum)
			{//加入节点
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
			{//加入边
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
		{//加入节点
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
			//加入边
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

	printf("\n【 3、约束条件优先级：必经边 = 必经点 < 跳数】——经过节点数 = %3d， 花费 = %d, 不经过的必经点数 = %3d, 不经过的必经边数 = %3d \n", optEffect(AllMustNodeOrderGather_2), 
		getCostFromMustOrdeLink(AllMustNodeOrderGather_2), mustNodeLink.endIndex, mustEdgeLink.endIndex);
	//PrintPathes(AllMustNodeOrderGather_2);
}
//约束条件优先级：必经点 < 必经边 < 跳数
void out_4()
{//必经点《必经边《跳数
	RInitInsertLink();
	RClearUsedFlag(0);
	Set_4_Used(2);/* 设置删除一些边标记 */
	InsertNoDelete();
	getNewAllMustNodeLink();/* 获得并打印所有必经节点顺序链 */

	//printf("\n先点后边 插入前= %d\n", optEffect(AllMustNodeOrderGather_2));

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
		//	printf("\n先点后边 = %d\n", optEffect(AllMustNodeOrderGather_2));

	}
	opt_2();
	deleteGather_2();

	printf("\n【 4、约束条件优先级：必经点 < 必经边 < 跳数】——经过节点数 = %3d， 花费 = %d, 不经过的必经点数 = %3d, 不经过的必经边数 = %3d \n", optEffect(AllMustNodeOrderGather_2), 
		getCostFromMustOrdeLink(AllMustNodeOrderGather_2), mustNodeLink.endIndex, mustEdgeLink.endIndex);
	//PrintPathes(AllMustNodeOrderGather_2);
}
//约束条件优先级：必经边 < 必经点 < 跳数
void out_5()
{//必经边《必经点《跳数
	RInitInsertLink();
	RClearUsedFlag(0);
	Set_5_Used(2);/* 设置删除一些边标记 */
	InsertNoDelete();
	getNewAllMustNodeLink();/* 获得并打印所有必经节点顺序链 */

	//printf("\n先边后点 加入前 = %d\n", optEffect(AllMustNodeOrderGather_2));

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
		//		printf("\n先边后点 = %d\n", optEffect(AllMustNodeOrderGather_2));
	}
	opt_2();
	deleteGather_2();

	printf("\n【 5、约束条件优先级：必经边 < 必经点 < 跳数】——经过节点数 = %3d， 花费 = %d, 不经过的必经点数 = %3d, 不经过的必经边数 = %3d \n", optEffect(AllMustNodeOrderGather_2), 
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
		printf("没有经过的必经点：");
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
		printf("没有经过的必经边：");
		for (int i = 1; i <= mustEdgeLink.endIndex; i++)
		{
			printf(" %d-%d ", mustEdgeLink.ListData[i].no1, mustEdgeLink.ListData[i].no2);
		}
		printf("\n");
	}
}
//约束条件优先级：必经点 < 跳数 < 必经边
void out_1_path()
{//必经点 < 跳数 < 必经边
	RInitInsertLink(); /*可插入链重新初始化*/
	RClearUsedFlag(0);
	Set_1_Used(2); /*设置删除一些点的标记*/
	InsertNoDelete();
	getNewAllMustNodeLink();/* 获得并打印所有必经节点顺序链 */
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
	
	printf("\n【 1、约束条件优先级：必经点 < 跳数 < 必经边】——经过节点数 = %3d， 花费 = %d, 不经过的必经点数 = %3d, 不经过的必经边数 = %3d \n", optEffect(AllMustNodeOrderGather_2),
		getCostFromMustOrdeLink(AllMustNodeOrderGather_2), mustNodeLink.endIndex, mustEdgeLink.endIndex);

	shuchu_node();
	PrintPathes(AllMustNodeOrderGather_2);
}
//约束条件优先级：必经边 < 跳数 < 必经点
void out_2_path()
{//必经边 < 跳数 < 必经点
	RInitInsertLink();
	RClearUsedFlag(0);
	Set_2_Used(2);/* 设置删除一些边标记 */
	InsertNoDelete();
	getNewAllMustNodeLink();/* 获得并打印所有必经节点顺序链 */
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
	
	printf("\n【 2、约束条件优先级：必经边 < 跳数 < 必经点】——经过节点数 = %3d， 花费 = %d, 不经过的必经点数 = %3d, 不经过的必经边数 = %3d \n", optEffect(AllMustNodeOrderGather_2),
		getCostFromMustOrdeLink(AllMustNodeOrderGather_2), mustNodeLink.endIndex, mustEdgeLink.endIndex);
	shuchu_edge();
	PrintPathes(AllMustNodeOrderGather_2);
}
//约束条件优先级：必经边 = 必经点 < 跳数
void out_3_path()
{//必经点 < 跳数 < 必经边
	RInitInsertLink(); /*可插入链重新初始化*/
	RClearUsedFlag(0);
	Set_3_Used(2); /*设置删除一些点的标记*/
				   //Set_2_Used(2);
	InsertNoDelete();
	getNewAllMustNodeLink();/* 获得并打印所有必经节点顺序链 */
							//printf("3 加入已经删除点、边前——%d\n", optEffect(AllMustNodeOrderGather_2));
	while (optEffect(AllMustNodeOrderGather_2) < AdjGraf.MaxHop)
	{
		int temp, temp1, temp2;
		if ((mustNodeLink.endIndex > 0) && (mustEdgeLink.endIndex > 0))
		{
			if (mustNodeLink.ListData[mustNodeLink.endIndex].costSum <
				mustEdgeLink.ListData[mustEdgeLink.endIndex].costSum)
			{//加入节点
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
			{//加入边
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
		{//加入节点
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
			//加入边
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
	
	printf("\n【 3、约束条件优先级：必经边 = 必经点 < 跳数】——经过节点数 = %3d， 花费 = %d, 不经过的必经点数 = %3d, 不经过的必经边数 = %3d \n", optEffect(AllMustNodeOrderGather_2),
		getCostFromMustOrdeLink(AllMustNodeOrderGather_2), mustNodeLink.endIndex, mustEdgeLink.endIndex);
	shuchu_node();
	shuchu_edge();
	PrintPathes(AllMustNodeOrderGather_2);
}
//约束条件优先级：必经点 < 必经边 < 跳数
void out_4_path()
{//必经点《必经边《跳数
	RInitInsertLink();
	RClearUsedFlag(0);
	Set_4_Used(2);/* 设置删除一些边标记 */
	InsertNoDelete();
	getNewAllMustNodeLink();/* 获得并打印所有必经节点顺序链 */
							//printf("\n先点后边 插入前= %d\n", optEffect(AllMustNodeOrderGather_2));

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
		//	printf("\n先点后边 = %d\n", optEffect(AllMustNodeOrderGather_2));

	}
	opt_2();
	deleteGather_2();
	
	printf("\n【 4、约束条件优先级：必经点 < 必经边 < 跳数】——经过节点数 = %3d， 花费 = %d, 不经过的必经点数 = %3d, 不经过的必经边数 = %3d \n", optEffect(AllMustNodeOrderGather_2),
		getCostFromMustOrdeLink(AllMustNodeOrderGather_2), mustNodeLink.endIndex, mustEdgeLink.endIndex);
	shuchu_node();
	shuchu_edge();
	PrintPathes(AllMustNodeOrderGather_2);
}
//约束条件优先级：必经边 < 必经点 < 跳数
void out_5_path()
{//必经边《必经点《跳数
	RInitInsertLink();
	RClearUsedFlag(0);
	Set_5_Used(2);/* 设置删除一些边标记 */
	InsertNoDelete();
	getNewAllMustNodeLink();/* 获得并打印所有必经节点顺序链 */
							//printf("\n先边后点 加入前 = %d\n", optEffect(AllMustNodeOrderGather_2));

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
		//		printf("\n先边后点 = %d\n", optEffect(AllMustNodeOrderGather_2));
	}
	opt_2();
	deleteGather_2();
	
	printf("\n【 5、约束条件优先级：必经边 < 必经点 < 跳数】——经过节点数 = %3d， 花费 = %d, 不经过的必经点数 = %3d, 不经过的必经边数 = %3d \n", optEffect(AllMustNodeOrderGather_2),
		getCostFromMustOrdeLink(AllMustNodeOrderGather_2), mustNodeLink.endIndex, mustEdgeLink.endIndex);
	shuchu_node();
	shuchu_edge();
	PrintPathes(AllMustNodeOrderGather_2);
}
void out_6_path()
{
	int hop_2opt = optEffect(AllMustNodeOrderGather);
	printf("\n【 6、约束条件优先级：跳数 < 必经边 / 必经点】——经过节点数 = %3d， 花费 = %d, 不经过的必经点数 = %3d, 不经过的必经边数 = %3d \n", hop_2opt,
		getCostFromMustOrdeLink(AllMustNodeOrderGather), 0, 0);
	PrintPathes(AllMustNodeOrderGather);
}
#pragma once

//约束条件优先级：必经点 < 跳数 < 必经边
void Set_1_Used(int val);
//约束条件优先级：必经边 < 跳数 < 必经点
void Set_2_Used(int val);
//约束条件优先级：必经边 = 必经点 < 跳数
void Set_3_Used(int val);
//约束条件优先级：必经点 < 必经边 < 跳数
void Set_4_Used(int val);
//约束条件优先级：必经边 < 必经点 < 跳数
void Set_5_Used(int val);
void InsertNoDelete();
void RClearUsedFlag(int val);
void RInitInsertLink();
void getNewAllMustNodeLink();
void DeleteAndPrint();
//约束条件优先级：必经点 < 跳数 < 必经边
void out_1();
//约束条件优先级：必经边 < 跳数 < 必经点
void out_2();
//约束条件优先级：必经边 = 必经点 < 跳数
void out_3();
//约束条件优先级：必经点 < 必经边 < 跳数
void out_4();
//约束条件优先级：必经边 < 必经点 < 跳数
void out_5();
void Out();
//约束条件优先级：必经点 < 跳数 < 必经边
void out_1_path();
//约束条件优先级：必经边 < 跳数 < 必经点
void out_2_path();
//约束条件优先级：必经边 = 必经点 < 跳数
void out_3_path();
//约束条件优先级：必经点 < 必经边 < 跳数
void out_4_path();
//约束条件优先级：必经边 < 必经点 < 跳数
void out_5_path();
void out_6_path();
void shuchu_node();
void shuchu_edge();

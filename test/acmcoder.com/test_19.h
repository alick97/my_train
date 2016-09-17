#pragma once 




/*


装载乘客
题目描述
X学校最近组织了一场春游踏青活动，向Y公司租赁汽车运输学生。这次参加活动的总共有n个班级，第i班总共有ai名学生，每辆车最大乘车人数为m，满足m>a1, a2, ..., an。乘车时必须按照班级排列顺序进行乘车，不能调整班级顺序进行拼车。为保证同一个班级的学生在同一辆车上，如果当前汽车装完上一个班级后，下一个班级所有同学无法装下，那么当前车开走使用下一辆车。问最少需要多少辆车才能把所有学生运完？
输入
第一行数据是两个整数：n, m (1≤n,m≤100)，n表示班级数目，m表示汽车最大装载人数。接下来n行是数据表示每个班级的人数数字a1, a2, ..., an (1≤ai≤m)。
样例输入
4 3
2 3 2 1

输出
输出需要的汽车数目。
样例输出
3


*/#include <iostream>
using namespace std;
int get_count(int n, int m, int arr[])
{
    int count = 0;
   int i = 0;
   while (i < n)
   {
       int tmp = 0;
       while (tmp < m && i < n)
       {
           tmp += arr[i];
           i++;
       }

       if (tmp > m)
       {
           i--;
       }
      count++;
   }

   return count;
}


void test_19()
{

    int n,m;
    int arr[1000];
    while (cin>>n>>m)
    {
        for (int i = 0; i < n; i++)
        {
            cin>>arr[i];
        }
        cout<<get_count(n,m ,arr)<<endl;
    }

}
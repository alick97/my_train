#pragma once

#include <iostream>
using namespace std;


/*

公交车乘客
题目描述
一个公交车经过n个站点，乘客从前门上车，从后门下车。
现在统计了在第i个站，下车人数a[i]，以及上车人数b[i]。
问公交车运行时候车上最多有多少乘客
输入
第一行读入一个整数n(1<=n<=100)，表示有n个站点
接下来n行，每行两个数值，分别表示在第i个站点下车人数和上车人数
样例输入
4
0 3
2 5
4 2
4 0
输出
每组输出车上最多的乘客数目
样例输出
6

*/

int get_max_people(int (*p)[2], int n)
{
    int max = 0;
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        count += p[i][1] - p[i][0];
        if (max < count)
        {max = count;}
    }

    return max;
}

void test_get_max_people()
{
    int arr[100][2];
    int n;
    while (cin>>n)
    {
       for (int i = 0; i < n; i++)
       {
          cin>>arr[i][0]>>arr[i][1];
       }
       cout<<get_max_people(arr, n)<<endl;
    }
}




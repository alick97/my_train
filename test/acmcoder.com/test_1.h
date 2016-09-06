#pragma once
#include <iostream>
using namespace std;

/*

    题目描述
    有股神吗？
    有，小赛就是！
    经过严密的计算，小赛买了一支股票，他知道从他买股票的那天开始，股票会有以下变化：第一天不变，以后涨一天，跌一天，涨两天，跌一天，涨三天，跌一天...依此类推。
    为方便计算，假设每次涨和跌皆为1，股票初始单价也为1，请计算买股票的第n天每股股票值多少钱？
    输入
    输入包括多组数据；
    每行输入一个n，1<=n<=10^9 。
    样例输入
    1
    2
    3
    4
    5
    输出
    请输出他每股股票多少钱，对于每组数据，输出一行。
    样例输出
    1
    2
    1
    2
    3

*/
#include <vector>

// 数据多 内存超出  acmcoder.com测试通过率50% 
//vector<int> v;
//int getmoney(int n)
//{
//    int money = 0;
//    int index = 0;
//    v.resize(100);
//    v[index++] = 1;
//    int prev = 1;
//    int tag = 1;
//  while (index != n)
//  {
//      if (tag > 0)
//      {
//          v[index++] = 1;
//          tag--;
//      }
//      else
//      {
//          v[index++] = -1;
//          prev = prev + 1;
//          tag = prev;
//      }
//  }
//  for (int i = 0; i < n; i++)
//  {
//      money += v[i];
//  }
//
//
//    return money;
//
//}


int getmoney(int n)
{
    int money = 1;
    int i = 1;
    int count = 1;

    for (i = 2; ; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            if (j !=i)
            {
                money += 1;
            }
            else
            {
                money--;
            }
            count++;
            if (count == n)
            {
                return money;
            }

        }

    }

    return 1;

}


void test_1()
{
    int n;
    while (cin>>n)
    {
        cout<<getmoney(n)<<endl;
    }

}

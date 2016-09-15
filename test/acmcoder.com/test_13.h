#pragma once


/*


研究生考试
题目描述
欢迎大家参加奇虎360 2016校招在线招聘考试，首先预祝大家都有个好成绩!
我相信参加本次在线招聘考试的有不少研究生同学。我们知道，就计算机相关专业来说，考研有4门科目，分别是政治（满分100分），英语（满分100分），数学（满分150分）和专业课（满分150分）。
某校计算机专业今年录取研究生的要求是：政治、英语每门课成绩不低于60分，数学和专业课不低于90分，总成绩不低于310分。并且规定：在满足单科以及总成绩最低要求的基础上，350分以上（含350分）为公费（Gongfei），310分~349分为自费(Zifei)。
请编程判断考生的录取情况。

输入
输入数据首先包括一个正整数N，表示有N组测试数据。
每组数据包含4个正整数，分别表示考生的四门课成绩（顺序为：政治、英语、数学、专业课），你可以假设所有的分数数据都合法。
样例输入
3
61 62 100 120
80 80 120 100
55 90 130 130

输出
请输出每组数据对应考生的录取情况（Fail/Zifei/Gongfei）。

样例输出
Zifei
Gongfei
Fail


*/
#include <iostream>
using namespace std;

void Print_admit(int (*p)[4], int n)
{
    for (int i = 0; i < n ; i++)
    {
       if (p[i][0] >= 60 && p[i][1] >= 60 && p[i][2] >= 90 && p[i][3] >= 90)
       {
           int count = 0;
           for (int j = 0; j < 4; j++)
           {
            count += p[i][j];
           }

           if (count >= 350)
           {
             cout<<"Gongfei"<<endl;
           }
           else if (count >= 310)
           {
            cout<<"Zifei"<<endl;
           }
           else
           {
               cout<<"Fail"<<endl;
           }


       }
       else
       {
       cout<<"Fail"<<endl;
       }
    }

}

void test_13()
{
    int n;
    int arr[1000][4];
    while (cin>>n)
    {
       for (int i = 0; i < n; i++)
       {
         for (int j = 0; j < 4; j++)
         {
           cin>>arr[i][j];
         }
       }

      
        Print_admit(arr, n);
       
    }
}


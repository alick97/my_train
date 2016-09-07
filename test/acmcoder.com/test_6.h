#pragma once

/*

上台阶
题目描述
有一楼梯共m级，刚开始时你在第一级，若每次只能跨上一级或二级，要走上第m级，共有多少走法？
注：规定从一级到一级有0种走法。
输入
输入数据首先包含一个整数n(1<=n<=100)，表示测试实例的个数，然后是n行数据，每行包含一个整数m，（1<=m<=40), 表示楼梯的级数。
样例输入
2
2
3
输出
对于每个测试实例，请输出不同走法的数量。
样例输出
1
2


*/

#include <iostream>
using namespace std;

int get_method(int n)
{
    if (n == 1)
    {
        return 0;
    }

    if (n == 2)
    {
        return 1;
    }
    if (n == 3)
    {
        return 2;
    }
    int method_count = 0;
    int prev1 = 1;
    int prev2 = 2;
    for (int i = 4; i <= n; i++)
    {     
        method_count = prev1 + prev2;
        prev1 = prev2;
        prev2 = method_count;
    }

    return method_count;
}

void test_6()
{
    int n;
    while (cin>>n)
    {
      int t;
      for (int i = 0; i < n; i++)
      {
      cin>>t;
         cout<<get_method(t)<<endl;
      }
       
    }

}

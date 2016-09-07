#pragma once

#include <iostream>
using namespace std;



/*****

题目描述
果园里有堆苹果，N（1＜N＜9）只熊来分。第一只熊把这堆苹果平均分为N份，多了一个，它把多的一个扔了，拿走了一份。第二只熊把剩下的苹果又平均分成N份，又多了一个，它同样把多的一个扔了，拿走了一份，第三、第四直到第N只熊都是这么做的，问果园里原来[最少]有多少个苹果？

输入
输入1个整数，表示熊的个数。它的值大于1并且小于9。
样例输入
5
输出
为1个数字，表示果园里原来有的苹果个数。
样例输出
3121



url  :     http://www.nowcoder.com/question/next?pid=734817&qid=26021&tid=4831062

**********/




//  穷举
int get_num(int n)
{
    int count;
    int bear;
    for (int i = n + 1; ; i++)
    {
       count = i;
       bear = n;
       while (count % n == 1)
       {
           count = count - count / n - 1;
           bear--;
       }

       if (bear == 0)
       {
           return i;
       }
    }

    return -1;
}

void test_8()
{
    int n;
    while (cin>>n)
    {
        cout<<get_num(n)<<endl;
    }

}


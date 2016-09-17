#pragma once


/*


文艺青年爱文学

题目描述
小赛是一名文艺的程序员，他十分热爱文学。乘车去公司应聘的路上，小赛又在构想自己的诗歌了——
 
"啊！小赛啊小赛！帅啊很帅可帅了！
    啊！小赛啊小赛！棒啊很棒可棒了！
    啊！小赛啊小赛！啊啊啊啊啊啊啊！"
 
尽管小赛的诗歌——额……有那么一点——（啊啊别拦我——让我掐死这只小赛！）……
但是，小赛自己还是深深陶醉其中的。
 
小赛现在想要创作一首恰好为一定字数（共有n个能满足要求的字数，达到任一皆可）的新诗歌……
他会构想m种长度的短句（如上面那首“诗歌”，有长度为1和7的短句），构想每种长度的短句所耗费的时间是相同的。
现在让你帮忙算下，小赛最少需要多少时间，才能达成自己的目标呢？如果没有办法实现，请输出"It is not true!"（没有引号）。

输入
第一行一个整数n，表示小赛想创作诗歌的字数的集合大小。
接下来n行，其中第i行为一个数a[i]，表示这首诗歌可以是a[i]个字。
第二行一个整数m，表示小赛可以构想出m种不同长度短句的个数。
接下来m行，其中第i行为两个整数b[i],c[i]，其中b[i]表示小赛可以创作出长度为b[i]的短句，对应的c[i]表示创作这种长度短句所消耗的时间。
 
数据保证——a[]中的数各不相同，b[]中的数各不相同，c[]不超过10000.
数据保证——
对于30%的测试点，n=1，1<=m<=2，1<=a[],b[]<=20，
对于70%的测试点，1<=n,m<=5，1<=a[],b[]<=100;
对于100%的测试点，1<=n,m<=100，1<=a[],b[]<=10000;

样例输入
2
7
11
2
3 1
2 100

输出
输出一行，
如果有办法达成目标，则输出一个整数，表示达成目标所最少需要的创作时间。
如果没有办法达成目标，则输出"It is not true!"（没有引号）

样例输出
103

*/

/* 答题思想  类似于 几个数字 可以重复 和 为一个数的所有排列组合   解法类似于斐波那契数列 但用数组记录结果 减少重复计算的时间复杂度*/

#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
vector<int> len,t;

const int MAX = 0x7FFFFFFF;
vector<int> keep_dp(10001); // 优化递归

int dp(int x)
{
    if (x == 0)
    {
        return 0;
    }

    if (keep_dp[x] > 0)
    {
        return keep_dp[x];
    }
    int smin = MAX;
    for (int i = 0; i < len.size(); i++)
    {
        if (x - len[i] >= 0)
        {
            smin = min(smin, dp(x - len[i]) + t[i]);
        }
    }
    keep_dp[x] = smin;

    return smin;
}






void test_20()
{
    int n;
    while (cin>>n)
    {
        vector<int> req(n);
        for (int i = 0; i < req.size(); i++)
        {
            cin>>req[i];
        }

        int m;
        cin>>m;

        len.resize(m), t.resize(m);

        for (int i = 0; i < t.size(); i++)
        {
            cin>>len[i]>>t[i];
        }

        int smin = MAX;
        for (int i = 0; i < req.size(); i++)
        {
            smin = min(smin, dp(req[i]));
        }

        if (smin < MAX)
        {
            cout<<smin<<endl;
        }
        else
        {
            cout<<"It is not true!"<<endl;
        }


    }

}



















/*
        // 别人的程序 参考  类似于斐波那契数列的递归 但是用数组记录结果 优化复杂度
#include <iostream>
#include <string.h>
#include <cstdio>
#include <vector>
using namespace std;
vector<int> len,t;
const int MAX=2000000;
vector<int> keep_dp(10001);
int dp(int x)
{
	//if(x<0)return MAX;
	if(!x)return 0;
	if(keep_dp[x]>0)return keep_dp[x];
	int smin=MAX;
	for(int i=0;i<len.size();i++)
	{
		if(x-len[i]>=0)
			smin=min(smin,dp(x-len[i])+t[i]);
	}
	keep_dp[x]=smin;
	return smin;
}

int main()
{
	#ifdef H2
		freopen("in.txt","r",stdin);
		freopen("out.txt","w",stdout);
	#endif
	int n;
	cin>>n;
	vector<int> req(n);
	for(int i=0;i<n;i++)
		cin>>req[i];
	int m;
	cin>>m;
//	len.resize(m);t.resize(n);
	len.resize(m);t.resize(m);
	for(int i=0;i<m;i++)
		cin>>len[i]>>t[i];
	int smin=MAX;
	//cout<<smin<<endl;
	for(int i=0;i<req.size();i++)
	{
		smin=min(smin,dp(req[i]));
	}
	if(smin<MAX)
		cout<<smin<<endl;
	else cout<<"It is not true!"<<endl;
    return 0 ;
}
*/




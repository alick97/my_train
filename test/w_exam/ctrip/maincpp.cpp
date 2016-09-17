#define _CRT_SECURE_NO_WARNINGS 1




// <algorithm>
#include <stdlib.h>
#include <vector>
#include <iostream>
using namespace std;


/*

股票利润
时间限制：C/C++语言 1000MS；其他语言 3000MS
内存限制：C/C++语言 65536KB；其他语言 589824KB
题目描述：
假如一个数组中存储了一个股票，在一天交易窗口内各时间点的股票价格（正整数）。只允许一次买入和一次卖出，请提供一个算法，计算出通过卖出和买入可以得到的最大利润
输入
价格序列，用,号隔开
输出
最大的可能利润

样例输入
2,3,2,4
样例输出
2


*/
#include <string>
vector<int> v;
int get_max(vector<int> v)
{
    int max = 0;
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = i + 1; j < v.size(); j++)
        {
            if (v[j] - v[i] > max)
            {
                max = v[j] - v[i];
            }
        }
    }

    return max;
}

void test_max()
{
    string s;
    while (cin>>s)
    {
        v.clear();
        const char* cur = s.c_str();
        for (int i = 0; i < s.size(); i++)
        {

            if (s[i] == ',')
            {
                s[i] == '\0';
                v.insert(v.end(), atoi(cur));
                cur = &s[i+1];
            }

        }
        v.insert(v.end(), atoi(cur));

        cout<<get_max(v)<<endl;
    }

}


int main()
{
    test_max();
    return 0;
}




#include <iostream>
using namespace std;

/*
二分查找
时间限制：C/C++语言 1000MS；其他语言 3000MS
内存限制：C/C++语言 65536KB；其他语言 589824KB
题目描述：
请写一个二分查找算法查找一个数最先出现的index，如果数不在集合中需要返回(-1)-当前数应该出现的位置。例如 [1,3,6],查找5,5应该是在index=2的位置但并不在集合中。返回(-1)-2 = -3。
输入
第一行读入一个整数x，表示要查找的数；第二行读入一个正整数n，表示待查找数组的元素个数；第三行读入n个递增整数，构成待查找的数组。
输出
整数x在数组中出现的索引位置(索引从0开始计数)；如果不存在，返回(-1)-当前数应该出现的位置。

样例输入
3
5
0 1 3 5 6
样例输出
2

*/
int arr[1000];
int b_find(int n, int x, int arr[])
{
    int left = 0;
    int right = n - 1;
    int index = 0;
    while (left <= right)
    {
        int mid = left + (right - left)/2;
        if (arr[mid] < x)
        {
            left = mid + 1;
            index = left;
        }
        else if (arr[mid] > x)
        {
            right = mid - 1;
            index = mid;
        }
        else
        {
            return mid;
        }
    }
    return (-1 - index);
}

int main()
{
    int x;
    int n;
    while (cin>>x)
    {
        cin>>n;
        for (int i = 0; i < n; i++)
        {
            cin>>arr[i];
        }
        cout<<b_find(n,x,arr)<<endl;
    }
    return 0;
}






/*
    
遍历最短路径长度
时间限制：C/C++语言 1000MS；其他语言 3000MS
内存限制：C/C++语言 65536KB；其他语言 589824KB
题目描述：
暴风降临的龙母丹妮莉丝·坦格利安要骑着她的龙以最快的速度游历各国，她的谋士们纷纷献策规划路线。作为她的谋士之一和仰慕者的你，决定冒险穿越到21世纪借助计算机来寻求最优路线。请设计一段程序，读取各国两两之间的距离，距离以邻接矩阵表示，并计算出遍历各国的最短路径长度。
输入
第一行：国家数量，假设为n
后续n行是国家间距离的邻接矩阵表示
输出
遍历各国的最短路径长度

样例输入
4
0,1,2,3
1,0,4,5
2,4,0,2
3,5,2,0
样例输出
5

*/
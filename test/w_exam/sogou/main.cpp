#define _CRT_SECURE_NO_WARNINGS 1

/*

    距离的总和
    时间限制：C/C++语言 2000MS；其他语言 4000MS
    内存限制：C/C++语言 65536KB；其他语言 589824KB
    题目描述：
    定义两个大于2的偶数之间的距离，为这两个数之间质数的个数。从小到大输入n个大于2的偶数，输出所有数两两之间距离的总和（应该有n*(n-1)/2个距离，输出总和就好)。
    输入
    第一行是输入偶数的个数，最小为2，最大可能到几万。之后每行为一个偶数，最小是4，最大可能是几百万，不重复的升序排列。
    输出
    输入数据两两间距离的总和，这应该是一个不小于0的整数。

    样例输入
    3
    4
    6
    12
    样例输出
    6


    */



#include<algorithm>

#include<iostream>
#include <vector>
using namespace std;

bool is_zhishu(int num)
{
  
    for (int i = 2; i <= num/2; i++)
    {
         if (num % i == 0)
         {
          return false;
         }
    }
    return true;
}

int get_geshu(int n1, int n2)
{
     int count = 0;
     for (int i = n1; i <= n2; i++)
     {
         if (is_zhishu(i))
         {count++;}
     }
     return count;
}

int main()
{
    int n;
    int tmp;
    while(cin>>n)
    {
        int count = 0;
         vector<int> v;
        for (int i = 0; i < n; i++)
        {
           cin>>tmp;
           v.insert(v.end(), tmp);
        }
        // GET 质数
        vector<int> pri;
        for (int i = v[0]; i <= *(--v.end()); i++)
        {
             if (is_zhishu(i))
             {
                pri.insert(pri.end(), i);
             }
        }

        vector<int> pri_count;
        pri_count.resize(v.size() - 1);
        int prev = 0;
        for (int i = 1; i < v.size(); i++)
        {
              for (int j = prev; j < pri.size(); j++)
              {
                 if (pri[j] < v[i])
                 {
                  pri_count[i - 1]++;
                 }
                 else
                 {
                    prev = j;
                    break;
                 }
              }
        }
        //    4         6        12     14
        //         5         7\11    13  
        //         1         2         1               (1+2)+(1+2+1)+(2 + 1)    +1 + 2 + 3 = 14
        for (int i = 0; i < pri_count.size(); i++)
        {
           for (int j = i + 1; j < pri_count.size(); j++)
           {
               //count +=( pri_count[i] + pri_count[j]);
               for (int k = i; k <= j; k++)
               {
                   count += pri_count[k];
               }
           }
           count += pri_count[i];
        }


         cout<<count<<endl;
    }
    return 0;
}



/*

一个字符串的最大回文前缀长度
时间限制：C/C++语言 1000MS；其他语言 3000MS
内存限制：C/C++语言 65536KB；其他语言 589824KB
题目描述：
求一个字符串的最大回文前缀长度。回文是指正反方向读起来都一样的字符串，比如“abcdcba”就是一个回文。
输入
一个文本文件，至少包含一个字节。每个字节是一个字符。最大长度可能有几十万字节。
输出
最大回文前缀的长度。

样例输入
sogou
样例输出
1


*/
///////////////////////////////  有问题？？？  //////////////////////////////////////
//
//#include<string>
//#include <iostream>
//#include <algorithm>
//using namespace std;
//
//
//
//int get_count(string s)
//{
//    int s_size = s.size();
//    string rev_str = s.assign(s, s_size/2 + 1, s_size);
//    string fas_str = s.assign(s, 0, s_size/2);
//    reverse(rev_str.begin(), rev_str.end());
//    
// 
//    int count = 0;
//    for (int i = 0; i < s_size/2; i++)
//    {
//        for (int j = 0; j < s_size/2 - i; j++)
//        {
//             string s_tmp(s.c_str() + i + j);
//            size_t f = rev_str.find(s_tmp);
//            if (f != string::npos)
//            {
//                count++;
//            }
//        }
//        
//    }
//    return count;
//}
//
//int main()
//{
//    string s;
//    while (cin>>s)
//    {
//       cout<<(get_count(s)+1)/2<<endl;
//    }
//   return 0;
//}

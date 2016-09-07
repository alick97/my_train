//
//
//#pragma once 
//
//
///*********
//
// qsort 练习     比较函数 *p1 - *p2  从小到大排
// sort  练习     比较函数 int p1  < int p2   从小到大排      比较的结构体的operator()   也是 p1<p2  从小到大
//***************/
//
//#include<iostream>
//#include <vector>
//#include <algorithm>
//using namespace std;
//
//#define __SIZE__ 8
//int arr[__SIZE__] = { 3,5,4,1,2,7,9,5};
//
//int compare_than(const void * p1, const void* p2)
//{
//    return *(int *)p1 - *(int*)p2;   //  从小到大升序
//}
//
//int compare_less(const void * p1, const void* p2)
//{
//    return *(int *)p2 - *(int*)p1;   //  从大到小降序
//}
//void Print()
//{
//    for (int i = 0; i < __SIZE__; ++i)
//    {
//        cout<<arr[i];
//    }
//    cout<<endl;
//}
//
//
//void test_qsort()         
//{
//   // qsort(arr,8,sizeof(int),compare_than); // 12345579
//    qsort(arr,8,sizeof(int),compare_less); // 97554321
//    Print();
//}
//
//
//vector<int> v(arr, arr + sizeof(arr)/sizeof(int));
//
//void print_v()
//{
//    for (int i = 0; i < __SIZE__; i++)
//    {
//        cout<<v[i];
//    }
//    cout<<endl;
//
//}
//
//bool fun_than(const int& a, const int& b)
//{
//    return a > b;       // 从大到小排序
//}
//
//struct than
//{
//    bool operator()(const int& a, const int& b)
//    {
//        return a < b;     // 从小到大排序
//    }
//
//};
//
//
//void test_sort()
//{
//    
//    
//    //12345579
//  // sort(v.begin(), v.end());
//  // print_v();
//
//    // 97554321 
//   //sort(v.begin(), v.end(), fun_than);
//   sort(v.begin(), v.end(), than());
//    print_v();
//}
//

/********
计算器的新功能

题目描述
当你学一些可视化程序设计语言时，老师经常会让你设计并且编程做出一个计算器，这时也许你会仿照windows系统自带的计算器外观和功能去设计，但是现在老师要你多做出一个有新功能的计算器，实现当输入一个数时，能够将这个数分解成一个或多个素因子乘积的形式，并按素因子的大小排列显示出来。大家对计算器中数的表示应该很清楚的。下面显示出了0 — 9这十个数字的表示形式。每个数字都占据5 * 3大小的字符区域

你能实现这个新功能吗？试试看吧！
输入
输入有多组测试数据，每组包括一个正整数n（1 < n <= 1000000)。
样例输入
10
2
输出
对于每个数，将它分解成若干个素数乘积的形式，并按从小到大的顺序输出，素因子之间用“ * ”的形式连接。
样例输出
 -     -
  |   |
 -  *  -
|       |
 -     -
 
 -
  |
 -
|
 -




******************/

#pragma once 

#include <iostream>
using namespace std;
#include <vector>
#include <string>
vector<int> v;

void get_prime_v(int n)
{
    v.clear();
    int prime = 2;
    while (n >= prime)
    {
        if (prime == n)
        {
            v.insert(v.end(), prime);
            break;
        }
        else if (n % prime == 0)
         {
             n /= prime;
             v.insert(v.end(), prime);
        }
        else
        {
            prime++;
        }
    }
}



    string line1[10] = {" - ", "   ", " - ", " - ", "   ", " - ", " - ", " - ", " - ", " - "};
    string line2[10] = {"| |", "  |", "  |", "  |", "| |", "|  ", "|  ", "  |", "| |", "| |"};
    string line3[10] = {"   ", "   ", " - ", " - ", " _ ", " - ", " - ", "   ", " - ", " - "};
    string line4[10] = {"| |", "  |", "|  ", "  |", "  |", "  |", "| |", "  |", "| |", "  |"};
    string line5[10] = {" - ", "   ", " - ", " - ", "   ", " - ", " - ", "   ", " - ", " - "};

    string get_string_num(int n)
    {
        string s;
        while (n > 0)
        {
            char tmp = n % 10;
            n /= 10;
            s.insert(s.begin(), tmp + '0');
        }
        return s;
    }

void print_calcuate(int n)
{
    get_prime_v(n);

    /*
    
     -     -
      |   |
     -  *  -
    |       |
     -     -
    
    **/
  
   
     string s;
            for (int j = 0; j < v.size(); j++)
            {
                s = get_string_num(v[j]);
                for (int index = 0; index < s.size(); index++)
                {
                    cout<<line1[s[index] - '0'];
                }
                cout<<" ";
            }
            cout<<endl;
            for (int j = 0; j < v.size(); j++)
            {
                s = get_string_num(v[j]);
                for (int index = 0; index < s.size(); index++)
                {
                    cout<<line2[s[index] - '0'];
                }
                cout<<" ";
            }
            cout<<endl;
            for (int j = 0; j < v.size(); j++)
            {
                s = get_string_num(v[j]);
                for (int index = 0; index < s.size(); index++)
                {
                    cout<<line3[s[index] - '0'];
                }
                if (j != v.size() - 1)
                cout<<"*";
            }
            cout<<endl;
            for (int j = 0; j < v.size(); j++)
            {
                s = get_string_num(v[j]);
                for (int index = 0; index < s.size(); index++)
                {
                    cout<<line4[s[index] - '0'];
                }
                cout<<" ";
            }
            cout<<endl;
            for (int j = 0; j < v.size(); j++)
            {
                s = get_string_num(v[j]);
                for (int index = 0; index < s.size(); index++)
                {
                    cout<<line5[s[index] - '0'];
                }
                cout<<" ";
            }
            cout<<endl;

        

    


}


void test_5()
{
    int n;
    while (cin>>n)
    {
        print_calcuate(n);
    }

}

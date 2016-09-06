
#pragma once


/************



题目描述
给定一个长度为n的整数数组a，元素均不相同，问数组是否存在这样一个片段，只将该片段翻转就可以使整个数组升序排列。其中数组片段[l,r]表示序列a[l], a[l+1], ..., a[r]。原始数组为
a[1], a[2], ..., a[l-2], a[l-1], a[l], a[l+1], ..., a[r-1], a[r], a[r+1], a[r+2], ..., a[n-1], a[n]，
将片段[l,r]反序后的数组是
a[1], a[2], ..., a[l-2], a[l-1], a[r], a[r-1], ..., a[l+1], a[l], a[r+1], a[r+2], ..., a[n-1], a[n]。
输入
第一行数据是一个整数：n (1≤n≤105)，表示数组长度。
第二行数据是n个整数a[1], a[2], ..., a[n] (1≤a[i]≤109)。
样例输入
4
2 1 3 4
输出
输出“yes”，如果存在；否则输出“no”，不用输出引号。
样例输出
yes

******************************/
#include <iostream>
using namespace std;
#define __COUNT__   10000000
int arr[__COUNT__];


void print_is_reverse(int n, int arr[])
{
  
    int i =  1;
    int start_index = 0;
   
    int max_count = 0;
    bool is_order = true;
    for (; i < n; i++)
    {
        // 1 2 4 3 5
      //   1 2  5 4 3
      
         // 特殊  3 2 1 1 5 1
        if (is_order)
        {
            if (arr[i] <= arr[i - 1])
            {
                is_order = false;
                start_index = i - 1;
               // max_count++;
            }
        }
        else
        {
          
	if (arr[i] > arr[i - 1])
    {
            if (arr[i] > arr[start_index]  )
            {
                
                        max_count++;
                is_order = true;
           
                
            }
      else
        
      {cout<<"no"<<endl;return;}
                 }

        }
    }

    if (max_count == 1)
    {
        cout<<"yes"<<endl;
    }
    else
    {
        cout<<"no"<<endl;
    }


}


void test_3()
{
    int n;
    while (cin>>n)
    {
        for (int i = 0; i < n; i++)
        {
            cin>>arr[i];
        }
        print_is_reverse(n, arr);
    }

}




//
//
//int main()
//{
//
//test_3();
//  
//return 0;
//
//}

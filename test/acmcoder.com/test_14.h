

#pragma once

/*


比大小【字符串字典排序 全排列】
题目描述
现在有"abcdefghijkl”12个字符，将其所有的排列中按字典序排列，给出任意一种排列，说出这个排列在所有的排列中是第几小的？
输入
第一行有一个整数n（0＜n＜=10000）;
随后有n行，每行是一个排列；
样例输入
3
abcdefghijkl
hgebkflacdji
gfkedhjblcia
输出
输出一个整数m，占一行，m表示排列是第几位；
样例输出
1
302715242
260726926

*/

//  效率太低
//   *****************************  输出了字符串的所有排列 并且是 按照字典排序的
/*
#include <iostream>
using namespace std;
#include <string>

 int str_count  = 0;

bool get_index(char *str, int size,int index ,char* desc)
{
    if (index == size - 1)
    {
        str_count++;
        if (strcmp(str, desc) == 0)
        {
           return true;
        }
        else
        {
           return false;
        }
    }
   bool ret = false;
     for (int i = index; i < size; i++ )
     {
        //swap(str[index], str[i]);
         // 右旋一位    abcd     adbc    
         //              ^ ^      ^  
         char tmp = str[i];  // d
         int j = i;
         for (; j > index; j--)
         {
             str[j] = str[j-1];
         }
         str[j] = tmp;
        ret = get_index(str ,size, index + 1, desc);
        if (ret)
        {
          return ret;
        }
        //swap(str[index], str[i]);
        // 左旋一位 还原
        //        adbc     abcd
        //         ^          ^
        tmp = str[index];
        for (j = index; j < i; j++)
        {
            str[j] = str[j+1];
        }
        str[j] = tmp;
     }
     return false;
}
string s[100];
void test_14()
{
   
  //  string desc = "abc";
    int n;
    while (cin>>n)
    {
       for (int i = 0; i < n; i++)
       {
          cin>>s[i];
       }

       for (int i = 0; i < n; i++)
       {
           string desc = "abcdefghijkl";
           str_count = 0;
           get_index(const_cast<char*>(desc.c_str()), s[i].size(), 0, const_cast<char*>(s[i].c_str()));
           cout<<str_count<<endl;
       }
    }
   
}
*/

#include <iostream>
using namespace std;
#include <string>
int get_index(string s)
{
     //  12
     int count = 0;
     bool is[256] = {false};
     for (int i = 0; i < s.size() - 1; i++)
     {
         int n = s.size() - i - 1;
         int quan_c = 1;// 全排列
         while (n > 1)
         {
             quan_c *= n--;
         }
       
         char c = s[i];
         int less_c = 0;
         for (int i = c - 1; i >= 'a'; i--)
         {
            if (!is[(unsigned int)i])
            {
                less_c++;
            }
         }
         is[(unsigned int)c] = true;
             count += less_c * quan_c;
     }
      return count + 1;
}

string s[100];
void test_14()
{
   
  //  string desc = "abc";
    int n;
    while (cin>>n)
    {
       for (int i = 0; i < n; i++)
       {
          cin>>s[i];
       }

       for (int i = 0; i < n; i++)
       {
           cout<<get_index(s[i])<<endl;
       }
    }
   
}
#pragma once

/*

回文串
题目描述
给定一个字符串，问是否能够通过添加一个字母将其变成“回文串”。 “回文串”是指正着和反着读都一样的字符串。如：”aa”,”bob”,”testset”是回文串，”alice”,”time”都不是回文串。
输入
一行一个有小写字母构成的字符串，字符串长度不超过10。

样例输入
coco

输出
如果输入字符串可以通过添加一个字符，则输出”YES”，否则输出”NO”。

样例输出
YES


*/
#include <iostream>
#include <string>
using namespace std;
bool is_palindrome(const char* left, const char *right)
{
    
    bool is = true;
    while (left <= right)
    {
        if (*left != *right)
        {
            is = false;
            break;
            
        }
        left++;
            right--;
    }
    return is;
}

bool get_all(const string& s)
{
    const char* left = s.c_str();
    const char* right = s.c_str() + s.size() - 1;
    bool is_1 = true;
    bool is_2 = true;
    while (left <= right)
    {
        if (*left != *right)
        {
            is_1 = is_palindrome(left+1, right);
            is_2 = is_palindrome(left,right -1);
            break;
        }
        left++;
        right--;
    }
    if (is_1 || is_2 )
    {
        return true;
    }
    else
    {
        return false;
    }

}


void test_is_palindrome()
{
    string t;
    while (cin>>t)
    {
        if(get_all(t))
        {
            cout<<"YES"<<endl;
        }
        else
        {
            cout<<"NO"<<endl;
        }


    }

}

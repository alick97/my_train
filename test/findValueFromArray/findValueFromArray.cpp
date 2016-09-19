#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
using namespace std;

/******
 * 1 一个数组中只有一个数出现一次 其他都成对出现 找出这个数
 * （利用异或）
 ****************/

int findValue_1(const int arr[], int length)
{
    assert(NULL != arr && length > 0);

    int ret = 0;
    for (int i = 0; i < length; i++)
    {
        ret ^= arr[i];
    }

    return ret;
}

void test_findValue_1()
{
    int arr[] = {1,2,2,3,3,4,4};
    int value = findValue_1(arr, 7);
}

/************
 * 2 一个数组中，有两个数字出现了一次，其他数字都是成对出现，请找出这两个数字。
 * （利用异或）
 ****************/
void  findValue_2(const int arr[], int length)
{
    assert(NULL != arr && length > 0);
    int value1 = 0;
    int value2 = 0;

    // 根据value1 与 value2值不同 二进制中肯定有一位不同 根据这一位将数据分成两组
    // 先找异或结果
    int ex = 0;
    for (int i = 0; i < length; i++)
    {
        ex ^= arr[i];
    }

    unsigned int index = 0;

    // 11100 & 11011 == 11000    11100 ^ 11000 == 00100
    index ^= ex & (ex - 1);//(这里以从右向左第一个不同的位)

    // 例如 找到value1 和 value2 用index分组

    for (int i = 0; i < length; i++)
    {
        if (index == (arr[i] & index))
        {
            value1 ^= arr[i];
        }
        else
        {
            value2 ^= arr[i];
        }
    }


    cout<<"value1:"<<value1<<endl;
    cout<<"value2:"<<value2<<endl;

}


void test_findValue_2()
{
    int arr[] = {1,2,33,33,44,44,55,55,-1,-1};
    findValue_2(arr, 10);
}

/************
 * 3 一个数组中，有三个数字出现了一次，其他数字都是成对出现，请找出这三个数字中的一个数字。
 * （利用异或）
 ****************/






int main()
{
    //test_findValue_1();
    test_findValue_2();
    return 0;
}




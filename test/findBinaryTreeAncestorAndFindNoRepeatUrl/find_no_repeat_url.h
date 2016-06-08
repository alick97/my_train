#pragma once

#include<iostream>
using namespace std;

#include<bitset>

void index_repeat(int* a, int an, int* b, int bn)
{
    const unsigned int n = 0x11111;
    bitset<n>  bm;

    for (int i = 0; i < bn; i++)
    {
        bm.set(b[i]);
    }

    for(int i = 0; i < an; i++)
    {
        if (bm.test(a[i]))
        {
            cout<<a[i]<<"    repeated"<<endl;
        }
    }
}

void test_url()
{
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    int b[10] = {7,8,9,10,44,55,66,77,88,33};
    index_repeat(a,10,b,10);
}


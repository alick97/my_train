#pragma once
/*

行编辑器
题目描述
你知道行编辑器吗？不知道也没关系，现在我会告诉你：
1.如果你收到一个
输入
第一行是一个整数T，代表有T组数据。
每组数据的开始时一个字符串，字符串长度小于100，每个字符一定是(
样例输入
3
whli##ilr#e(s#*s)
outcha@putchar(*s=#++)
returnWA##A!!##C
 

输出
每组数据输出一行经过行编辑器编辑过的字符串，具体可以看样例。
样例输出
while(*s)
putchar(*s++)
returnAC

*/
#include <iostream>
using namespace std;
char c[50][101];

void my_flush(char* desc, char* src)
{
    while (*src != '\0')
    {
        *desc = *src;
        desc++;
        src++;
    }
    *desc = '\0';
}

char * line_deal(char* pc)
{
   
    //  @ 只输出后面的字符
    // A##A ->   A            A!!##C -> AC
    char* cur = pc;
        char* houtou = cur - 1;
    while (*cur != '\0' )
    {
        if (*cur == '@')
        {
            houtou = cur;
        }
        cur++;
    }
    cur = houtou + 1;
    char* new_head = cur;
    while (*cur != '\0')
    {
        if (*cur == '#')
        {
            
                
                if (*(cur + 1) == '\0' && cur != new_head)
                {
                    *(cur - 1) = 0;
                }
                else
                {
                    my_flush(cur -1, cur +1);
                }


                    cur = cur - 1;
                     continue;      
        }
         cur++;  
    }

    return new_head;
}

void test_line()
{
    int n;
    while (scanf("%d",&n) != EOF)
    {
         for (int i = 0; i < n; i++)
        {
            scanf("%s", c[i]);
        }

         for (int i = 0; i < n; i++)
        {
            printf("%s\n", line_deal(c[i]));
        }
    }

   

}


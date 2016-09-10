#define _CRT_SECURE_NO_WARNINGS 1




/*   360 笔试题20160910  **/
/*
时间限制：C/C++语言 1000MS；其他语言 3000MS
内存限制：C/C++语言 65536KB；其他语言 589824KB
题目描述：
小B乘火车和朋友们一起在N市到M市之间旅行。她在路途中时睡时醒。当她醒来观看窗外的风景时，注意到每个火车站都有一种特别颜色的旗帜，但是她看到的旗帜仅仅是经过的一小部分。小B在乘车过程中有两次清醒的时间，她到达旅程终点时处于睡梦中。出站时，她和朋友们谈论着一路的见闻，朋友们觉得很有意思。
他们把N到和M之间经过车站的旗帜颜色依次列出来，然后告诉你小B记得的旗帜颜色序列，让你判断小B究竟是从N和M之间哪些方向才能看到所说颜色的旗帜，还是根本就不可能看到？颜色用字母代表，相同的字母代表相同的颜色，不同的字母则表示不同的颜色。
输入
输入中有多组测试数据。每组测试数据包含三行，第一行为一个由小写拉丁字母构成的非空字符串，长度不超过10^5，表示N到M之间车站的颜色。火车从M向N运行时，经过的车站相同，只是方向相反。第二行为小B在第一次睡醒时看到的颜色序列，第三行为小B在第二次睡醒时看到的颜色序列。两个序列都是小写的拉丁字母构成的字符串，长度不超过100个字母。每个序列的颜色顺序排列按小B看到的时间顺序排列。
输出
对每组测试数据，在单独的行中输出小B的旅行方向。
forward – 由N到M方向；
backward – 由M到N方向；
both – 两种方向都有可能；
invalid – 不可能看到这样的颜色序列；

样例输入
atob
a
b
aaacaaa
aca
aa
样例输出
forward
both

Hint
火车假定时刻处于运动状态，不会两次看到同一个旗帜。N市和M市的车站没有旗帜。

*/

#include <iostream>
#include<string>
#include <algorithm>
using namespace std;

bool is_forword(string str, string str1, string str2)
{
     size_t f1,f2,f3;
     f1=str.find(str1);
     f2=str.find(str2);
  if (f1!=string::npos && f2!=string::npos)
  {
        if (f1 + str.length()<= f2)
        {return true;}

        f3 = str.find(str2, f1+ str.length());
        if (f3!=string::npos)
        {return true;}
  }
  

  return false;

}

bool is_hou(string str, string str1, string str2)
{
     reverse(str.begin(), str.end());
  size_t f1,f2,f3;
     f1=str.find(str1);
     f2=str.find(str2);
    if (f1!=string::npos && f2!=string::npos)
  {
        if (f1 + str.length() <= f2)
        {return true;}

        f3 = str.find(str2, f1+ str.length());
        if (f3!=string::npos)
        {return true;}
  }
  return false;

}

void check(string s, string s1, string s2)
{
    bool b1 = is_forword(s, s1, s2);
    bool b2 = is_hou(s, s1, s2);
      if (b1 && b2)
      {cout<<"both"<<endl;}
      else if (b1)
      {cout<<"forward"<<endl;}
      else if (b2)
      {cout<<"backward"<<endl;}
      else
      {cout<<"invalid"<<endl;}
}

int main()
{
   string s,s1,s2;
   while (cin>>s>>s1>>s2)
   {check( s, s1,s2);}
   return 0;
}




/*

内存管理
时间限制：C/C++语言 1000MS；其他语言 3000MS
内存限制：C/C++语言 65536KB；其他语言 589824KB
题目描述：
物联网技术的蓬勃发展，各种传感器纷纷出现。小B所在的项目组正在开发一个物联网项目，她们在研究设计一种新的传感器。这种传感器有自己的基本处理单元，具有一定的自主性，能够进行简单的数据收集、处理、存储和传输。为降低系统功耗并保证系统可靠性和可控性，他们要对内存进行基本的管理。研究小组计划开发一个实验性内存管理器，实现对内存的分配、释放和整理。对应的接口为new、del和def，使用语法为：
new size：分配size字节大小的内存块，返回该内存块的句柄handle，size为正整数；
del handle：释放句柄handle指向的内存块；
def：整理内存碎片，将所有已分配内存块按地址从低到高的顺序迁移，使空闲内存碎片在高地址端拼接在一起；
初始内存为 initSize 字节大小的整片空闲内存，编号为 1 到 initSize 。
new size操作中，若存在不小于size的连续空闲内存，则按照小地址优先的原则从空闲内存区域中分配size大小的内存块，标记该内存块状态为已分配，并返回指向该内存块的句柄。若无法分配，则返回空（NULL）。
del handle操作释放由handle标记的内存块，标记被释放的内存状态为空闲。若handle为无效句柄，则返回ILLEGAL_OPERATION。
def 完成内存整理工作，无返回值。
根据设计，每次成功内存分配返回的句柄为一个正整数，从1开始，依次计数。失败的存储分配操作不影响计数。
项目小组将此项任务分配给小B，小B向你求助，你能帮她吗？
输入
输入中有多组测试数据。每组测试数据的第一行为两个正整数T和MaxMem（1<=T<=10000, 1<=MaxMem<=10000），其中T为操作次数，MaxMem为初始内存大小，随后有T行操作指令。
输出
对每组测试数据，按操作顺序输出操作结果。对每个new操作，在单独行中输出结果，成功时输出其返回句柄值，失败则输出NULL。若del操作失败，输出ILLEGAL_OPERATION。def不产生输出。

样例输入
6 10
new 5
new 3
del 1
new 6
def
new 6
样例输出
1
2
NULL
3


*/
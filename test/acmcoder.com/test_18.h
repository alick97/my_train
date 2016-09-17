#pragma once



/*

搬圆桌
题目描述
小A有一张半径为r的圆桌，其中心位于(x,y)，现在他想把圆桌的中心移到(x1, y1)。每次移动一步，小A都得在圆桌边界上固定一个点，然后将圆桌绕这个点旋转。 问最少需要几步才能把圆桌移到目标位置？

输入
一行五个整数r,x,y,x1,y1( 1 ≤ r ≤ 100000,  - 100000 ≤ x, y, x1, y1 ≤ 100000)。
样例输入
2 0 0 0 4

输出
一个整数，表示最少需要移动的步数。

样例输出
1

*/
#include <iostream>
using namespace std;
#include <cmath>
int get_step(int r, int x, int y, int x1, int y1)
{
    //int max = (abs(x - x1) + abs(y - y1)) / (r * 2);
   double dist = sqrt(pow(x1 - x,2) + pow(y1- y, 2));

    int step = ceil(dist / (2*r));

    
    return step;
}

void test_18()
{
    int r,x,  y,  x1, y1;
    while (cin>>r>>x>>y>>x1>>y1)
    {
        cout<<get_step( r,  x,  y,  x1, y1)<<endl;
    }

}


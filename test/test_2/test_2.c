/*************************************************************************
	> File Name: test_2.c
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年07月25日 星期一 22时54分35秒
 ************************************************************************/

#include<stdio.h>

// 交换两个整型变量的值 不允许创建临时变量
int my_swap(int *a, int *b)
{
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

void test_my_swap()
{
	int a = 1;
	int b = 2;
	my_swap(&a, &b);
	printf("%d    %d", a, b);
}

// 写一个函数 返回二进制中1的个数
// 15 0000 1111    4个1
unsigned int bin_1(unsigned int x)
{
	unsigned int count = 0;
	unsigned int i = 1;
	while (i != 0)
	{
		if ((x & i) > 0)
		{
			count++;
		}

		i <<= 1;
	}
	return count;
}

void test_bin_1()
{
	int i = 15;
	printf("%d\n", bin_1(i));
}

int main()
{
	//test_my_swap();
	test_bin_1();
	return 0;
}

/*************************************************************************
	> File Name: test_4.c
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月01日 星期一 00时59分45秒
 ************************************************************************/

#include<stdio.h>
// 1 编写程序 可以一直接收键盘字符 如果小写 输出大写 大写 输出小写 数字不输出

void char_switch()
{
	char c;
	printf("input :> ");
	while(c = getchar())
	{
		if (c >= 'a' && c <= 'z')
		{
			printf("%c", c - ('a' - 'A'));
		}
		else if (c >= 'A' && c <= 'Z')
		{
			printf("%c", c + 'a' - 'A');
		}
		else if (c >= '0' && c <= '9')
		{
			;
		}
		else
		{
			break;
		}
	}

	printf("\n");
}



// 2 输出一个整数的每一位
void print_bit_num(unsigned int num)
{
	unsigned int i = 1;
	i <<= 31;
	while (i != 0)
	{
		printf("%d", (i&num) > 0);
		i >>= 1;
	}
	printf("\n");
}

void test_print_bit_num()
{
	unsigned int i = 14;
	print_bit_num(i);
}



// 3 计算1/1-1/2+1/3-1/4+1/5.。。。。。+1/99-1/100的值。
void add_sub()
{
	float i = 1, j = 1, s = 0;
	for (; j <= 100; j++)
	{
		s += i/j;
		i = 0 - i;
	}
	printf("--------%d\n", s);
}
// 4 编写程序 数一下 1-100的所有整数中出现多少次数字9

int find_nine(int x)
{
	int count  = 0;
	do 
	{
		if (x % 10 == 9)
		{
			count++;
		}
		x = x/10;
	}while (x != 0);
	return count;
}

void find_100()
{
	int i = 1, count = 0;
	for (i = 1; i <= 100; i++)
	{
		count += find_nine(i);
	}

	printf("1-100     9 count: %d\n", count);
}

int main()
{

//	char_switch();
 //   test_print_bit_num();
//	add_sub();
     find_100();
	return 0;
}

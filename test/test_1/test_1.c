/*************************************************************************
	> File Name: test_1.c
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年07月20日 星期三 10时37分15秒
 ************************************************************************/

#include<stdio.h>
#include <math.h>

// 打印100-200之间的素数
void test_1()
{
	int i = 100, j=2;
	printf("100-200 之间的素数为：\n");
	for (    i = 101; i < 200; i+=2)
	{
		int is_su = 1;
		for (j = 2; j <= (int)sqrt(i); j++)
		{
			if (i % j == 0)
			{
				is_su = 0;
				break;
			}
		}

		if (is_su)
			printf("%d\n", i);
	}

	return  ;
}


// 输出乘法口诀表
void test_2()
{
	int i,j;
	for (i = 1; i < 10; i++)
	{
		for (j = 1; j <= i; j++)
		{
			printf("%d*%d=%d   ", j , i, i*j);
		}
		printf("\n");
	}

}

// 判断1000年---2000年之间的润年
int is_leap_year(int year)
{
	if (year % 4== 0 &&year %100 != 0 || year %100 == 0 && year%400 == 0)
		return 1;
	else return 0;
}
void test_3()
{
	int year = 1000;
	printf("1000 - 2000年之间的润年为：\n");
	for (; year<= 2000; year++)
	{
		if (is_leap_year(year))
			printf("%d\n", year);
	}
}
int main()
{
	//test_1();
	//test_2();
	  test_3();
	return 0;
}

/*************************************************************************
	> File Name: test_8.c
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月16日 星期二 23时03分50秒
 ************************************************************************/

/*
 * 这里小牛 在出生当年算起 在第五个年头才开始生 
 * 
 * 第1-2-3 年新产生的 牛 每年1头 ，最后算有多少牛时， 不考虑产生第一
 * 年那一头小牛的母牛， 这是 根据测试用例 总结的
 * 
 * f(n) = f(n - 4) + f(n - 1); 
 * f(n) 表示第n年产生的 小牛
 * f(n - 4)为 4年之前的小牛 今年 可以生育小牛
 * f(n - 1) 去年可以差生这么多新牛 就说明去年这么多个数的牛可以生小牛
 *           那么今年它们也可以
 * */


#include<stdio.h>
#include <stdlib.h>

/* method 1 recursive */
int new_cows_method1(int n)
{
	if (n <= 4)
	{
		return 1;
	}
	else
	{
		return new_cows_method1(n - 1) + new_cows_method1(n - 4);
	}
}

int num_cows_method1(int n)
{
	int sum = 0;
	int i = 1;
	for (; i <= n; i++)
	{
		sum += new_cows_method1(i);
	}
	return sum;
}



/* method2 not recursire use array*/
int num_cows_method2(int n)
{
	int* new_cows_arr = (int *)malloc(sizeof(int)*n);
	int i = 0;
	for (i = 0; i < n; i++)
	{
		if (i < 4)  // 0 1 2 3
		{
			new_cows_arr[i] = 1;
		}
		else
		{
			new_cows_arr[i] = new_cows_arr[i - 1] + new_cows_arr[i - 4]; 
		}
	}

	int sum = 0;

	for (i = 0; i < n; i++)
	{
		sum += new_cows_arr[i];
	}

	free(new_cows_arr);

	return sum;
}


/* method3 not recursire use only variable*/
int num_cows_method3(int n)
{
	int y1,y2,y3,y4, y5;
	y1 = y2 = y3 = y4 = y5 =1;

	int i  = 1, sum = 0;
	for (i = 1; i <= n; i++)
	{
		if (i <= 4)
		{
			sum += 1;
		}
		else
		{
			y5 = y4 + y1;
			sum += y5;
			y1 = y2;
			y2 = y3;
			y3 = y4;
			y4 = y5;
		}
	}
	return sum;
}

void test_num_cows()
{
	int i = 0;
	// 2,4,5->2,4,6
	printf("method 1\n");
	printf("2-----%d \n",num_cows_method1(2) );
	printf("4-----%d \n",num_cows_method1(4) );
	printf("6-----%d \n",num_cows_method1(5) );
	printf("method 2\n");
	printf("2----%d \n",num_cows_method2(2) );
	printf("4----%d \n",num_cows_method2(4) );
	printf("6----%d \n",num_cows_method2(5) );
	printf("method 3\n");
	printf("2----%d \n",num_cows_method3(2) );
	printf("4----%d \n",num_cows_method3(4) );
	printf("6----%d \n",num_cows_method3(5) );
}
int main()
{
	test_num_cows();
	return 0;
}

/*************************************************************************
	> File Name: test.c
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2016年06月09日 星期四 13时01分34秒
 ************************************************************************/

#include<stdio.h>

int func(int n)
{
	int sum = 0, i;

	for (i = 0; i <= n; i++)
	{
		sum += i;
	}
	return sum;
}

int main()
{
	int i ;
	int a[] = {1,2,3,4,5};
	char c[] = "abcde";
	int*  pa = a;
	long result = 0;
	
	struct 
	{
		int i;
		int b;
	} stru;
	stru.i = 0;
	stru.b=3;

	for (i = 1; i <= 100; i++)
	{
		result += i;
	}

	printf("result[1-100] = %d\n", result);
	printf("result[1-250] = %d\n", func(250));

	return 0;
}

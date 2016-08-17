/*************************************************************************
	> File Name: test_9.c
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月17日 星期三 23时20分24秒
 ************************************************************************/

#include<stdio.h>
#include <math.h>
//1.实现一个函数，打印乘法口诀表，口诀表的行数和列数自己指定，
//输入9，输出9*9口诀表，输出12，输出12*12的乘法口诀表。

void printCFB(int line)
{
	int i = 1, j = 1;
	for (i =1; i <= line; i++)
	{
		for (j=1; j <= i; j++)
			printf("%3d * %3d = %3d", j, i, i*j);
		printf("\n");
	}
}

void test1()
{
	printCFB(4);
}
//2.使用函数实现两个数的交换。
//

void swap(int *a, int *b)
{
	int temp;
	temp=*a;*a = *b; *b = temp;
}

void test2()
{
	int a = 1, b=0;
	swap(&a, &b);
	printf("1 0 -swap-> %d %d\n", a, b);
}
//3.实现一个函数判断year是不是润年。
//
//

int is_leap(int year)
{
	if (year % 4 == 0 && year % 100 != 0 ||\
			year % 400 == 0)
		return 1;
	else
		return 0;
}
void test3()
{
	printf("2013    --     %s\n", is_leap(2013)?"is leap": "is not leap");
	printf("2016    --     %s\n", is_leap(2016)?"is leap": "is not leap");
	printf("2000    --     %s\n", is_leap(2000)?"is leap": "is not leap");
	printf("2100    --     %s\n", is_leap(2100)?"is leap": "is not leap");
}
//4.创建一个数组，
//实现函数init（）初始化数组、
//实现empty（）清空数组、
//实现reverse（）函数完成数组元素的逆置。
//要求：自己设计函数的参数，返回值。

void init_array(int a[], int len)
{
	int i =0;
	for (; i < len; i++)
		scanf("%d", &a[i]);
}

void empty_array(int a[], int len)
{
	int i = 0;
	for (; i < len; i++)
	{
		a[i] = 0;
	}
}

void reverse_array(int a[], int len)
{
	int temp = 0, i = 0, j=len - 1;
	while (i <= j)
	{
		temp=a[i];a[i]=a[j];a[j]=temp;
		i++;
		j--;
	}
}

void print_array(int a[], int len)
{
	int i = 0;
	for (i = 0; i < len; i++)
		printf("%4d", a[i]);
	printf("\n");
}
void test4()
{
	int a[10];
	init_array(a, 10);
	print_array(a, 10);

	reverse_array(a, 10);
	print_array(a, 10);

	empty_array(a, 10);
	print_array(a, 10);

}
//5.实现一个函数，判断一个数是不是素数。
int is_prime(int num)
{
	// need math.h
	int i = 2;
	if (num <= 1) return 0;
	for (i = 2; i <=(int)sqrt(num); i++)
	{
		if (num % i == 0)
		{
			return 0;
		}
	}
	return 1;
}

void test5()
{
	int arr[10] = {	1,2,3,4,5,6,7,8,9,10};
	int i = 0;
	for (; i < 10; i++)
	{
		printf("%d is %s \n", arr[i], is_prime(arr[i])? "prime": "not prime");
	}
	printf("\n");
}

int main()
{
	//test1();
	//test2();
	//test3();
	//test4();
	test5();
	return 0;
}

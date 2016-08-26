/*************************************************************************
	> File Name: test_17.c
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月26日 星期五 23时15分42秒
 ************************************************************************/

#include<stdio.h>
#include <assert.h>


//1.编写一个函数实现n^k，使用递归实现
float pow_n_k(float n, int k)
{
	assert(n >= 0  );
	if (k  <= 0)
	{
		return 1.0;
	}
	else
	{
		return n * pow_n_k(n, --k);
	}
}

void test_pow_n_k()
{
	printf("8--> result:%f\n", pow_n_k(2,3));
}




//2. 写一个递归函数DigitSum(n)，输入一个非负整数，返回组成它的数字之和，例如，调用DigitSum(1729)，则应该返回1+7+2+9，它的和是19
//

int DigitSum(int num)
{
	if (num <= 0)
	{
		return 0;
	}
	else
	{
		return num %10 + DigitSum(num / 10);
	}
}

void test_DigintSum()
{

	printf("19-->result:%d\n", DigitSum(1729));
}

//3. 编写一个函数reverse_string(char * string)（递归实现）
//实现：将参数字符串中的字符反向排列。
//要求：不能使用C函数库中的字符串操作函数。
//

void reverse_string(char s[], int len)
{
	if (s && s < s + len -1)
	{
		char temp = *s;
		*s = *(s + len -1);
		*(s + len - 1) = temp;
		reverse_string(s+1, len -= 2);
	}
}


void test_reverse_string()
{
	char s[] = "nihao sunshine";
	printf("%s\n", s);
	reverse_string(s, sizeof(s) - 1);
	printf("%s\n", s);
}

int main()
{
	//test_pow_n_k();
	//test_DigintSum();
	test_reverse_string();
	return 0;
}

#include <stdio.h>
//1 将数组A中的内容和数组B 中的内容交换
void arraySwap(int* a1, int* a2, int len)
{
	int i = 0, temp;
	for (; i < len; i++)
	{
		temp = a1[i]; 
		a1[i] = a2[i];
		a2[i] = temp;
	}
}

void test_arraySwap()
{
	int a1[10] = {1,2,3,4,5,6,7,8,9,10};
	int a2[10] = {10,9,8,7,6,5,4,3,2,1};
	arraySwap(a1, a2, sizeof(a1)/sizeof(a1[0]));
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", a1[i]);
	}
	printf("\n");
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", a2[i]);
	}
	printf("\n");
}

//2 获得一个数二进制序列中所有偶数位和奇数位，分别输出二进制序列
void binEvenOdd(unsigned int num)
{
	unsigned int i = 1;
	i <<= 31;
	while (i >0)
	{
		printf("%d",(num&i)>0);
		i >>= 1;
	}

	printf("\neven:\n");

	i = 1;
	i <<= 31;
	while (i >0)
	{
		printf("%d",(num&i)>0);
		i >>= 2;
	}
	printf("\nodd :\n");
	
	i = 1;
	i <<= 30;
	while (i >0)
	{
		printf("%d",(num&i)>0);
		i >>= 2;
	}

	printf("\n");



}


void test_binEvenOdd()
{
	int x = 14;
	binEvenOdd(x);
}
//3 将三个数字按从小到大输出

void threeCout(int *a)
{
	int  i = 0;
	for (; i < 3; i++)
	{
		int index = i - 1;
		int temp = a[i];
		while (index >= 0 && a[index] > temp)
		{
				a[index + 1] = a[index];
				index--;
		}
		a[index + 1] = temp;
	}
}

void test_threeCount()
{
	int a[] = {3,2,1};
	threeCout(a);
	for (int i = 0; i < 3; i++)
	{
		printf("%d  ", a[i]);
	}
	printf("\n");

}

//4 求两数的最大公约数
// a/b1 = q1...r1
// a = b1*q1   + r1
// a = (r1*q2 + r2)* q1 + r1  if r2 == 0  r1 is ret  // b1 = r1*q2 + r2
// a = ((r2*q3 + r3)*q2 + r2)*q1 + r1   if r3 == 0  r2 is ret // r1 = r2*q3 + r3

//default  a> b
int max_measure(int a, int b)
{
	int r , q;
	if (a <= 0 || b <=0)
	{
		return -1;
	}
	if (b > a)
	{
		int tmp = a; a = b; b = tmp;
	}

	do
	{
		q = a / b;
		r = a % b;
		a = b;
		b = r;
	}while (r != 0);
	return a;
}

void test_max_measure()
{
	int ret = max_measure(14, 5); // 1
	printf("%d\n", ret);
	 ret = max_measure(24, 16); // 8
	printf("%d\n", ret);
}




int main()
{
	//test_arraySwap();
	//test_binEvenOdd();
	//test_threeCount();
	test_max_measure();
	return 0;

}



/*************************************************************************
	> File Name: test_10.c
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月18日 星期四 22时35分33秒
 ************************************************************************/

#include<stdio.h>

//1 折半查找
// 在升序数组中找元素 存在返回下标 不存在返回-1
//

int find_binary(const int arr[], const int len, const int dest)
{
	int left = 0;
	int right = len - 1;
	int mid = len >> 2;
	if (dest < arr[0] || dest > arr[len - 1])
	{
		return -1;
	}

	while (left <= right)
	{
		if (dest < arr[mid])
		{
			right = mid - 1;
		}
		else if (dest > arr[mid])
		{
			left = mid + 1;
		}
		else
		{
			return mid;
		}
		mid = left + ((right -left)>>2);
	}

	return -1;
}

void test_1()
{
	int arr[] = {1,2,3,4,5,6,7,8,9};
	int i = find_binary(arr,9, 7 );
	printf("7---------result: %d\n", arr[i]);
}

//2 从字符串提取子字符串

int my_substr(char dst[], const char src[], int start, int len )
{
	if (dst == NULL || src == NULL || len < 0 || start < 0)
	{
		return -1;
	}
	int i = 0, j = 0, num = 0;	
	while(src[i++] != '\0')
	{
		num++;
	}
	if (start >= num)
	{
		return -1;
	}

	i = start;
	while (src[i] != '\0' && i - start < len)
	{
		dst[j++] = src[i++];
	}
	dst[j] = '\0';
	return j;
}

void test_2()
{
	char src[] = "aabbccdd";
	char buf[20];
	int num = 0;
	num =  my_substr( buf,  src, 2, 4 );
	printf("4 num:%d,   buf: %s\n",num,  buf);

	num =  my_substr( buf,  src, 2, 8 );
	printf("6 num:%d,   buf: %s\n",num,  buf);
}

//3 有一个分数序列
//       2/1+3/2+5/3+8/5+13/8+…
//  求出这个数列前 20 项的和。

float sum_seq()
{
	float num = 2;
	float den = 1;
	int i = 0;
	float sum = 0;
	while (i++ < 20)
	{
		sum +=num / den;
		float tmp = num;
		num += den;
		den = tmp;
	}
	return sum;
}

void test_3()
{
	printf("sum: %f\n", sum_seq());
}
//4 一个球从 100 米高的地方自由落下，每次落地后反跳回原高度的一半，再落下，再反弹。求第10次落地时，共经过多少米，第 10 次反弹多高。

void get_height()
{
	float prev_height = 100;
	float now_height = prev_height / 2;
	int i = 1;
	float sum = prev_height;
	//while (i++ < 2)
	while (i++ < 10)
	{
		sum += prev_height;// 2*now_height
		now_height = prev_height / 2;
	}
	printf("now height %f, sum %f\n", now_height, sum);
}



void test_4()
{
	get_height();// 200 50
}

//5 猴子吃桃问题。猴子第一天摘下若干个桃子，当即吃了一半，好不过瘾，又多吃了一个。第二天早上又吃了剩下的桃子的一半，又多吃了一个。以后每天都吃了前一天剩下的一半零一个，到第 10 天早上想再吃的时候，就剩下一个桃子。求第一天共摘多少个桃子。
//


// now = prev -  (prev / 2 + 1 ) 
// now = prev/2 - 1
// prev = 2*(now + 1)
void get_peach()
{
	int i = 1;
	int sum = 1;
	while (i++ < 10)
	{
		sum = (sum + 1)<<2;
	}
	printf("peach num %d\n", sum);
}
 void test_5()
{
	get_peach();
}
int main()
{
	//test_1();
	//test_2();
	//test_3();
	//test_4();
	test_5();
              

	return 0;
}

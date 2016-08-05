#include <stdio.h>

// 1.编写一个程序，从标准输入读取几行输入。每行输入都要打印到标准输出上，前面加上行号。
// 在编写这个程序的时候要使这个程序能够处理的输入行的长度没有限制。

typedef struct S
{
	char data;
	struct S* next;
}S, *Sp;

void test_1()
{
	char ch;
	int flag = 1;
	int i = 1;
	while ((ch = getchar()) != EOF)
	{
		if (flag == 1)
		{
			printf("%d.", i);
			i++;
			flag = 0;
		}

		putchar(ch);
		if (ch == '\n')
		{
			flag = 1;
		}
	}
}


void test_1_by_array()
{
	char arr[50][20] = {0};
	int i =0;
	for (i = 0; i < 50; i++)
	{
		gets(arr[i]);
		if (arr[i] == '\0')
		{
			break;
		}
	}

	for (i = 0; i < 50; i++)
	{
		if (arr[i] == '\0')
		{
			break;
		}
		printf("%d.",i);
		puts(arr[i]);
		
	}

}

// 2. 编这样一个程序，用户输入10个整数，程序找出其中的最大值和最小值
void findMaxMin()
{
	int a[10], max, min;
	int i = 0;
	printf("输入10个数 ，求最大和最小\n");
	for (i = 0; i < 10; i++)
	{
		scanf("%d", &a[i]);
	}

	min = max= a[0];
	for (i = 1; i < 10; i++)
	{
		if (a[i]> max)
		{
			max =a[i];
		}

		if (a[i] < min)
		{
			min = a[i];
		}
	}

	printf("最大值%d      最小值%d\n", max, min);
}

////////////////////////////////////////////////////////////
//
//
//                  经典 全排列 算法 
//
// 
// 3 写程序求解：
// 有1、2、3个数字，能组成多少个互不相同且无重复数字的三位数？打印出来？
void swap_char(char* c1, char* c2)
{
	char tmp = *c1;
	*c1 = *c2;
	*c2 = tmp;
}
char arr[4] = "123";

void print_123(int i)
{
	if (arr[i] == '\0')
	{
		printf("%s \n", arr);
	}
	int j = 0;
	for (j = i; j < 3; j++)	
	{
		swap_char(&arr[i], &arr[j]);
		print_123(i+1);
		swap_char(&arr[i], &arr[j]);
	}
}


// 4. 测试 机器 的 大小端
typedef union
{
	unsigned short int value;
	unsigned char c ;
} un;

int isBig()
{
	un u;
	u.value = 1;

	if (u.c == 1)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int main()
{

//	test_1();
//	test_1_by_array();
    // findMaxMin();
	//
	//print_123(0);
	printf("%s\n",isBig() == 1? "big": "little");
	return 0;
}






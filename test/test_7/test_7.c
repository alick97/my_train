/*************************************************************************
	> File Name: test_7.c
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月06日 星期六 23时41分13秒
 ************************************************************************/

#include<stdio.h>

// 1
//   
// 5位运动员参加了10米台跳水比赛，有人让他们预测比赛结果
// A选手说：B第一，我第三。
// B选手说：我第二，E第四。
// C选手说：我第一，D第二。
// D选手说：C最后，我第三。
// E选手说：我第四，A第一。
// 比赛结束后，每位选手都说对了一半，请编程确定比赛的名次。

void get_position()
{
	int a = 1, b = 1, c = 1, d = 1, e = 1;
	for (a = 1; a < 6; a++)
	{
		for (b = 1; b < 6; b++)
		{
			for (c = 1; c < 6; c++)
			{
				for (d = 1; d < 6; d++)
				{
					for (e = 1; e < 6 ; e++)
					{
						if (a != b && a != c && a != d && a != e &&\
							b != c && b != d && b != e &&\
							c != d && c != e &&\
							d != e)
						{
							if ((b == 1) + (a == 3) == 1 &&\
								(c == 1)+ (d == 2) == 1 &&\
								(c == 5) + (d == 3) == 1 &&\
								(e == 4)+ (a == 1) == 1)
							{
								printf("a:%d b:%d c:%d d:%d, e:%d\n", a,b,c,d,e);
							}
						}
					}

				}
			}
		}
	}

	
}

//2
//日本某地发生了一件谋杀案，警察通过排查确定杀人凶手必为4个嫌疑犯的一个。以下为4个嫌疑犯的供词。
//A说：不是我。
//B说：是C。
//C说：是D。
//D说：C在胡说
//已知3个人说了真话，1个人说的是假话。
//现在请根据这些信息，写一个程序来确定到底谁是凶手。

void find_criminal()
{
	int a, b, c, d;
	for (a = 0; a < 2;a++ )
	{
		for (b =0;b < 2; b++)
		{
			for (c = 0; c < 2; c++)
			{
				for (d = 0; d < 2; d++)
				{
					if (a+b+c+d == 1)
					{
						if ( (a == 0) + (c == 1) + (d == 1) +(d ==0) == 3 )
						{
							printf("a:%d    b:%d    c:%d   d:%d\n", a, b, c, d);
						}
					}
				}
			}
		}
	}
}


//////////////////----更好的方法--------------
void find_criminal_op()
{
	char criminal ;
	for (criminal = 'A'; criminal <= 'D'; criminal++)
	{
		if ((criminal != 'A') + (criminal == 'C') + (criminal == 'D')\
				+ (criminal != 'D') == 3)
		{
			printf("criminal is : %c\n", criminal);
		}
	}
}

//3
//在屏幕上 打印杨辉三角
#define NUM 9
void print_trianglei()
{
	int i,j;
	int a[NUM][NUM];
	for (i = 0; i < NUM; i++)
	{
		a[i][0] = a[i][i] = 1;
	}

	for (i = 2; i < NUM; i++)
	{
		for (j = 1; j < i; j++)
		{
			a[i][j] = a[i - 1][j] + a[i - 1][j - 1];
		}
	}

	for (i = 0; i < NUM; i++)
	{
		for (j = 0; j < (4*NUM)/2 - i - 4; j++)
		{
			printf(" ");
		}
		for (j = 0; j <= i; j++)
		{
			printf("%4d", a[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	//get_position();
	//find_criminal();
//	find_criminal_op();
	print_trianglei();
	return 0;
}

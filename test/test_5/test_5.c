#include <stdio.h>
#include <string.h>
#include <math.h>
/*
1.在屏幕上输出以下图案：
				*
			   ***
			  *****
			 *******
			*********
		   ***********
		  *************
		   ***********
			*********
			 *******
			  *****
			   ***
				*
*/

void print_x()
{
	char x[] = "                 ";
	int mid = strlen(x)/2;
	int l = mid - 1;
	int r = mid + 1;
	x[mid] = '*';
	printf("%s\n",x);
	while (l >= 0 && r < strlen(x))
	{
		sleep(1);
		x[l] = x[r] = '*';
		printf("%s\n",x);
		l--;
		r++;
	}
	while (l < r)
	{
		sleep(1);
		l++;
		r--;
		x[l] = x[r] = ' ';
		printf("%s\n",x);
	}

}

/*
	2.求出0～999之间的所有“水仙花数”并输出。“水仙花数”是指一个三位数，其各位数字的立方和确好等于该数本身，如；153＝1＋5＋3?，则153是一个“水仙花数”。
*/
	/*
	在数论中，水仙花数（Narcissistic number）也称为自恋数、自幂数、阿姆斯壮数或阿姆斯特朗数（Armstrong number），是指一N位数，其各个数之N次方和等于该数。
	例如153、370、371及407就是三位数的水仙花数，其各个数之立方和等于该数：
	153 = 1^3 + 5^3 + 3^3。
	370 = 3^3 + 7^3 + 0^3。
	371 = 3^3 + 7^3 + 1^3。
	407 = 4^3 + 0^3 + 7^3。
	*/

int find_shuixianhuashu(int x)
{
	int a1, a2, a3;
	if (x < 100 || x > 999)
	{
		return 0;
	}

	a1 = x % 10;
	a2 = (x/10) % 10;
	a3 = (x/100)% 10;
	if (pow(a1,3) + pow(a2, 3) + pow(a3, 3) == x)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}

void shuixian_0_999()
{
	int i = 100;
	for (; i < 1000; i++)
	{
		if(find_shuixianhuashu(i))
		{
			printf("%d    ", i);
		}
	}
	printf("\n");
}
/*
 *
	3.求Sn=a+aa+aaa+aaaa+aaaaa的前5项之和，其中a是一个数字，例如：2+22+222+2222+22222
*/

int get_a_aaaaa(int a)
{
	int i, Sn = 0;
	const int num = a;
	for (i = 0; i < 5; i++)
	{
		Sn += a;
		//error a = a + a*10;
		a = a*10 + num;
	}
	return Sn;
}
/*
4.编写一个程序，它从标准输入读取C源代码，并验证所有的花括号都正确的成对出现。
*/
int check_brackets(char a[])
{
	char b[50];
	int i = 0, j = 0;
	for (i = 0; i < strlen(a); i++)
	{
		if (a[i] == '{' && j < 50)
			b[j++]=a[i];
		if (a[i] == '}' )
		{
			if ( (j - 1) >= 0 && b[j - 1] == '{')
			{
				j--;
			}
			else
			{
				return 0;
			}
		}
	}
	if (j == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void check_bracks()
{
	char str[] = "           ";
	do
	{
		printf(":>");
		scanf("%s", str);
		if (strncmp(str, "quit", 4) == 0)
		{
			break;
		}
		printf("brackets is %s\n",(check_brackets(str) == 1) ? "ok" : "not ok");
	}while (1);

}
/*
5.编写程序模拟三次密码输入。
*/


void check_pwd()
{
	char pwd[7] = "123456";
	char input[7];
	int i = 0;
	do
	{
		printf("\r                     ");
		printf("\r请输入密码:>>");
		scanf("%6s", input);
		if (strncmp(pwd, input, 6) == 0)
		{
			printf("\r 登录成功！");
			break;
		}
		else{
			printf("\r 密码错误 还有%d次机会    ", 2 - i);
			fflush(stdout);
			sleep(3);
		}
		i++;
	}while (i < 3);
	printf("\n");
}

/*
6.编写猜数字游戏
*/

void game_num()
{
		int num;
		int x = 0;
		printf("-----猜 0-1000 之间的数字-----\n");
			srand(time(NULL));
		num = rand()%1000;
		int flag2 = 1;
		while (flag2)
		{

		printf("请输入数字 :>");
			scanf("%d", &x);
			if(x > num)
			{
				printf("\n猜大了\n");
			}
			else if (x < num)
			{
printf("\n猜小了\n");
			}
			else
			{
				printf("you win\n");
				break;
			}
		}
}
int main()
{

	//print_x();
	//shuixian_0_999();
//	int ret = get_a_aaaaa(1);
//	printf("ret:%d\n", ret);
//check_bracks();
//check_pwd();
game_num();
	return 0;
}

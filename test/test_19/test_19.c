/*************************************************************************
	> File Name: test_19.c
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月28日 星期日 23时21分56秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void int_pri_char(int n)
{
    if (n < 10)
	{
		putchar(n + '0');
		return ;
	}
	else
	{
		int_pri_char(n / 10);
	}
	putchar(n % 10 + '0');
}

void my_printf(const char s[], ...)
{
	if (!s) return;
	va_list arg;
	int count = 0;
	int i = 0;
	int j = 0;
	int temp = 0;
	char *ss = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == 'C' || s[i] == 'S' || s[i] == 'D')
		{
			++count;
		}
		i++;
	}
	va_start(arg, s);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == 'C' && j < count)
		{
			temp = va_arg(arg, int);
			putchar(temp);
			j++;
		}
		else if (s[i] == 'D' && j < count)
		{
			temp = va_arg(arg, int);
			if (temp < 0)
			{
				putchar('-');
				temp = 0 - temp;
			}
			int_pri_char(temp);
			j++;
		}
		else if (s[i] == 'S' && j < count)
		{
			ss = va_arg(arg, char*);
			while (*ss != '\0')
			{
				putchar(*ss);
				ss++;
			}
			j++;
		}
		else if (s[i] == '\\' && s[i+1] == 'n')
		{
			putchar('\n');
			i++;
		}
		else if (s[i] == '\\' && s[i + 1] == 't')
		{
				putchar('\t');
				i++;
		}
		else
		{
			putchar(s[i]);
		}
		i++;
	}
	va_end(arg);
}


int main()
{
my_printf("S D C C \n \t hello world \n\n", "abcd" ,-1455, 'v', 'f');
	return 0;
}

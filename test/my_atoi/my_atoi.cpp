#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <assert.h>
bool isInvalid = false;

int my_atoi(const char* str)
{
	if (NULL == str)
	{
		return 0;
	}

	int result = 0;
	int sign = 1;

	if ('0' <= str[0] && str[0] <= '9' || ('-' == *str || '+' == *str))
	{
		if ('+' == *str || '-' == *str)
		{
			if ('-' == *str)
			{
				sign = -1;
			}
			str++;
		}
	}
	else
	{
		isInvalid = true;
		return 0;
	}

	while ('0' == *str)
	{
		str++;
	}


	int count = 0;
	while ('0' <= *str && *str <= '9')
	{
		count++;
		result = result * 10 + *str - '0';
		str++;
	}
	// 防止溢出 最大支持9位十进制数
	if (count > 9)
	{
		isInvalid = true;
	}

	return sign * result;
}


int main()
{
	char s1[50]="+2147483647";
	printf("%d\n",	my_atoi(s1));

	char s2[50]="-00000000000002147483647";
	printf("%d\n",	my_atoi(s2));
	system("pause");
	return 0;
}
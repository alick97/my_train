#include <stdio.h>
#include <assert.h>
#include <string.h>
//1.模拟实现strncat

char * my_strncat(char *dest, char *src, int n)
{
	assert(dest && src);
	int len = strlen(dest);
	int i = 0;
	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[len + i] = src[i];
	}

	dest[len + i] = '\0';
	return dest;
}

void test_my_strncat()
{
	char str1[50] = "nihao";
	char str2[50] = " sunshine";
	my_strncat(str1, str2, 6);
	printf("str cat :   %s\n", str1);
}

//2.模拟实现strstr
char * my_strstr(const char *dest, const char *src)
{
	assert(dest && src);
	const char* p_dest = dest;
	const char* p_src = src;
	const char* p_ret = dest;
	while (*p_ret)
	{
		p_dest = p_ret;
		while (*p_dest++ == *p_src++)
		{
			if (*p_src == '\0')
			{
				return (char*)p_ret;
			}
		}

		p_ret++;
		p_src = src;
	}

	return NULL;
}

void test_strstr()
{
	char str1[] = "nihao sunshine hello";
	char str2[] = " sunshine hello";
	char str3[] = "nihao sun note";
	
	
	char *ret = my_strstr(str1, str2);
	if (ret)
	{
		printf("%s\n", ret);
	}
	else
	{
		printf("not found \n");
	}
	ret = my_strstr(str1, str3);

	if (ret)
	{
		printf("%s\n", ret);
	}
	else
	{
		printf("not found \n");
	}
}


//3.
//二维数组中的查找，杨氏矩阵
//题目：
//在一个二维数组中，每行都按照从左到右的递增的顺序排序。每列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个数组和一个数，判断数组中是否包含这个数。
//例如：
//二维数组
//1 2 3
//4 5 6
//7 8 9
//查找数字7.
//


int search_in_matrix(int arr[][3], int x, int y, int target)
{
	int x_pos = 0;
	while (x_pos < x && y >= 0)
	{
		if (target == arr[x_pos][y])
		{
			return 1;
		}
		else if (target < arr[x_pos][y])
		{
			y--;
		}
		else
		{
			x_pos++;
		}
	}
	return 0;
}

void test()
{
	int arr[][3] = {{1,2,3},{4,5,6},{7,8,9} ;
}

int main()
{
	//test_my_strncat();
	test_strstr();
	return 0;
}

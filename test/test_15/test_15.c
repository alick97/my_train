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
//char * my_strstr(const char *dest, const char *src)
//{
//	assert(dest && src);
//	const char* p_dest = dest;
//	const char* p_src = src;
//	const char* p_ret = dest;
//	while (*p_ret)
//	{
//		p_dest = p_ret;
//		while (*p_dest++ == *p_src++)
//		{
//			if (*p_src == '\0')
//			{
//				return (char*)p_ret;
//			}
//		}
//
//		p_ret++;
//		p_src = src;
//	}
//
//	return NULL;
//}
//
//

// 常用经典 实现方法
char *my_strstr(const char* str1, const char *str2)
{
	char *cp = (char*)str1;
	char *s1,*s2;
	
	if (!*str2) // 这个if 不多余 对于"" "" 的处理 不是NULL  而是s1""的地址
	{
		return ((char*) str1);
	}

	while (*cp)
	{
		s1 = cp;
		s2 = (char*) str2;

		while (*s1 && *s2 && !(*s1-*s2))
		{
			s1++;
			s2++;
		}

		if (!*s2)
		{
			return cp;
		}
		cp++;
	}
	return NULL;
}


void test_strstr()
{
	char str1[] = "nihao sunshine hello";
	char str2[] = " sunshine hello";
	char str3[] = "nihao sun note";
	char str4[] = "";	
	
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
	ret = my_strstr(str1, str4);

	if (ret)
	{
		printf("%s\n", ret);
	}
	else
	{
		printf("not found \n");
	}

	char str_1[] = "";
	char str_2[] = "";
	ret = my_strstr(str_1, str_2);

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

//   从 右上角  到 左下角 搜索
int search_in_matrix(int arr[][3], int x, int y, int target)
{
	int x_pos = 0;
	while (x_pos < x && y > 0)
	{
		if (target == arr[x_pos][y-1])
		{
			return 1; // success
		}
		else if (target < arr[x_pos][y-1])
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

void test_search()
{
	int arr[][3] = {{1,2,3},{4,5,6},{7,8,9}};
		printf("find 7 : %d\n", search_in_matrix(arr, 3,3, 7));
		printf("find -1 : %d\n", search_in_matrix(arr, 3,3, -1));
}

int main()
{
	//test_my_strncat();
	test_strstr();
	//test_search();
	return 0;
}

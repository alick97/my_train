/*************************************************************************
	> File Name: test_13.c
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月21日 星期日 21时47分53秒
 ************************************************************************/

#include<stdio.h>
#include <assert.h>
#include <string.h>

//字符串替换空格：请实现一个函数，把字符串中的每个空格替换成“％20”。例如输入“we are happy.”，则输出“we%20are%20happy.”。
//

void replace_black(char * str)
{
	assert(str);
	int blank_num = 0;
	int old_len;
	int new_len;
	char  *cur = str;
	old_len = strlen(str);

	while (*cur)
	{
		if (*cur == ' ')
		{
			blank_num++;
		}
		cur++;
	}
	new_len = blank_num*2 + old_len;
	while (old_len < new_len) // 从后向前复制
	{
		if (str[old_len] !=  ' ' )
		{
			str[new_len--] = str[old_len--];
		}
		else // ' '
		{
			str[new_len--] = '0';
			str[new_len--] = '2';
			str[new_len--] = '%';
			old_len--;
		}
	}
}

int main(){
	char str[] = "we are happy.";
	printf("old str:    %s\n", str);
	replace_black(str);
	printf("new str:    %s\n", str);
	return 0;
}

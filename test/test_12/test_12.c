#include <stdio.h>


//1.有一个字符数组的内容为:"student a am i",请你将数组的内容改为"i am a student".
//要求：
//不能使用库函数。只能开辟有限个空间（空间个数和字符串的长度无关）。
//
//将字符串如"i am a student" 反转为"student a am i"(就地)  
////注：单词间空格可以任意多
////但比如：I_love__you 变成you__love_I 而不是you_love__I


#include <assert.h>
//交换两个单字符 
void char_swap(char *a , char *b)
{
	assert(a != NULL && b != NULL);
	char tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

// 交换[begin, end]区间的字符
void str_reverse(char *begin, char *end)
{
	assert(begin != NULL && end != NULL);
	while (begin < end)
	{
		char_swap(begin, end);
		begin++;
		end--;
	}
}


void string_reverse(char *str)
{
	assert(str != NULL);
	char *begin = str;
	char *end = str;
	char *wordend = NULL;
	while (*end)
	{
		end++;
	}
	if (end == str)
	{
		return;
	}
	end--;
	// 整体反转
	str_reverse(begin, end);
	end = begin = str;
	do
	{
		if (*end == ' ' || *end == '\0')
		{
			str_reverse(begin, end - 1);
			begin = end;
			while (*begin == ' ' && *begin != '\0')
			{
				begin++;
			}
			end = begin;
		}
			end++;
	}while (*(end-1) != '\0');
}

int main()
{
	char s[] = "student a am i";
	string_reverse(s);
	printf("%s\n", s);
	char ss[] = "a               bc d";
	string_reverse(ss);
	printf("%s\n", ss);
	return 0;
}

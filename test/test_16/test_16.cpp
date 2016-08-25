//1 实践：
//在终端输入多行信息，找出包含“ould”的行，并打印该行。
//如：
//Au,love could you and I with fate conspire
//To grasp this sorry scheme of things entire,
//Would not we shatter it to bitd – and then.
//
//在终端输出上述的文字，输出
//Au,love could you and I with fate conspire
//Au,love could you and I with fate conspire
//To grasp this sorry scheme of things entire,
//Would not we shatter it to bitd – and then.
//Would not we shatter it to bitd – and then.
//
//=========================================
#include <stdio.h>
#include <string.h>
int get_line(char line[], int limit)// line output arg
{
	int ch;
	int i = 0;
	while (limit && ((ch = getchar()) != '\n') && (ch != EOF))
	{
		line[i] = ch;
		i++;
		limit--;
	}

	if (ch == '\n')
	{
		line[i] = ch;
		line[++i] = '\0';   // for strstr
	}
	return i;
}

int test_1()
{
	char line[1024];
	while (get_line(line, 1023))
	{
		if (strstr(line, "ould") != NULL)
		{
			printf("%s", line);
		}
	}

	return 0;
}

//2 =========================================
//.实现一个函数int my_atoi(char s[]),可以将一个字符串转换为对应的整数。
//
//比如：输入字符串“1234”，返回数字1234。
//      输入字符串“+1234”，返回数字1234.
//	        输入字符串“-1234”，返回数字-1234.
//==========================================
long long StrToIntCore(const char *digit, bool minus);

enum Status { kValid = 0, KInvalid};
int g_nStatus = kValid;

int StrToInt(const char *str)
{
	g_nStatus = KInvalid;
	long long num = 0;

	if (str != 0 && *str != '\0')
	{
		bool minus = false;
		if (*str == '+')
		{
			str++;
		}
		else if (*str == '-')
		{
			str++;
			minus = true;
		}

		if (*str != '\0') // '+' '-'
		{
			num = StrToIntCore(str, minus);
		}
	}

	return (int) num;
}

long long StrToIntCore(const char *digit, bool minus)
{
	long long num = 0;

	while (*digit != '\0')
	{
		if (*digit >= '0' && *digit <= '9')
		{
			int flag = (minus ? -1:1);
			num = num * 10 + flag * (*digit - '0');

			if ((!minus && num > 0x7FFFFFFF) || (minus && num < (signed int)0x80000000)) 
			{
				num = 0;
				break;
			}
			digit++;
		}
		else
		{
			num = 0;
			break;
		}
	}

	if (*digit == '\0')
	{
		g_nStatus = kValid;
	}
	return num;
}





void test_StrTOInt()
{
	char* s1 = "+";
	printf("%s   -> g_nStatus:%d   int: %d\n",s1,g_nStatus, StrToInt(s1));
	char* s2 = "++"; 
	printf("%s   -> g_nStatus:%d   int: %d\n",s2,g_nStatus, StrToInt(s2));
	char* s3 = "asdsd";
	printf("%s   -> g_nStatus:%d   int: %d\n",s3,g_nStatus, StrToInt(s3));
	char* s4 = "1212454";
	printf("%s   -> g_nStatus:%d   int: %d\n",s4,g_nStatus, StrToInt(s4));
	char* s5 = "-111111111111111111111111111111111111111";
	printf("%s   -> g_nStatus:%d   int: %d\n",s5,g_nStatus, StrToInt(s5));
	char* s6 = "-1212121";
	printf("%s   -> g_nStatus:%d   int: %d\n",s6,g_nStatus, StrToInt(s6));
}






//3.实现一个函数itoa（int n,char s[]），将整数n这个数字转换为对应的字符串，保存到s中。
//
#include <assert.h>
void Itoa(int n, char s[])
{
	assert(s);
	int i = 0;
	if (n < 0)
	{
		s[i++] = '-';
		n = 0 - n;
	}
	else
	{
		s[i++] = '+';
	}

	while (n)
	{
		s[i++] = n % 10 + '0';
		n = n/10;
	}
	s[i] = '\0';

	char *left = s+1;
	char *right = &s[i-1];

	while (left < right)
	{
		char tmp = *left;
		*left = *right;
		*right = tmp;
		left++;
		right--;
	}
}


void test_itoa()
{
	char s[20];
	int i = -96547;
	Itoa(i, s);
	printf("%d ->  %s\n", i, s);
	 i = 45787;
	Itoa(i, s);
	printf("%d ->  %s\n", i, s);
}
//4.编写一个函数itob（int n,char s[], int b）,将整数n转换为以b进制的数。保存到s中。
//
void Itob(int n, char s[], int b)
{
	int i = 0;
	assert(s && b > 1);
	if (n < 0)
	{
		s[i++] = '-';
		n = 0 - n;
	}
	else
	{
		s[i++] = '+';
	}

	while (n)
	{
		s[i++] = n % b + '0';
		n /= b;
	}
	s[i] = '\0';

	// swap
	char* left = &s[1];
	char* right = &s[i - 1];

	while (left < right)
	{
		char tmp = *left;
		*left = *right;
		*right = tmp;
		left++;
		right--;
	}
}
void test_itob()
{
	char s[20];
	int i = 15;
	Itob(i, s, 2);
	printf("%d ->  %s\n", i, s);
	 i = -16;
	Itob(i, s, 2);
	printf("%d ->  %s\n", i, s);
}


//
//5.编写一个程序统计输入字符串中：
//各个数字、空白字符、以及其他所有字符出现的次数。
void get_symbol_num(char s[])
{
	if (s == NULL) return;
	int i = 0;
	int num_num = 0;
	int space = 0;
	int other_num = 0;
	
	while (s[i] != '\0')
	{
		if (s[i] == ' ')
		{
			space++;
		}
		else if (s[i] > '0' && s[i] <= '9')
		{
			num_num++;
		}
		else
		{
			other_num++;
		}
		i++;
	}

	printf("the character number of \"%s\" ：  num:%d, space:%d, other:%d\n", s, num_num, space , other_num);

}

void test_5()
{

	char s[] = "abcd  123123  &&*";
	get_symbol_num(s);
}

int main()
{
//	test_1();
//test_StrTOInt();
//test_itoa();
//test_itob();
test_5();
	return 0;
}

#include <stdio.h>
#include <string.h>
#include <assert.h>

//1.每瓶汽水1元，两个空瓶可以置换一瓶汽水，现在有20元，最多能喝多少瓶汽水。（编程实现）。
//
int get_count()
{
	int left = 20;
	int count = 20;
	while (left > 1)
	{
		count += (left>>1);
		left = left%2 + (left>>1);
	}

	printf("count :%d , left :%d\n", count , left);
}



//
//2.实现一个函数，可以左旋字符串中的k个字符。
//AABCD左旋一个字符得到ABCDA
//AABCD左旋两个字符得到BCDAA
//


void reverse(char str[], int len)
{
	assert(str && len >= 0);
	int left = 0;
	int right = len -1;
	char tmp;
	while (left < right)
	{
		tmp = str[left];
		str[left] = str[right];
		str[right] = tmp;
		left++;
		right--;
	}
}

int leftRotate(char str[], int x)
{
	assert(str);
	int len = strlen(str);
	if (x < 0 || x > len)
		return -1;

	// rotate left part 
	reverse(str, x);
	// rotate right part
	reverse(str + x , len -x );

	// rotate all
	reverse(str, len);

	return 0;
}

void test_leftRotate()
{
	char str[] = "abcdefg";
	leftRotate(str, 2);
	printf("%s\n", str);

}
//3.判断一个字符串是否为另外一个字符串旋转之后的字符串。
//例如：给定s1 ＝ AABCD和s2 = BCDAA，返回1，给定s1=abcd和s2=ACBD，返回0.
//
//
//AABCD左旋一个字符得到ABCDA
//AABCD左旋两个字符得到BCDAA
//
//AABCD右旋一个字符得到DAABC
//AABCD右旋两个字符得到CDAAB
//

int isleftRotate(char dest[], char src[])
{
	assert(dest && src);
	int len = strlen(src);
	int i = 0;
	if (len != strlen(dest))
	{
		return 0;
	}

	do 
	{
		if (!strncmp(dest, src, len))
		{
			return 1;
		}
		leftRotate(src, 1);
		i++;
	}while (i < len);

	return 0;
}

void test_isleftRotate()
{
	char s1[] = "abcd";
	char s2[] = "bcda";
	char s3[] = "bacd";
	printf("%s, %s,   %d\n",s1, s2, isleftRotate(s1,s2));
	printf("%s, %s,   %d\n",s1, s2, isleftRotate(s1,s3));
}

int main()
{
	//iget_count();
	
 test_isleftRotate();
	test_leftRotate();
	return 0;
}

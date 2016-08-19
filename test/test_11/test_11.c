#include <stdio.h>
#include <math.h>

//1.编程实现：
//两个int（32位）整数m和n的二进制表达中，有多少个位(bit)不同？ 
//输入例子:
//1999 2299
//输出例子:7

int count_one(int num)
{
	int count = 0;
	while (num)
	{
		count++;
		num = num & (num - 1); // 将二进制中从最低位出现的首个1变成零 【比按位比较速度快】
	}
	return count;
}

int find_byte_difference(int num1, int num2)
{
	int num = num1 ^ num2;// 问题转化为 找 二进制中1的个数
	return count_one(num);
}

void test_1()
{
	printf("1999 -a 2299  = 7?    result: %d\n", find_byte_difference(1999,2299));
	printf("-1 one count 32 ? result:%d\n", count_one(-1));
}




//2.编写函数：
//unsigned int  reverse_bit(unsigned int value);
//这个函数的返回 值value的二进制位模式从左到右翻转后的值。
//
//如：
//在32位机器上25这个值包含下列各位：
//00000000000000000000000000011001
//翻转后：（2550136832）
//10011000000000000000000000000000
//程序结果返回：
//          2550136832

unsigned int reverse_bit(unsigned int value)
{
	/*    method 1   */
/*	unsigned int rev_val = 0;
	int i = 0;
	while (i++ < 32)
	{
		rev_val <<= 1;
		rev_val |= (value & 1);
		value >>= 1;
	}
	return rev_val;
*/
	/*  method 2*/
	int i = 0;
	unsigned int sum = 0;
	for (i = 0; i < 32; i++)
	{
		sum += ((value >> i) & 1) * pow(2, 31 - i);
	}
	return sum;
}

void test_2()
{
	// 25----->2550136832
	printf("25----->2550136832?  %dresult:%u\n", 25, reverse_bit(25));
}




//
//3.不使用（a+b）/2这种方式，求两个数的平均值。
//

void test_3()
{
	int num1 = 10;
	int num2 = 20;
	int avg1 = (num1 & num2) + ((num1 ^ num2) >> 1);// 相当于  
	// 相同位 保留 （&）    不同位相加除以2 (^>>)   
	
	int avg2 = num1 - ((num1 - num2) >> 1);
	printf("15 ? result: %d, %d\n", avg1, avg2);
}



//4.一组数据中只有一个数字出现了一次。
//其他所有数字都是成对出现的。请找出这个数字。（使用位运算）

int find_d(int arr[] , int len)
{
	int i = 0;
	int tmp  = 0 ;
	for (; i < len; i++)
	{
		tmp ^= arr[i]; // a^b^a == b
	}

	return tmp;
}

void test_4()
{
	int arr[11] = {1,1,2,2,3,3,4,4,5,5,6};
	printf("6 ? result: %d\n", find_d(arr, 11));
}

//5、【加强版】
//一个整型数组里除了两个数字之外，其他的数字都出现了两次。请写程序找出这两个只出现一次的数字。
//
//[异或运算的性质：任何一个数字异或它自己都等于0 ]
//
//[有了上面简单问题4的解决方案之后，我们回到原始的问题。如果能够把原数组分为两个子数组。在每个子数组中，包含一个只出现一次的数字，而其他数字都出现两次。如果能够这样拆分原数组，按照前面的办法就是分别求出这两个只出现一次的数字了。 
//
//我们还是从头到尾依次异或数组中的每一个数字，那么最终得到的结果就是两个只出现一次的数字的异或结果。因为其他数字都出现了两次，在异或中全部抵消掉了。由于这两个数字肯定不一样，那么这个异或结果肯定不为0，也就是说在这个结果数字的二进制表示中至少就有一位为1。我们在结果数字中找到第一个为1的位的位置，记为第N位。现在我们以第N位是不是1为标准把原数组中的数字分成两个子数组，第一个子数组中每个数字的第N位都为1，而第二个子数组的每个数字的第N位都为0。(这两个数字不同，意味着为1的那个位是相异的)
//
//
//

void test_5()
{
	int arr[] = {2,2,3,3,-1,5};
	int i = 0;
	int result = 0;
	int num1 = 0;
	int num2 = 0;
	int len = sizeof(arr)/ sizeof(arr[0]);
	for (i = 0; i < len ; i++)
	{
		result ^= arr[i];
	}

	// 找第一个相异 的位置
	unsigned int index = 1;
	while (index)
	{
		if (result & index)
		{
			break;
		}
		index <<= 1;
	}

	//按照index  分 两组
	i = 0;
	for (; i < len; i++)
	{
		if (arr[i] & index)
		{
			num1 ^= arr[i];
		}
		else
		{
			num2 ^= arr[i];
		}
	}

	printf("num1 :%d, num2 :%d\n", num1, num2);
}

int main()
{
//	test_1();
//	test_2();
//	test_3();
//	test_4();
	test_5();
	return 0;
}

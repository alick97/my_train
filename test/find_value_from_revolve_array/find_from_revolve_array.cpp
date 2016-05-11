#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
/**
 * 从有序递增旋转数组45679123 中找到数字6的位置
 * 数组递增 但有旋转
 * 二分查找思想
 * 时间复杂度小于O(N)
 * {7,8,9,10,1,2,3,4,5,6}
 *************/

int find_revolve_array(const int arr[], int len, int value)
{
	if (NULL == arr || len < 0)
	{
		throw exception("Invalid input");
		return 0;
	}

	int left = 0;
	int right = len - 1;
	int mid = -1;

	while (left <= right)
	{
		mid = (left - right) / 2 + right; // 不要用 left / 2 + right / 2   因为(5 + 7)/2 = 6  而 (5/2 + 7/2) = 5

		if (arr[mid] == value)
		{
			return mid;
		}
		else if (value < arr[mid]) 
		{
			if (value >= arr[left]) // 在左边
			{
				right = mid -1;
			}
			else // 在右边
			{
				left = mid + 1;	
			}
		}
		else
		{
			if (value <= arr[right])
			{
				left = mid + 1;
			}
			else
			{
				right = mid - 1;
			}
		}
	}

	return -1;
}

void test()
{
	int arr[] = {7,8,9,10,1,2,3,4,5,6};
	int index = find_revolve_array(arr, 10, 7);
}

int main()
{
	test();
	return 0;
}

#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <assert.h>
using namespace std;

#include"sort.h"
/**********
 * 常见比较排序算法
 * 选择排序、堆排序、冒泡排序、选择排序、快速排序、归并排序
 * 
 *****************/

//1  直接插入排序
void InsertSort(int* arr, int size)
{
    assert(NULL != arr && size > 0);

    for (int i = 0; i < size; i++)
    {
        int tmp = arr[i];
        int end = i - 1;

        while (end >= 0 && arr[end] > tmp)
        {
            arr[end + 1] = arr[end];
            end--;
        }

        arr[end + 1] = tmp;
    }
}

void test_InsertSort()
{
    int arr[10] = {2,5,4,9,3,6,8,7,1,0};
    InsertSort(arr, 10);
}


//2 希尔排序
// 2 5 4 9 3 6 8 7 1 0
// 2     9     8     0
//   5     3     7
//     4     6     1

void ShellSort(int* arr, int length)
{
    assert(arr && length > 0);
    //int gap = 3;
    int gap = length;
    while (gap > 1)
    {
        gap = gap /3 + 1; // gap = 1 相当于最后一次用了直接插入排序

        for (int i = 0; i < length - gap; i++) // 注意i++ 不是i+=gap
        {
            int end = i;
            int tmp = arr[i + gap];

            while (end >= 0 && arr[end] > tmp)
            {
                arr[end + gap] = arr[end];
                end -= gap;
            }
            arr[end + gap] = tmp;
        }
    }
}

void test_ShellSort()
{
    int arr[10] = {2,5,4,9,3,6,8,7,1,0};
    ShellSort(arr, 10);
}

//3 选择排序

void SelectSort(int* arr, int size)
{
    assert(NULL != arr && size > 0);

    for (int i = 0; i < size; i++)
    {
        int min = i;

        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }

        swap(arr[i], arr[min]);
    }
}

void test_SelectSort()
{
    int arr[10] = {2,5,4,9,3,6,8,7,1,0};
    SelectSort(arr, 10);
}

// 选择排序同时排最大和最小【记录下标交换有坑】
//void SelectSort_min_max(int* arr, int size)
//{
//    assert(NULL != arr && size > 0);
//    int left = 0;
//    int right = size - 1;
//
//    while (left < right)
//    {
//        int min = left;
//        int max = left;
//        for (int i = left; i <= right; i++)
//        {
//            if (arr[i] < arr[min])
//            {
//                min = i;
//            }
//
//            if (arr[i] > arr[max])
//            {
//                max = i;
//            }
//        }
//            swap(arr[left], arr[min]); // 有问题 【坑】如 最小的在最右边 or 最大值在最左边 9 5 2 4 3 1 交换时 先是【1】 5 2 4 3 9 然后 【9】 5 2 4 3 1
//            swap(arr[right],arr[max]);
//            // 解决方法 1 直接值交换 而不是 交换索引
//            // 解决方法 2 交换时判断一下
//            right--;
//            left++;
//        
//    }
//}

 // 解决方法 1 直接值交换 而不是 交换索引
//void SelectSort_min_max(int* arr, int size)
//{
//    assert(NULL != arr && size > 0);
//    int left = 0;
//    int right = size - 1;
//
//    while (left < right)
//    {
//        //int min = arr[left];
//        //int max = arr[left];
//        for (int i = left; i <= right; i++)
//        {
//            if (arr[i] < arr[left])
//            {
//               // min = i;
//                 // 解决方法 1 直接值交换 而不是 交换索引
//                swap(arr[i], arr[left]);
//            }
//
//            if (arr[i] > arr[right])
//            {
//               // max = i;
//                swap(arr[i], arr[right]);
//            }
//        }
//           
//            right--;
//            left++;
//        
//    }
//}

   // 解决方法 2 交换时判断一下
void SelectSort_min_max(int* arr, int size)
{
    assert(NULL != arr && size > 0);
    int left = 0;
    int right = size - 1;

    while (left < right)
    {
        int min = left;
        int max = left;
        for (int i = left; i <= right; i++)
        {
            if (arr[i] < arr[min])
            {
                min = i;
            }

            if (arr[i] > arr[max])
            {
                max = i;
            }
        }
        swap(arr[left], arr[min]);

        // 解决方法二 判断一下 手动处理 最大值在最左边 或 最小值在最右边的请况
        if (max == left)
        {
            max = min;
        }

        swap(arr[right],arr[max]);
         
        right--;
        left++;
        
    }
}

void test_SelectSort_min_max()
{
    // int arr[10] = {0,1,2,3,4,5,6,7,8,9}; //ok
     int arr[10] = {9,5,2,4,3,4,7,8,6,1}; // error
    SelectSort_min_max(arr, 10);
}

//4 堆排序
// 向下调整
void _AdjustDown(int* arr, int parent, int size) 
{
    int child = parent * 2 + 1;

    while (child < size)
    {
        if (child + 1 < size && arr[child + 1] > arr[child])
        {
            child++;
        }

        if (arr[child] > arr[parent])
        {
            swap(arr[child], arr[parent]);
            parent = child;
            child = parent * 2 + 1;
        }
        else
        {
            break;
        }
    }
}

void HeapSort(int* arr, int size)
{
    assert(NULL != arr && size > 0);

    // 建大堆
    for (int i = (size - 2) / 2 - 1; i >= 0; i--)
    {
        _AdjustDown(arr, i, size);
    }

    while (size > 1)
    {
        swap(arr[0], arr[size - 1]);
        _AdjustDown(arr, 0, --size);
    }
}

void test_HeapSort()
{
    int arr[10] = {2,5,4,9,3,6,8,7,1,0};
    HeapSort(arr, 10);
}


// 5 冒泡排序
void BubbleSort(int* arr, int size)
{
    assert(NULL != arr && size > 0);

    for (int i = 0; i < size; i++)
    { 
        bool isOrder = true; // 已经有序
        for (int j = 0; j < size - i -1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                isOrder = false;
            }
        }

        if (isOrder)
        {
            break;
        }
    }
}

void test_BubbleSort()
{
    int arr[10] = {2,5,4,9,3,6,8,7,1,0};
    BubbleSort(arr, 10);
}

// 快速排序
// [begin , end] 一次划分
int Partition(int* arr, int begin, int end)
{
    assert(NULL != arr);

    int tmp = end;
    int left = begin;
    int right = end - 1;

    while (left < right)
    {
        while (left < right && arr[left] < arr[tmp])
        {
            left++;
        }

        while (left < right && arr[right] > arr[tmp])
        {
            right--;
        }

        swap(arr[left], arr[right]);
    }

    if (arr[left] > arr[tmp])
    {
        swap(arr[left], arr[tmp]);
        return left;
    }

    return tmp;
}


void _QuickSort(int* arr, int begin, int end)
{
    assert(arr);

    if (begin < end)
    {
        int index = Partition(arr, begin, end);
        _QuickSort(arr, begin, index - 1);
        _QuickSort(arr, index + 1, end);
    }
}

void QuickSort(int* arr, int size)
{
    assert(NULL != arr && size > 0);

    _QuickSort(arr, 0, size - 1);
}

void test_QuickSort()
{
    int arr[10] = {2,5,4,9,3,6,8,7,1,0};
    QuickSort(arr, 10);
}

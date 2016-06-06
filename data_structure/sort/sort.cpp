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

// 方法二 挖坑法
// [begin end]
int Partition_2(int* arr, int begin, int end)
{
    assert(arr);
    int key = arr[end];

    while (begin < end)
    {
        while (begin < end && key >= arr[begin])
        {
            begin++;
        }
        arr[end] = arr[begin];

        while (begin < end && arr[end] >= key)
        {
            end--;
        }

        arr[begin] = arr[end];
    }
    // 5 6
    arr[end] = key;
    return end;
}

// 方法二 prev、cur法
// 与前两种不同 不利用right做索引 同时也适合【链表排序】
// [begin end]
int Partition_3(int* arr, int begin, int end)
{
    assert(arr);
    int cur = begin;
    int prev = cur - 1;
    int key = arr[end]; // 【待用三数取中法优化】

    while (cur < end)
    {
        if (arr[cur] < key && ++prev != cur) // prev 在大数第一个
        {
            swap(arr[prev],arr[cur]);
        }

        ++cur;
    }

    swap(arr[++prev], arr[end]);
    return prev;
}


void _QuickSort(int* arr, int begin, int end)
{
    assert(arr);

    if (begin < end)
    {
        //int index = Partition(arr, begin, end);
       //  int index = Partition_2(arr, begin, end); // 挖坑法
        int index = Partition_3(arr, begin, end); //  prev、cur法
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


// 快排优化
// 1 三数取中法
// 2 当区间长度较小时 使用别的排序 如直接插入排序 减少递归次数

// 【优化1 三数取中法 防止已经排好序的 成为最差的情况O(N^2)】
int GetMid(int* arr,int left, int mid, int right)
{
    assert(arr);
    if (arr[left] < arr[mid])  // left < mid
    {
        if (arr[right] < arr[left])
        {
            return right;
        }
        else if (arr[right] > arr[mid])
        {
            return mid;
        }
        else
        {
            return right;
        }
    }
    else  //  mid < left
    {
        if (arr[right] < arr[mid])
        {
            return mid;
        }
        else if (arr[right] > arr[left])
        {
            return left;
        }
        else
        {
            return right;
        }
    }
}


int Partition_OP(int* arr, int begin, int end)
{
    assert(arr);
    int cur = begin;
    int prev = cur - 1;
    // 【优化1 三数取中法】
    int mid = GetMid(arr, begin, begin +(begin - end)/2, end);
    int key = arr[mid]; // 
    ///////////////////////////////////////////////////////
    while (cur < end)
    {
        if (arr[cur] < key && ++prev != cur) // prev 在大数第一个
        {
            swap(arr[prev],arr[cur]);
        }

        ++cur;
    }

    swap(arr[++prev], arr[end]);
    return prev;
}


void _QuickSort_OP(int* arr, int begin, int end)
{
    assert(arr);
    // 【优化2  当区间长度较小时 使用别的排序 如直接插入排序 减少递归次数】
    if (begin >= end)
    {
        return ;
    }

    if (end - begin <= 10)
    {
        // 调用直接插入排序
        InsertSort(arr + begin, end - begin + 1); 
    }
    else
    {
        //int index = Partition(arr, begin, end);
       //  int index = Partition_2(arr, begin, end); // 挖坑法
        int index = Partition_3(arr, begin, end); //  prev、cur法
        _QuickSort_OP(arr, begin, index - 1);
        _QuickSort_OP(arr, index + 1, end);
    }
}

void QuickSort_OP(int* arr, int size)
{
    assert(NULL != arr && size > 0);

    _QuickSort_OP(arr, 0, size - 1);
}

#include<Windows.h>
#include<time.h>
void test_QuickSort_OP()
{
    srand(time(0));
  
    int* arr = new int[100];

    for (int i = 0; i < 100; i++)
    {
        arr[i] = rand();
    }

    unsigned  int start_time = GetTickCount();
    QuickSort_OP(arr, 100);
    unsigned int end_time = GetTickCount();
    cout<<"time:"<<(end_time-start_time)<<endl;

    for (int i = 0; i < 100; i++)
    {
        cout<<arr[i]<<endl;
    }

    delete[] arr;
}


// 快排 【非递归】 利用stack
#include<stack>
void _QuickSort_NRe(int* arr, int left, int right)
{
    assert(arr);
    stack<int> s;
    s.push(left);
    s.push(right);

    while (!s.empty())
    {
        int end = s.top();
        s.pop();
        int start = s.top();
        s.pop();

        int div = Partition(arr, start, end);

        if (start < div - 1) // 至少两个数
        {
            s.push(start);
            s.push(div - 1);
        }

        if (div + 1 < end)
        {
            s.push(div + 1);
            s.push(end);
        }
    }
}

void test_QuickSort_NRe()
{
    int arr[10] = {2,5,4,9,3,6,8,7,1,0};
    _QuickSort_NRe(arr,0, 10 - 1);
}
// 归并排序
// 63    95  |  84    46 |  18   24 |  27  31 |  46
// 63    95  |  46    84 |  18   24 |  27  31 |  46
// 46 63 84 95           |     18 24 27 31 | 46
//           18 24 27 31 46 63 84 95       |   46
//                    18 24 27 31 46 46 63 84 95
// [left ,right]

// 合并（前提 两数组 有序）
void Merge(int* arr, int* tmp, int left,int mid, int right) // 合并
{
    assert(arr && tmp);
    int i = left;
    int index = mid + 1; // 第二组
    int begin = left; // 第一组

    while (begin <= mid && index <= right)
    {
        if (arr[begin] > arr[index])
        {
            tmp[i++] = arr[index++];
        }
        else
        {
            tmp[i++] = arr[begin++];
        }
    }

    // 可能剩下一组的部分 下面两个while只执行一个
    while (begin <= mid)
    {
        tmp[i++] = arr[begin++];
    }

    while (index <= right)
    {
        tmp[i++] = arr[index++];
    }

    // 排好后 赋值给arr
    for (int j = left; j <= right; j++)
    {
        arr[j] = tmp[j];
    }

}


void _mergeSort(int* arr,int* tmp, int left, int right)
{
    assert(arr && tmp);
    if (left < right)
    {
        int mid = left + (right - left)/2;
        // 使左右 小数组 有序
        _mergeSort(arr, tmp, left, mid);
        _mergeSort(arr, tmp, mid + 1, right);
        // 在左右有序的情况下 合并
        Merge(arr, tmp, left, mid, right); // 合并
    }
}


void MergeSort(int* arr, int n)
{
    assert(NULL != arr && n > 0);
    int* tmp = new int[n]; // 临时空间 存放排好的中间结果
    _mergeSort(arr, tmp, 0, n - 1);

    delete[] tmp;
}


void test_MergeSort()
{
    int arr[] = {63  ,  95  , 84  ,  46 ,  18 ,  24 ,  27 , 31 ,  46};
    MergeSort(arr, 9);
}


// 计数排序
// 1  如 知道范围 0-99  用哈希直接定址法
// 2 如范围100000-200000    则减去100000 进行下标映射
void CountSort(int* arr, int size)
{
    const int count = 100;
    int* tmp = new int[count];
    memset(tmp, 0, sizeof(int) * count);

    for (int i = 0; i < size; i++)
    {
        tmp[arr[i]] += 1;
    }

    int index = 0;
    for (int i = 0; i < count; i++)
    {
        while (tmp[i] > 0)
        {
            arr[index++] = i;
            tmp[i]--;
        }
    }
}

void test_CountSort()
{
    int arr[10] = {2,5,4,9,3,6,8,7,1,0};
    CountSort(arr, 10);
}

// 基数排序
int Maxbit(int* a, int size) // 计算数组中最大值的位数
{
    int bit = 1;
    int num = 10;

    for (int i = 0; i < size; i++)
    {
        // 100 3
        if (a[i] >= num)
        {
            bit++;
            num *= 10;
        }
    }

    return bit;
}

// 基数排序 有矩阵快速转置的影子
void RadixSort(int* arr, int size)
{
    int maxbit = Maxbit(arr, size);
    int* tmp = new int[size];
    int* start = new int[10]; //  起始位置
    int* count = new int[10]; // 次数 记录0-9 数字的次数
    int radix = 1; // 哪一位 1  10   100   1000
    for (int bit = 0; bit < maxbit; bit++)
    {
        for (int j = 0; j < 10; j++)
        {
            count[j] = 0;
        }

        for (int j = 0; j < size; j++)
        {
            int k = (arr[j]/radix) % 10; // 对应位置上的数字
            count[k]++;
        }
        // 计算start
        start[0] = 0;
        for (int i = 1; i < 10; i++)
        {
            start[i] = start[i - 1] + count[i - 1];
        }

        // 一趟排序 
        for (int i =0; i < size; i++)
        {
            int k = (arr[i]/radix) % 10;
            tmp[start[k]++] = arr[i];
        }

        // tmp 写回 arr
        for (int i = 0; i < size; i++)
        {
            arr[i] = tmp[i];
        }

        radix = radix * 10;
    }
    
    delete[] tmp;
    delete[] start;
    delete[] count;
}

void test_RadixSort()
{
    int arr[10] = {2,5,4,9,3,6,8,7,1,0};
     RadixSort(arr, 10);
}
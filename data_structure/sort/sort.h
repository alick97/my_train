#define _CRT_SECURE_NO_WARNINGS 1


// 插入排序
void InsertSort(int* arr, int size);
void test_InsertSort();

//2 希尔排序
// 2 5 4 9 3 6 8 7 1 0
// 2     9     8     0
//   5     3     7
//     4     6     1

void ShellSort(int* arr, int length);
void test_ShellSort();

//3 选择排序

void SelectSort(int* arr, int size);
void test_SelectSort();

// 选择排序同时排最大和最小
void SelectSort_min_max(int* arr, int size);
void test_SelectSort_min_max();

//4 堆排序
// 向下调整
void _AdjustDown(int* arr, int parent, int size) ;
void HeapSort(int* arr, int size);
void test_HeapSort();

// 5 冒泡排序
void BubbleSort(int* arr, int size);
void test_BubbleSort();


// 快速排序
// [begin , end] 一次划分
int Partition(int* arr, int begin, int end);
void QuickSort(int* arr, int size);
void _QuickSort(int* arr, int begin, int end);
void test_QuickSort();


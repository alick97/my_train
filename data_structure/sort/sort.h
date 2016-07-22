#pragma once

// 直接插入排序
void InsertSort(int*arr, int size);
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
// 快排优化
void QuickSort_OP(int* arr, int size);
void test_QuickSort_OP();

// 快排优化
void QuickSort_OP(int* arr, int size);
void test_QuickSort_OP();

int Partition_OP(int* arr, int begin, int end);
// 快排 【非递归】 利用stack
void _QuickSort_NRe(int* arr, int left, int right);
void test_QuickSort_NRe();


// 快排 【非递归】 利用stack
void _QuickSort_NRe(int* arr, int left, int right);
void test_QuickSort_NRe();
// 归并排序
void MergeSort(int* arr, int n);
void test_MergeSort();
// 计数排序
// 1  如 知道范围 0-99  用哈希直接定址法
// 2 如范围100000-200000    则减去100000 进行下标映射
void CountSort(int* arr, int size);
void test_CountSort();

// 基数排序 有矩阵快速转置的影子
void RadixSort(int* arr, int size);
void test_RadixSort();



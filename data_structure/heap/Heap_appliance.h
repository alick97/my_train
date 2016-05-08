#pragma once
#include <assert.h>
#include <time.h>
//堆的应用
// 1
// 百万个数据【N个】 不能一次调入内存 放在文件中 找前n个大的数
// 解法：先建n个数据的 【小堆】   把剩下的数据每次向里面push一个 然后再从里面每次pop一个  最后
// 剩下的n个 就是前n个大的数     【小堆特点 堆顶最小 每次把最小的弹出 所以留下的 就是大的】
// 时间复杂度 Nlog2 n     因为 log2 n 与N相比太小 所以 约为 N  



// 2
// 10000人中 发红包金额大的前100用户   【扩展 海量数据处理】
const int N = 10000;
const int k = 100;

void _ajustDown(int a[], int size,int parent)
{
	assert(a && size >= 0);

	int child = parent * 2 + 1;

	while (child < size)
	{
		if (child + 1 < size && a[child + 1] < a[child]) // 小堆
		{
			child++;
		}

		if (a[child] < a[parent])
		{
			swap(a[child], a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else 
		{
			break;
		}
	}
}


void GetTopK(int a[],int topk[],int k)	// topk 接收返回的最大的k个元素
{
	assert(a && k >= 0);
	//int topk[k];
	// 导入 前k个数据
	for (int i = 0; i < k; i++)
	{
		topk[i] = a[i];
	}

	// 建小堆
	for (int i = (k - 2)/2; i > 0; --i)
	{
		_ajustDown(topk, k, i);	// 向下调整
	}

	// 小堆顶换成 剩下的数据

	for (int i = k; i < N; i++)
	{
		if (a[i] > a[0])
		{
			topk[0] = a[i];
			_ajustDown(topk, k, 0);
		}
		else
		{
			continue;
		}	
	}
}


void test_topk()
{
	int a[N], topk[k];

	srand(time(0));

	for (int i = 0; i < k; i++)
	{
		a[i] = rand() % N;
	}

	for (int i = k; i < N; i++)
	{
		a[i] = N + i;
	}

	GetTopK(a,topk,k);

	cout<<topk[0]<<endl;
}


//3
// 堆排序
// heap.hpp 中
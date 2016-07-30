#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
/**
 *  堆
 
 *
 *
 *
 *
 ***/

#include<iostream>
#include<vector>
#include <assert.h>
#include"HuffmanTree.h"
using namespace std;

template<class T>
struct Less
{
    bool operator()(const T& l, const T& r)
    {
        return l < r;
    }
};

// 特化 T*
template<class T>
struct Less<T*>
{
    bool operator()(const T* l, const T* r)
    {
        return *l < *r;
    }
};

template<class T>
struct Greater
{
    bool operator()(const T& l, const T& r)
    {
        return l > r;
    }
};

template<class T, template<class> class Continer = Greater> //  默认大堆
class Heap
{
public:
    Heap(){};
    Heap(const T* a, int size);
    void Push(const T& x);
    void Pop();

	T& GetTop();
	bool Empty();
	size_t Size();
	void HeapSort(int size);

	void PrintHeap();
protected:
    void _AdjustDown(int parent);    //  向下调整
	void _AdjustDown(int parent, int size);
    void _AdjustUp(int child);   //  向上调整
protected:
    vector<T> _a;
    Continer<T> _com;
};

template<class T, template<class> class Continer>
Heap<T, Continer>::Heap(const T* a, int size)
{
    assert(a);

    for (int i = 0; i < size; i++)
    {
        _a.push_back(a[i]);
    }

    //  建堆
    for (int i = (_a.size() - 2) / 2; i > 0; i--)  
        //  _a.size()-1 为下标（从0开始）   找第一个非叶子结点   叶子节点看成堆  向上找叶子结点 每个结点向下调整
    {
        _AdjustDown(i); //  向下调整
    }
    _AdjustDown(0);
}

template<class T, template<class> class Continer>
void Heap<T, Continer>::_AdjustDown(int parent)
{
    int child = parent * 2 + 1;  //  左孩子
    int size = _a.size();

    while (child < size)    //  防止越界
    {
        if (child + 1 < size && _com(_a[child + 1], _a[child]))
        {
            ++child;    //  有右孩子 且右孩子大于左孩子
        }

        if (_com(_a[child], _a[parent]))
        {
            swap(_a[parent], _a[child]);
            //  下移
            parent = child;
            child = parent * 2 + 1;
        }
        else
        {
            //  因为下面是排好的堆
            break;
        }
    }
}



template<class T, template<class> class Continer>
void Heap<T,Continer>::Push(const T& x)
{
	_a.push_back(x);
	_AdjustUp(_a.size() - 1);
}


template<class T, template<class> class Continer>
void Heap<T, Continer>::_AdjustUp(int child)
{
	size_t parent = (child - 1) / 2;

	while (child > 0)	//	有坑 不要用parent >= 0 判断 因为size_t  parent=（0-1）/2 为比较大的正数 用 int的parent也可能死循环 当_com 比较用>=含等于时 
	{
			if (_com(_a[child], _a[parent]))
		{
			swap(_a[child], _a[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
}

template<class T, template<class> class Continer>
void Heap<T,Continer>::Pop()
{
	assert(!_a.empty());
	size_t size = _a.size();
	swap(_a[0],_a[size - 1]);	//	顶部和 最后一个交换 后面调整少一些
	_a.pop_back();
	_AdjustDown(0);
}

template<class T, template<class> class Continer>
T& Heap<T,Continer>::GetTop()
{
	assert(_a.size() > 0);
	return _a[0];
}

template<class T, template<class> class Continer>
bool Heap<T,Continer>::Empty()
{
	return (_a.size() == 0);
}

template<class T, template<class> class Continer>
size_t Heap<T,Continer>::Size()
{
	return _a.size();
}

template<class T, template<class> class Continer>
void Heap<T,Continer>::HeapSort(int size)	//	堆排序
{
	// 建大堆（这里一定是大堆  每次把堆顶排到后面）
	for (int parent = (size - 2) / 2; parent >= 0; --parent)
	{
		_AdjustDown(parent);
	}

	while(size > 1)
	{
		swap(_a[0], _a[size-1]); // 最大的放后面
		_AdjustDown(0, --size); // 忽略后面一个 堆大小少一个
	}
}

template<class T, template<class> class Continer>
void Heap<T,Continer>::_AdjustDown(int parent, int size)
{
	int child = parent * 2 + 1;
	while (child < size)
	{
		//	这里必须是大堆 所以不用仿函数
		if (child + 1 < size && _a[child + 1] > _a[child])
		{
			child++;
		}

		if (_a[child] > _a[parent])
		{
			swap(_a[child], _a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}


template<class T, template<class> class Continer>
void Heap<T,Continer>::PrintHeap()
{
	int size = Size();
	for (int i = 0; i < size; i++)
	{
		cout<<_a[i]<<" ";
	}
	cout<<endl;
}



void test_heap_creat()
{
    int array[] = {10, 16, 18, 12, 11, 13, 15, 17, 14, 19};
    size_t size = sizeof(array)/ sizeof(array[0]);
   // Heap<int, Greater> h(array, size);
	// Heap<int> h(array, size);
	Heap<int, Less> h(array, size);
	 h.Push(88);
	 h.Pop();
}

void test_heap_other()
{
	int array[] = {10, 16, 18, 12, 11, 13, 15, 17, 14, 19};
    size_t size = sizeof(array)/ sizeof(array[0]);
    Heap<int, Greater> h(array, size);
	h.PrintHeap();
	cout<<h.GetTop()<<endl;
	cout<<h.Size()<<endl;
	cout<<h.Empty()<<endl;
	h.HeapSort(10);
	h.PrintHeap();
}
	




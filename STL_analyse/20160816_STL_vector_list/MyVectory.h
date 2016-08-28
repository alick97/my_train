#pragma once
#include "MyAllocator.h"
#include "Construct.h"
#include "Uninitialized.h"


template <class T, class Alloc = Alloc>
class Vector
{
public:
    typedef T ValueType;
    typedef ValueType* Iterator; // 原生指针 直接作为 迭代器
    typedef const ValueType* ConstIterator;
    typedef ReverseIterator<Iterator> ReverseIterator;

	// 定义空间配置器
    typedef SimpleAlloc<ValueType, Alloc> DataAllocator;

   Vector()
        :_start(0)
        ,_finish(0)
        ,_endOfStorage(0)
    {}

   ~Vector()
   {
       Destroy(Begin(), End());
       DataAllocator::Deallocate(_start, _endOfStorage - _start);
   }


   void PushBack(const T& x)
   {
       _CheckStorage();
       *_finish = x;
       ++_finish;
   }

   void Insert(Iterator pos, const T& x )
   {
        _CheckStorage();

        if (pos < Begin() || pos > End())
        {
            return ;
        }

        Iterator cur = End() - 1;
        while (cur >= pos)
        {
            *(cur+1) = *(cur);
            --cur;
        }
        *pos = x;
        _finish++;
   }

   Iterator Erase(Iterator pos)
   {
      Iterator ret = pos+1;
        while (pos < (End() - 1))
        {
            *pos = *(pos+1);
            ++pos;
        }

        _finish--;

        return ret;

   }

   T& operator[](size_t index)
   {
    return _start[index];
   }

   size_t Size()
   {
        return _finish - _start;
   }

   Iterator Begin()
   {
       return _start;
   }

   ConstIterator Begin() const
   {
        return _start;
   }

   Iterator End()
   {
    return _finish;
   }

   ConstIterator End() const
   {
    return _finish;
   }

protected:
    void _CheckStorage()
    {
        if (_finish == _endOfStorage)
        {
            size_t size = Size();
            size_t newStorage = size * 2 + 3;
           /*
           T* tmp = new T[newStorage];

            // 应该类型萃取 提高效率 这里先简单拷贝
            if (_start)
            {
                for (size_t i = 0; i < size; ++i)
                {
                    tmp[i] = _start[i];
                }
                delete[] _start;
            }
            */
            // 改用空间适配器
            T* tmp = DataAllocator::Allocate(newStorage);
            // 类型萃取 进行初始化  高效 
            if (_start)
            {
                //vector的迭代器就是 指针 所以直接传tmp
                // UninitializedCopy中用到的ValueType 有特化版本   __TypeTraits< _Tp*>也用指针类型的特化版本
                UninitializedCopy(_start, _finish, tmp);
                Destroy(_start, _finish);
                DataAllocator::Deallocate(_start, _endOfStorage - _start);
            }

            _start = tmp;
            _finish = _start + size;
            _endOfStorage = _start + newStorage;
        }

    }

protected:
    Iterator _start;
    Iterator _finish; // 开区间 指向下标为size的结点
    Iterator _endOfStorage;
};


void PrintVector1(Vector<int>& v)
{
    Vector<int>::Iterator it = v.Begin();
    while (it != v.End())
    {
        //*it = 10;
        cout<<*it<<" "<<endl;
        ++it;
    }
    cout<<endl;
}

void PrintVector2(const Vector<int>& v)
{
    Vector<int>::ConstIterator it = v.Begin();
    while (it != v.End())
    {
      // error  *it = 10;
        cout<<*it<<endl;
        ++it;
    }
    cout<<endl;
}


void TestVector()
{
    Vector<int> v;
    v.PushBack(1);
    v.PushBack(2);
    v.PushBack(3);
    v.PushBack(4);

     v.Insert(v.End()-1,5);
     PrintVector1(v);
     v.Insert(v.End()-1,6);

    
    PrintVector1(v);
    //PrintVector2(v);

    Vector<int>::Iterator it = v.Erase(v.Begin());
    PrintVector1(v);
     it = v.Erase(v.Begin());
    PrintVector1(v);

    cout<<v[0]<<endl;
}


void TestVector_allocate()
{
	Vector<int> v;
	v.PushBack(1);
	v.PushBack(2);
	v.PushBack(3);
	v.PushBack(4);

	PrintVector1(v);
	PrintVector2(v);
}

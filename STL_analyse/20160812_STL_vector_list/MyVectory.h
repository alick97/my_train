#pragma once

template <class T>
struct Vector
{
    typedef T* Iterator; // 原生指针 直接作为 迭代器
    typedef const T* ConstIterator;
    //--------       未完待续             ----------
public:
   Vector()
        :_start(0)
        ,_finish(0)
        ,_endOfStorage(0)
    {}

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
            T* tmp = new T[newStorage];

            // 应该类型萃取 提高效率 这里先简单拷贝
            if (_start)
            {
                for (size_t i = 0; i < size; ++i)
                {
                    tmp[i] = _start[i];
                }
                delete _start;
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

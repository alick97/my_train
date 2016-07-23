#pragma once
/********
 * 模拟实现一个栈
******************/
#include <iostream>
using namespace std;
#include<assert.h>
template<class T>
class Stack
{
public:
    Stack();
    Stack(const Stack<T>& s);
    Stack<T>& operator=(Stack<T> s);
    void Push(const T& x);
    void Pop();
    T& Top();
    bool Empty();
    size_t Size();
    ~Stack();
protected:
    void _CheckCapacity();
protected:
    T* _a;
    size_t _top;
    size_t _capacity;
};

template<class T>
Stack<T>::Stack()
    :_a(NULL)
    ,_top(0)
    ,_capacity(0)
{}

template<class T>
Stack<T>::Stack(const Stack<T>& s)
{
    _capacity = s._capacity;
    _a = new T[_capacity];
    _top = s._top;
    for (int i = 0; i < _top; i++)
    {
        _a[i] = s._a[i];
    }

}

template<class T>
Stack<T>& Stack<T>::operator=(Stack<T> s)
{
    swap(_a, s._a);
    _top = s._top;
    _capacity = s._capacity;

    return *this;
}

template<class T>
void Stack<T>::Push(const T& x)
{
    _CheckCapacity();
    _a[_top] = x;
    _top++;
}

template<class T>
 void Stack<T>::Pop()
 {
     assert(_top > 0);
     _top--;
 }

 template<class T>
T& Stack<T>::Top()
{
    assert(_top > 0);
    return _a[_top - 1];
}

template<class T>
bool Stack<T>::Empty()
{
    return _top == 0;
}

template<class T>
size_t Stack<T>::Size()
{
    return _top;
}

template<class T>
 Stack<T>::~Stack()
 {
     if (_a != NULL)
     {
         delete[] _a;
         _a = NULL;
     }
 }


template<class T>
void Stack<T>::_CheckCapacity()
{
    if (_top == _capacity)
    {
        _capacity = _capacity * 2 + 3;
        T* tmp = new T[_capacity];

        for (size_t i = 0; i < _top; i++)
        {
            tmp[i] = _a[i];
        }

        delete[] _a;
        _a = tmp;

    }

}



void test_MyStack() 
{
	Stack<int> s1;
	s1.Push(1);
	s1.Push(2);
	s1.Push(3);
	s1.Push(4);

	int *p = new int[0];
	
	/*s1.Pop();
	s1.Pop();
	s1.Pop();
	s1.Pop();*/
	/*s1.Pop();
	s1.Pop();*/

	Stack<int> s2(s1);
	Stack<int> s3;
	s3 = s2;

    cout<<s2.Top()<<endl;
	cout<<s3.Top()<<endl;
	cout<<s3.Empty()<<endl;
	cout<<"size:"<<s3.Size()<<endl;

	s3.Pop();
	s3.Pop();
	s3.Pop();
	s3.Pop();
	cout<<s3.Empty()<<endl;

	cout<<"size:"<<s3.Size()<<endl;

}
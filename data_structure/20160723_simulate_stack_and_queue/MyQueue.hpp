#pragma once
/**************
 * 模拟实现队列
 * 用链表实现
************/
#include <iostream>
using namespace std;
#include<assert.h>
template<class T>
struct Node
{
    Node()
        :_next(NULL)
    {}

    Node(const T& x)
        :_data(x)
        ,_next(NULL)
    {}
    T _data;
    Node<T>* _next;
};

template<class T>
class Queue
{
public:
    Queue()
        :_head(NULL)
        ,_tail(NULL)
    {}

    Queue(const Queue<T>& q)
    {
        Node<T>* cur = q._head;
        Node<T>* p_newnode = NULL;

        if (cur != NULL)
        {
            p_newnode = new Node<T>(cur->_data);
            _head = p_newnode;
            cur = cur->_next;
        }

        while (cur != NULL)
        {
            p_newnode->_next = new Node<T>(cur->_data);
            p_newnode = p_newnode->_next;
            cur = cur->_next;
        }

        _tail = p_newnode;
    }

    ~Queue()
    {
        _destory();
    }

    Queue<T>& operator=(Queue<T> q)
    {
        swap(_head, q._head);
        swap(_tail, q._tail);

        return *this;
    }

    void Push(const T& x)
    {
        Node<T>* newNode = new Node<T>(x);

        if (_head == NULL)
        {
            _head = _tail = newNode;
        }
        else
        {
            _tail->_next = newNode;
            _tail =newNode;
        }
    }

    void Pop()
    {
        if (_head == NULL)
        {
            return;
        }

        if (_head == _tail)
        {
            delete _head;
            _head = _tail = NULL;
            return;
        }

        Node<T>* del = _head;
        _head = _head->_next;
        delete del;
    }

    T& Front()
    {
        assert(_head != NULL);
        return _head->_data;
    }

    T& Back()
    {
        assert(_tail != NULL);
        return _tail->_data;
    }

    bool Empty()
    {
        if (_head != NULL)
        {
            return false;
        }

        return true;

    }

    size_t Size()
    {
        size_t count = 0;
        Node<T>* cur = _head;
        while (cur != NULL)
        {
            cur = cur->_next;
            count++;
        }

        return count;
    }

protected:
    void _destory()
    {
        Node<T>* cur = _head;
        Node<T>* del = _head;
        while (cur != NULL)
        {
            cur = cur->_next;
            delete del;
            del = cur;
        }

        _head = _tail = NULL;

    }

protected:
    Node<T>* _head;
    Node<T>* _tail;
};

void test_queue()
{
	int f;
	int e;
	bool emp = false;
	size_t size = -1;
	Queue<int> q1;
	q1.Push(1);
	e = q1.Back();
	q1.Push(2);
	e = q1.Back();
	q1.Push(3);	
	e = q1.Back();
	q1.Push(4);
	e = q1.Back();

	Queue<int> q2(q1);
	Queue<int> q3;
	q3 = q2; 

	
	emp = q1.Empty();
	size = q1.Size();

	f = q1.Front();
	q1.Pop();
	f = q1.Front();
	q1.Pop();
	f = q1.Front();
	q1.Pop();
	f = q1.Front();
	q1.Pop();

	
	q1.Pop();

	emp = q1.Empty();
	size = q1.Size();

	

}
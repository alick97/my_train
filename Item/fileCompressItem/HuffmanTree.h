#pragma once

#include"Heap.h"
#include <assert.h>
#include <iostream>
using namespace std;
template <class T>
struct HuffmanNode
{
    HuffmanNode<T>* _left;
    HuffmanNode<T>* _right;
    T _weight; // 权重

    HuffmanNode()
        :_left(NULL)
        ,_right(NULL)
    {}

    HuffmanNode(T weight)
        :_left(NULL)
        ,_right(NULL)
        ,_weight(weight)
    {}

    bool operator<(const HuffmanNode<T>& h) const
    {
       return  _weight < h._weight;
    }

};


template <class T>
class HuffmanTree
{
    typedef HuffmanNode<T> Node;
public:
    HuffmanTree()
        :_root(NULL)
    {}

    HuffmanTree(const T* arr, size_t size, const T& invalid)
    {
        assert(arr);
        _root = _CreatTree(arr, size, invalid);
    }

    Node* GetRootNode()
    {
        return _root;
    }

    ~HuffmanTree()
    {
        _delete(_root);
    }

protected:
    Node*  _CreatTree(const T* arr, size_t size, const T& invalid)
    {
        assert(arr != NULL && size > 0);

        // 建小堆
        Heap<Node*, Less> heap;
        Node* parent = NULL; // 最小 和 次小相加结点指针

        for (size_t i = 0; i < size; i++)
        {
            if (arr[i] != invalid) // 重载operator!=
            {
                heap.Push(new Node(arr[i])); // 这里压的是指针 比较Less要特化一个T* 的特化版
            }
        }

        while (heap.Size() > 1)
        {
            Node* firstMin = heap.GetTop();
            heap.Pop();

            Node* secondMin = heap.GetTop();
            heap.Pop();

            parent = new Node(firstMin->_weight + secondMin->_weight); // 这里_weight 可能是结构体或其他 operator+要重载 在FileCompress.h 的 struct CharInfo中重载
            parent->_left = firstMin;
            parent->_right = secondMin;

            // 新计算结点 重新压入堆中
            heap.Push(parent);
        }

        return parent;
    }

    void _delete(Node* root)
    {
        if (root != NULL)
        {
            _delete(root->_left);
            _delete(root->_right);

            delete root;
        }
    }

private:
    Node* _root;
};
#pragma once

// 迭代器的型别

struct InputIteratorTag {};  // 只读迭代器
struct OutputIteratorTag {}; // 只写迭代器
struct ForwardIteratorTag : public InputIteratorTag {};     // 前向迭代器 
struct BidirectionalIteratorTag : public ForwardIteratorTag {}; // 双向迭代器
struct RandomAccessIteratorTag : public BidirectionalIteratorTag {}; // 随机访问迭代器


// 迭代器
template <class Category, class T, class Distance = int, class Pointer = T*, class Reference = T&>
struct Iterator
{
    typedef Category IteratorCategory; // 迭代器的类型
    typedef T ValueType; // 迭代器所指的对象的类型
    typedef Distance DifferenceType; // 两个迭代器之间的距离
    typedef Pointer Pointer; // 迭代器所指对象类型的指针
    typedef Reference Reference; //迭代器对象类型的引用
};


// Traits 提取各个迭代器所对应的型别

template <class Iterator>
struct IteratorTraits
{
    typedef typename Iterator::IteratorCategory IteratorCategory ;
    typedef typename Iterator::ValueType ValueType; 
    typedef typename Iterator::DifferenceType DifferenceType; 
    typedef typename Iterator::Pointer Pointer; 
    typedef typename Iterator::Reference Reference;  
};

// 偏特化 原生指针类型
template<class T>
struct IteratorTraits<T*>
{
    typedef RandomAccessIteratorTag IteratorCategory; // 迭代器的类型
    typedef T ValueType; // 迭代器所指的对象的类型
    //////////////////////////////////////////////////////////////
    typedef size_t  DifferenceType; // 两个迭代器之间的距离
    typedef T* Pointer; // 迭代器所指对象类型的指针
    typedef T& Reference; //迭代器对象类型的引用
};


// 偏特化 const原生指针类型
template<class T>
struct IteratorTraits<const T*>
{
    typedef RandomAccessIteratorTag IteratorCategory; // 迭代器的类型
    typedef T ValueType; // 迭代器所指的对象的类型
    //////////////////////////////////////////////////////////////
    typedef size_t  DifferenceType; // 两个迭代器之间的距离
    typedef const T* Pointer; // 迭代器所指对象类型的指针
    typedef const T& Reference; //迭代器对象类型的引用
};

// Distance 的实现
// _Distance 重载
template<class InputIterator>
//inline typename IteratorTraits<InputIterator>::DifferenceType
inline size_t _Distance(InputIterator first, InputIterator last, InputIteratorTag) // O(N)
{
    IteratorTraits<InputIterator>::DifferenceType n = 0;
    while (first != last)
    {
        ++first;
        ++n;
    }
    return n;
};

template<class InputIterator>
//inline typename IteratorTraits<InputIterator>::DifferenceType
inline size_t _Distance(InputIterator first, InputIterator last, RandomAccessIteratorTag) // O(1)
{
    IteratorTraits<InputIterator>::DifferenceType n = 0;
    /*while (first != last)
    {
        ++first;
        ++n;
    }*/
    return last - first;
};

//inline typename IteratorTraits<RandomAccessIterator>::DifferenceType
template<class InputIterator >
inline size_t Distance(InputIterator first, InputIterator last)
{
   // return _Distance(first, last, InputIterator::IteratorCategory());
    // InputIterator::IteratorCategory()想法很好 但是 对于Vector这种 Iterator是T* 的 不支持 因为Vector类外 就没有一个 与他相对用的类Iterator   他的Iterator只是T*的别名， 没有其他 Iterator 里面的类型定义 如 IteratorCategory 所以编译是不通过的
    //

    return _Distance(first, last, IteratorTraits<InputIterator>::IteratorCategory());
};

//void test()
//{
//    List<int> l1;
//    l1.PushBack(1);
//    l1.PushBack(2);
//    l1.PushBack(3);
//    l1.PushBack(4);
//    cout<<"List Distance"<<Distance(l1.Begin(), l1.End())<<endl;
//
//
//    Vector<int> v1;
//    v1.PushBack(1);
//    v1.PushBack(2);
//    v1.PushBack(3);
//    v1.PushBack(4);
//    cout<<"Vector Distance"<<Distance(v1.Begin(), v1.End())<<endl;
//}



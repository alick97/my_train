#pragma once
// 迭代器的型别

struct InputIteratorTag {};  // 只读迭代器
struct OutputIteratorTag {}; // 只写迭代器
struct ForwardIteratorTag : public InputIteratorTag {};     // 前向迭代器 
struct BidirectionalIteratorTag : public ForwardIteratorTag {}; // 双向迭代器
struct RandomAccessIteratorTag : public BidirectionalIteratorTag {}; // 随机访问迭代器


template <class T, class Distance>
struct InputIterator {
	typedef InputIteratorTag IteratorCategory;
	typedef T                  ValueType;
	typedef Distance           DifferenceType;
	typedef T*                 Pointer;
	typedef T&                 Reference;
};

struct OutputIterator {
	typedef OutputIteratorTag IteratorCategory;
	typedef void                ValueType;
	typedef void                DifferenceType;
	typedef void                Pointer;
	typedef void                Reference;
};

template <class T, class Distance> 
struct ForwardIterator {
	typedef ForwardIteratorTag IteratorCategory;
	typedef T                    ValueType;
	typedef Distance             DifferenceType;
	typedef T*                   Pointer;
	typedef T&                   Reference;
};


template <class T, class Distance>
struct BidirectionalIterator {
	typedef BidirectionalIteratorTag IteratorCategory;
	typedef T                          ValueType;
	typedef Distance                   DifferenceType;
	typedef T*                         Pointer;
	typedef T&                         Reference;
};

template <class T, class Distance>
struct RandomAccessIterator {
	typedef RandomAccessIteratorTag IteratorCategory;
	typedef T                          ValueType;
	typedef Distance                   DifferenceType;
	typedef T*                         Pointer;
	typedef T&                         Reference;
};

//
// 迭代器内嵌包含的5种相应的型别
// Iterator Category、Value Type、Difference Type、Pointer、Reference
// 这5种内嵌的型别定义，确保了能够更方便的跟STL融合。
// 且方便Iterator Traits的类型萃取
//
//////////////////////////////////////////////////////////////////////////////
//  ValueType（。。。。）由迭代器 获取迭代器中的数据类型【迭代器数据类型萃取】
template<class T, class Distance>
inline T* ValueType(const InputIterator<T, Distance>&)
{
    return (T*)(0);
}
template <class T, class Distance> 
inline T* ValueType(const ForwardIterator<T, Distance>&) {
	return (T*)(0);
}

template <class T, class Distance> 
inline T* ValueType(const BidirectionalIterator<T, Distance>&) {
	return (T*)(0);
}

template <class T, class Distance> 
inline T* ValueType(const RandomAccessIterator<T, Distance>&) {
	return (T*)(0);
}

template <class T>
inline T* ValueType(const T*) { return (T*)(0); }

////////////////////////////////////////////////////////////////////////////

// 迭代器
template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
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
inline typename IteratorTraits<InputIterator>::DifferenceType
_Distance(InputIterator first, InputIterator last, InputIteratorTag) // O(N)
{
    IteratorTraits<InputIterator>::DifferenceType n = 0;
    // 前向的 要一个一个算 如 List::iterator
    while (first != last)
    {
        ++first;
        ++n;
    }
    return n;
};

template<class RandomAccessIterator>
inline typename IteratorTraits<RandomAccessIterator>::DifferenceType 
_Distance(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIteratorTag) // O(1)
{
    return last - first;// 随机的迭代器 这里last 和 first 是指针  直接相减就行 如vector::Iterator
};


template<class InputIterator >
inline typename IteratorTraits<InputIterator>::DifferenceType
Distance(InputIterator first, InputIterator last)
{
   // return _Distance(first, last, InputIterator::IteratorCategory());
    // InputIterator::IteratorCategory()想法很好 但是 对于Vector这种 Iterator是T* 的 不支持 因为Vector类外 就没有一个 与他相对用的类Iterator   他的Iterator只是T*的别名， 没有其他 Iterator 里面的类型定义 如 IteratorCategory 所以编译是不通过的
    //

    return _Distance(first, last, IteratorTraits<InputIterator>::IteratorCategory());
};




/* Advance 的实现*/
template<class InputIterator, class Distance>
inline void _Advance(InputIterator &i, Distance n, InputIteratorTag)
{
    while (n--) ++i;
}

// 特化  双向迭代器
template<class BidirectionalIterator, class Distance>
inline void _Advance(BidirectionalIterator& i, Distance n, BidirectionalIteratorTag)
{
    if (n >= 0)
        while(n--) ++i;
    else
        while (n++) --i;
}

// 特化 随机迭代器
template<class RandomAccessIterator, class Distance>
inline void _Advance(RandomAccessIterator& i, Distance n, RandomAccessIteratorTag)
{
    i += n;
}


template <class InputIterator, class Distance>
inline void Advance(InputIterator &i, Distance n )
{
    _Advance(i, n, IteratorTraits<InputIterator>::IteratorCategory());
}


/****************
 * 反向迭代器的定义  ，反向迭代器是正向迭代器的一层封装
******************/

template<class Iterator>
class ReverseIterator
{
public:
    // 通过迭代器萃取器，萃取出正向迭代器中定义的基本类型
    typedef typename IteratorTraits<Iterator>::IteratorCategory IteratorCategory;
    typedef typename IteratorTraits<Iterator>::ValueType ValueType;
    typedef typename IteratorTraits<Iterator>::DifferenceType DifferenceType;
    typedef typename IteratorTraits<Iterator>::Pointer Pointer;
    typedef typename IteratorTraits<Iterator>::Reference Reference;

    typedef Iterator IteratorType;
    typedef ReverseIterator<Iterator> Self;
public:
    ReverseIterator() {};
    explicit ReverseIterator(IteratorType x) // explicit 防止强制类型转换 IteratorType类型直接转换成RecerseIterator
        :_current(x)
    {}

    Reference operator*() const
    {
        // 这里解引用时 取得是 当前位置的前一个数据
        // 因为 RBegin () == End()   REnd() == Begin()
        Iterator tmp = _current;
        return *--tmp;
    }

    Pointer operator->() const
    {
        return &(operator*());
    }

    Self& operator++()
    {
        --_current;
        return *this;
    }

    Self operator++(int)
    {
        Self tmp = *this;
        --_current;
        return tmp;
    }

    Self operator--()
    {
        ++_current;
        return tmp;
    }

    Self operator--(int)
    {
        Self tmp = *this;
        ++_current;
        return tmp;
    }

    bool operator != (const Self& x)
    {
        return _current != x._current;
    }



protected:
    Iterator _current;// 直接就是对正向迭代器的封装
};

#pragma once

#include"TypeTraits.h"

// 构造和释放单个对象
template <class T>
inline void Destroy(T* pointer)
{
	pointer->~T();
}

template <class T1, class T2>
inline void Construct(T1* p, const T2& value)
{
	new(p)T1(value);// new 的定址构造 在已经开辟的空间上 调用拷贝构造、构造
}

// 释放一组区间对象  ForwardIterator迭代器
template <class ForwardIterator>
inline void 
__DestroyAux(ForwardIterator first, ForwardIterator last, __FalseType) // __FalseType 不是 无关痛痒的类型 如 string
{
	for ( ; first < last; ++first)
		Destroy(&*first);// 利用迭代器 找到对象的地址
}

template <class ForwardIterator> 
inline void
__DestroyAux(ForwardIterator, ForwardIterator, __TrueType) {} // __TrueType 是 无关痛痒的类型 如 int char...

template <class ForwardIterator, class T>
inline void
__Destroy(ForwardIterator first, ForwardIterator last, T*)// T*不是需要的 重点是 获取T类型 通过ValueType获取T*
{
	typedef typename __TypeTraits<T>::HasTrivialDestructor TrivialDestructor; // 类型萃取
	__DestroyAux(first, last, TrivialDestructor());
}

template <class ForwardIterator>
inline void Destroy(ForwardIterator first, ForwardIterator last)
{
	__Destroy(first, last, ValueType(first));
}

inline void Destroy(char*, char*){}
inline void Destroy(wchar_t*, wchar_t*){}
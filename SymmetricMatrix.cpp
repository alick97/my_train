#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
/**************
 *	对称矩阵
 *
 *
 *
 ****/

template<class T>
class SymmetricMatrix
{
public:
	SymmetricMatrix(T* a, size_t n);
	~SymmetricMatrix();
	T& Access(size_t i, size_t j);
	void Display() const;
protected:
	size_t _size;
	T* _a;
	size_t _n;	//维数
};

template<class T>
SymmetricMatrix<T>::SymmetricMatrix(T* a, size_t n)
	:_size((n * (n + 1))/2)	// 注意数据定义顺序
	,_a(new T[_size])
	,_n(n)
{
	size_t index = 0;

	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			if (j <= i)
			{
				_a[index++] = a[(i * (i + 1))/2 + j];
			}
			else
			{
				break;	//	存下三角
			}
		}
	}
}

template<class T>
void SymmetricMatrix<T>::Display() const
{
	for (size_t i = 0; i < _n; ++i)
	{
		for (size_t j = 0; j < _n; j++)
		{
			if (j <= i)
			{
				cout<<_a[i * (i + 1) / 2 + j]<<" ";
			}
			else
			{
				cout<<_a[j * (j + 1) / 2 + i]<<" "; // 巧妙
			}
		}
		cout<<endl;
	}
}

template<class T>
SymmetricMatrix<T>::~SymmetricMatrix()
{
	if (_a)
	{
		delete[] _a;
		_n = 0;
		_size = 0;
	}
}

template<class T>
T& Access(size_t i, size_t j)
{
	if (j > i)
	{
		swap(i, j);
	}

	return _a[i * (i + 1) / 2 + j];
}

void test_Sym()
{
	int array[] = {0, 1, 0, 2, 1, 0, 3, 2, 1, 0, 4 ,3 ,2 ,1,0};
	//int array[] = {0, 1, 2, 3, 4, 5};
	SymmetricMatrix<int> s(array,	5);
	s.Display();

}

int main()
{
	test_Sym();
	return 0;
}
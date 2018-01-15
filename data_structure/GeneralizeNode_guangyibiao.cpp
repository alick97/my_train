#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <assert.h>
using namespace std;

enum Type
{
	HEAD,
	VALUE,
	SUB
};

struct GeneralizedNode
{
	Type _type;	//	类型
	GeneralizedNode* _next;	//	指向同层下一个结点

	union
	{
		//int _value;
		char _value;
		GeneralizedNode* _subLink;	//	指向子表的指针
	};

	GeneralizedNode(Type type = VALUE, const int value = 0)
		:_type(type)
		,_next(NULL)
		,_value(value)
	{}
};

class Generalized
{
public:
	Generalized()
		:_head(NULL)
	{}

	Generalized(const char* str)
		:_head(NULL)
	{
		_head = _CreateList(str);
	}

	void Print() const	
	{
		_Print(_head);
		cout<<endl;
	}

	size_t Size() const
	{
		return _Size(_head);
	}

	size_t Depth() const
	{
		return _Depth(_head);
	}

protected:
	GeneralizedNode* _CreateList(const char*& str);
	void _Print(GeneralizedNode* head) const;
	bool _IsValue(char ch);
	size_t  _Size(GeneralizedNode* head) const;
	size_t _Depth(GeneralizedNode* head) const;

protected:
	GeneralizedNode* _head;
};
bool Generalized:: _IsValue(char ch)
{
	if ((ch >= '0' && ch <= '9')
		|| (ch >= 'a' && ch <= 'z')
		|| (ch >= 'A' && ch <= 'Z'))
	{
		return true;
	}
	else
	{
		return false;
	}
}

GeneralizedNode* Generalized::_CreateList(const char*& str)	//	注意&
{
	assert(str);

	assert(*str == '(');
	// D = (a,b,(c,d),(e,(f),h))

	GeneralizedNode* head = new GeneralizedNode(HEAD);
	GeneralizedNode* cur = head;
	++str;
	
	while (*str != '\0')
	{
		if (*str == '(')	// 有子层
		{
			cur->_next = new GeneralizedNode(SUB);
			cur = cur->_next;
			cur->_subLink = _CreateList(str);	//	下一层
		}
		else if(_IsValue(*str))
		{
			cur->_next = new GeneralizedNode(VALUE, *str);
			cur = cur->_next;
			++str;
		}
		else if (*str == ')')
		{
			++str;	// **********更新上一层的str
			break;
		}
		else // 其他情况 *str为 逗号 空格 制表符 等
		{
			++str;
		}
	}

	return head;
}


void Generalized::_Print(GeneralizedNode* head)	const
{
	assert(head && head->_type == HEAD);
	GeneralizedNode* cur = head->_next;
	cout<<"(";
	while(cur)
	{
		if (cur->_type == VALUE)
		{
			cout<<cur->_value;
			cur = cur->_next;
			if (cur != NULL)
			{
				cout<<",";
			}
		}
		else if (cur->_type == SUB)
		{
			_Print(cur->_subLink);
			cur = cur->_next;
			if (cur != NULL)
			{
				cout<<",";
			}
		}
	}
	cout<<")";
}

size_t  Generalized::_Size(GeneralizedNode* head) const
{
	assert(head && head->_type == HEAD);
	GeneralizedNode* cur = head->_next;
	size_t count = 0;
	while(cur)
	{
		if (cur->_type == VALUE)
		{
			count++;
		}
		else if(cur->_type == SUB)
		{
			count += _Size(cur->_subLink);
		}

		cur = cur->_next;
	}

	return count;
}

size_t Generalized::_Depth(GeneralizedNode* head) const
{
	assert(head && head->_type == HEAD);
	GeneralizedNode* cur = head->_next;
	size_t depth = 1;
	while(cur)
	{
		if (cur->_type == SUB)
		{
			depth += _Depth(cur->_subLink);
		}

		cur = cur->_next;
	}

	return depth;
}

void test_G_chuangjian()
{
	char* str = "(a,b,(c,d))";
	Generalized g(str);

	g.Print();

	cout<<g.Size()<<endl;
	cout<<g.Depth()<<endl;
}

int main()
{
	test_G_chuangjian();

	return 0;
}
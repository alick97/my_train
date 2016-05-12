#define _CRT_SECURE_NO_WARNINGS 1
//#include <iostream>
#include "BigData.h"

BigData::BigData(INT64 value)
	:_value(value)
{
	INT64ToString();
}

BigData::BigData(const char *pData)
{
	if (NULL == pData)
	{
		assert(false);
		return;
	}

	// "1235464678"
	// "+123456789"
    // "+"
    // "       "
    // "000012312313"
	// "-12131313123"
	// "123123asdad1231213"
	// "a4546546"
	// "000000000"

    char *pStr = (char*)pData;
	char cSymble = pData[0]; // 符号位
	// 规范化 规定 :1第一位为符号 以后就只考虑其他位
	//              2 符号位后第一位非零
    //  分类：符号  非符号的
	if (cSymble == '+' || cSymble == '-')
	{
		pStr++;
	}
	else if (cSymble >= '0' && cSymble <= '9')
	{
		cSymble = '+';
	}
	else // 第一位非法
	{
		_value = UN_INT;
		return;
	}

	// 去除多余的0 如"0000123123132"
    while ('0' == *pStr)
	{
		++pStr;
	}

	// 调整strData大小  resize自己维护‘\0’ 这里加1是加符号为
	_strData.resize(strlen(pStr) + 1);
	_strData[0] = cSymble;

	// "122121a121212"->"122121"
	_value = 0;
	int count = 1; // 包含符号
	while (*pStr >= '0' && *pStr <= '9')
	{
		_value = _value * 10 + (*pStr - '0');
		_strData[count++] = *(pStr++);
	}
	// 重新调整strData大小 防止"45464adsd44564"后面的无用
	_strData.resize(count);

	if (cSymble == '-') 
	{
		_value = 0 - _value;
	}
}

// 判溢出
bool BigData::IsINT64Overflow() const
{
	std::string temp("9223372036854775807"); //0x7fffffffffffffff

	if ('-' == _strData[0])
	{
		temp = "-9223372036854775808"; // 0x1000000000000000
	}

	if (_strData.size() < temp.size())
	{
		return false;
	}
	else if ((_strData.size() == temp.size()) && (_strData <= temp))
	{
		return false;
	}
	else
	{
		return true;
	}
}

BigData BigData::operator+(const BigData& bigData)
{
	// 两个数都没有溢出
	if (!IsINT64Overflow() && !bigData.IsINT64Overflow())
	{
		// 两数异号 无溢出
		if (_strData[0] != bigData._strData[0])
		{
			return BigData(_value + bigData._value);
		}

		// 两数同号 有可能溢出 
		// 不溢出条件(与下面两个条件相反)
		// 条件1 两个正数 7 + 4  7 > 10 - 4 溢出
		// 条件2 两个负数 -7-4   -7 < -10 - (-4) 溢出

		// 同号 无溢出情况
		else if ((_value >= 0 && MAX_INT64 - _value >= bigData._value) || (_value < 0 && MIN_INT64 - _value <= bigData._value))
		{
			return BigData(_value + bigData._value);
		}
	}
    //  至少有一个溢出
	// 结果溢出
	if (_strData[0] == bigData._strData[0])
    {
        return BigData((Add(_strData, bigData._strData)).c_str());
    }
    // 溢出 且 两个数异号
    return BigData((Sub(_strData, bigData._strData)).c_str());
}

std::string BigData::Add(std::string left, std::string right)
{
	int LSize = left.size();
	int RSize = right.size();

	// 保证 左边 长度 比右边长
	if (LSize < RSize)
	{
		std::swap(LSize, RSize);
		std::swap(left, right);
	}

	std::string ret;
	ret.resize(LSize + 1); // 最多最高位进一位
	ret[0] = left[0]; // 保存符号位
	int carryOver = 0; // 保存进位
	for (int i = 1; i < LSize; i++) // i 从1开始
	{
		int src = left[LSize - i] - '0' + carryOver;

		// 右边的长度小 可能越界
		if (i < RSize)
		{
			src += right[RSize - i] - '0';
		}

		// ret 总长为LSize + 1
		ret[LSize + 1 -i] = src % 10 + '0';
		carryOver = src / 10;
	}

	ret[1] = carryOver + '0';

	return ret; // "0004544654564" 多余的0不用考虑 operator+ 的return会重新构造BigData对象 构造函数会去除
}

std::string BigData::Sub(std::string left, std::string right)
{
    //

    return NULL;
}



std::ostream& operator<<(std::ostream& _cout, const BigData& bigData)
{
	if (!bigData.IsINT64Overflow())
	{
		_cout << bigData._value;
	}
	else
	{
		char* ptr = (char*)bigData._strData.c_str();
		if ('+' == ptr[0])
		{
			ptr++;
		}
		_cout<<ptr;
	}

	return _cout;
}

void BigData::INT64ToString() // 将_value转化为字符串
{
	char cSymble = '+';
	if (_value < 0)
	{
		cSymble = '-';
	}
	_strData.append(1, cSymble);
	INT64 pnumber = _value;
	if (pnumber < 0)
	{
		pnumber = 0 - pnumber;
	}

	while (pnumber)
	{
		int num = pnumber % 10;
		_strData.append(1, num + '0');
		pnumber /= 10;
	}

	char* pleft = (char*)_strData.c_str() + 1;
	char* pright = pleft + _strData.size() -2;

	while (pleft < pright) // 字符串逆置
	{
		std::swap(*pleft, *pright);
		pleft++;
		pright--;
	}
}


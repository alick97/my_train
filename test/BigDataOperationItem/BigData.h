#pragma once

#include <string>
#include <cassert>
#define UN_INT 0xcccccccccccccccc // long long 8 Byte
#define MAX_INT64 0x7FFFFFFFFFFFFFFF
#define MIN_INT64 0x8000000000000000
typedef long long INT64;

// 大数运算
// 处理大数运算的方法 字符串模拟

class BigData
{
	friend std::ostream& operator<<(std::ostream& _cout, const BigData& bigData);
public:
	BigData(INT64 value = UN_INT);
  	BigData(const char *pData);

	BigData operator+(const BigData& bigData);
    BigData operator-(const BigData& bigData);
    BigData operator*(const BigData& bigData);
    BigData operator/(const BigData& bigData);
private:
	std::string Add(std::string left, std::string right);
    std::string Sub(std::string left, std::string right);
    std::string Mul(std::string left, std::string right);
    std::string Div(std::string left, std::string right);
	bool IsINT64Overflow() const;
	void INT64ToString();
    bool IsLeftStrBig(char* pLeft, int LSize,const char* pRight, int RSize);
    char SubLoop(char* pLeft, int LSize,const char* pRight, int RSize);
private:
	INT64 _value;
	std::string _strData;
};

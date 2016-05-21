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

	// 调整strData大小  resize自己维护‘\0’ 这里加1是加符号位
	_strData.resize(strlen(pStr) + 1);
	_strData[0] = cSymble;

  


	// "122121a121212"->"122121"
	_value = 0;

      if (1 == _strData.size())
    {
        _strData.append(1, '0'); // "+" "0000000" 
        return;
    }

	int count = 1; // 包含符号
	while (*pStr >= '0' && *pStr <= '9')
	{
		_value = _value * 10 + (*pStr - '0');
		_strData[count++] = *(pStr++);
	}
	// 重新调整strData大小 防止"45464adsd44564"后面的无用
	_strData.resize(count);

    if (1 == count)
    {
        _value = UN_INT; // 防止 “+ashdashj” 返回0
        return;
    }

	if (cSymble == '-') 
	{
		_value = 0 - _value;
	}
}

// 判溢出
bool BigData::IsINT64Overflow() const
{
	std::string temp("+9223372036854775807"); //0x7fffffffffffffff

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
	// 两个数都没有溢出 结果没有溢出
	if (!IsINT64Overflow() && !bigData.IsINT64Overflow())
	{
		// 两数异号 无溢出
		if (_strData[0] != bigData._strData[0])
		{
			return BigData(_value + bigData._value);
		}

		// 两数同号 有可能溢出 
		// 不溢出条件
		// 条件1 两个正数7 、2   10 - 7 >= 2 
		// 条件2 两个负数 -7,-2  -10-(-7) <= -2

		// 同号 无溢出情况
        INT64 temp = MIN_INT64 - _value;
		 if ((_value >= 0 && MAX_INT64 - _value >= bigData._value) || (_value < 0 && /*MIN_INT64 - _value*/temp <= bigData._value))  
            // MIN_INT64 - _value <= bigData._value) 有问题 0 <= -3 当成无符号数 -3是比较大的正数 对于负数最小 + -3  出现0<=-3  本来溢出但这里进入无溢出情况 出错  所以要用temp
            // 编译警告：：\bigdataoperationitem\bigdata.cpp(116): warning C4018: “<=”: 有符号/无符号不匹配
		{
			return BigData(_value + bigData._value);
		}
	}


    //  两数至少有一个数溢出
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
	ret[0] = left[0]; // 保存符号位  左边大 左边符号为最终符号
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

 BigData BigData::operator-(const BigData& bigData)
 {
     // 两个都没有溢出 且结果没有溢出的情况
     if (!IsINT64Overflow() && !bigData.IsINT64Overflow())
     {
         // 两个同号
         if (_strData[0] == bigData._strData[0])
         {
             return BigData(_value - bigData._value);
         }
         else // 两个异号
         {
             // + 减去-    10 + (-2) = 8 >= 7
             if ((_value >= 0 && MAX_INT64 + bigData._value >= _value)
                 // -减去+  -10 + （2） = -8 <= -7
                     || (_value < 0 && MIN_INT64 + bigData._value <= _value))
             {
                 return BigData(_value - bigData._value);
             }
         }
     }

     // 
     // 结果溢出
     // 异号
     if (_strData[0] != bigData._strData[0])
     {
         BigData ret =  BigData(Add(_strData, bigData._strData).c_str());
         // 因为加法的符号是以长的数的符号为准 所以对于被减数是短的的情况要修正
         ret._strData[0] = _strData[0];
         return ret;
     }

     // 同号
     return BigData(Sub(_strData, bigData._strData).c_str());

 }


std::string BigData::Sub(std::string left, std::string right)
{
    //前提  假设 两数 同号
    int iLSize = left.size();
    int iRSize = right.size();
    char cSymble = left[0]; // 先用左边初始化 （在operator+中 两个异号用了Sub 与Sub假设两个同号不符  但结果是正确的）

    // 保证左边长度 大于等于 右边
    if (iLSize < iRSize || (iLSize == iRSize && left < right))
    {
        std::swap(left, right);
        std::swap(iLSize, iRSize);

        //  2 - 3 = -1  2+  -1  + ->-
        //  -2 - (-3) = 1   2- +1   -->+
        if ('+' == cSymble)
        {
            cSymble = '-';
        }
        else
        {
            cSymble = '+';
        }

    }
        // 保存结果
        std::string strRet;
        strRet.resize(left.size());
        strRet[0] = cSymble;

        for (int Idx = 1; Idx < iLSize; ++Idx)
        {
           int cRet = left[iLSize - Idx] - '0';

           // 防止 超出 right的范围
           if (Idx < iRSize)
           {
               cRet -= (right[iRSize - Idx] - '0');
           }

           if (cRet < 0)
           {
               // 向高位借位
               left[iLSize - Idx - 1] -= 1;
               cRet += 10;
           }

           strRet[iLSize - Idx] = cRet + '0';
        }

        return strRet;
    }

BigData  BigData::operator*(const BigData& bigData)
{
    if (_strData[1] == '0' || bigData._strData[1] == '0')
    {
        return BigData(INT64(0));
    }
    // 两个都无溢出 且结果不溢出 的情况
    if (!IsINT64Overflow() && !bigData.IsINT64Overflow())
    {
        // 同号
        if (_strData[0] == bigData._strData[0])
        {
            // 10 / -2 = -5 <= -3
            // 10 / 2 = 5 >= 3
            if (_value > 0 && MAX_INT64 / _value >= bigData._value 
                || (_value < 0 && MAX_INT64/_value <= bigData._value ))
            {
                return BigData(_value * bigData._value);
            }

        }
        else // 异号
        {
            // -10 / 2 = -5 <= -3
            // -10 / -2 = 5 >= 3
             if (_value > 0 && MIN_INT64 / _value <= bigData._value 
                || (_value < 0 && MIN_INT64/_value >= bigData._value ))
            {
                return BigData(_value * bigData._value);
            }
        }
    }

    // 结果溢出

    return BigData(Mul(_strData, bigData._strData).c_str());
}

std::string BigData::Mul(std::string left, std::string right)
{ 
    // 确定符号位
    char cSymbol = '+';
    if (left[0] != right[0])
    {
        cSymbol = '-';
    }

    int iLSize = left.size();
    int iRSize = right.size();

    // 保证左边长度 小于 右边 (使得 下面 外循环比内循环小一点)
    if (iLSize > iRSize)
    {
        std::swap(left, right);
        std::swap(iLSize, iRSize);
    }

    // 开辟 返回空间   为两数长度和加上符号位 
    // 因为100*1000<= 100000 所以99*999 < 100000 5位
    std::string sRet;
   // sRet.resize(iLSize + iRSize - 1);// 注意 这里符号位算了两遍 所以减去1
     // 用另外一个 防止【注2】 每次多加‘0’ 
    sRet.assign(iLSize + iRSize - 1, '0');

    sRet[0] = cSymbol;
   
    int iDataLen = sRet.size();
   


    int ioffset = 0; // 每次向左边移位
    // 先取左边一个 和 右边每一位相乘
    for (int iLIdx = 1; iLIdx < iLSize; iLIdx++)
    {
        char cLeft = left[iLSize - iLIdx] - '0';// 虽然char 但内容意思是数字 不是字符 节省空间
        char cStep = 0;// 进位

        if (cLeft == 0)
        {
            ioffset++;
            continue;
        }
        // 99*999
        for (int iRIdx = 1; iRIdx < iRSize; ++iRIdx)
        {
            char cRet = cLeft * (right[iRSize - iRIdx] - '0') + cStep;
           //【注2】//错误 每次多加‘0’ sRet[iDataLen - iRIdx - ioffset] += cRet%10 + '0';
            // 解决方法 看上面【注2】 开辟空间是用string的assign初始化成‘0’
            cRet += sRet[iDataLen - iRIdx - ioffset] - '0';
            sRet[iDataLen - iRIdx - ioffset] = cRet%10 + '0';
            cStep = cRet/10;
        }
        sRet[iDataLen - iRSize - ioffset] += cStep;
        ioffset++;
    }

    return sRet;
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
    INT64 pnumber = _value;
	if (_value < 0)
	{
		cSymble = '-';
        pnumber = 0 - pnumber; // 注意  -9223372036854775808 负的最小 无法转到 正的  如 两位数 最高位符号位 0 - 100 = 100 下面运算要 注意判断负数  见下面【注意1】
	}
	_strData.append(1, cSymble);

	while (pnumber)
	{
		int num = pnumber % 10;

        // 【注意1】 
        if (num < 0)
        {
            num = 0 - num;
        }

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

    if (1 == _strData.size())
    {
        _strData.append(1, '0');
    }

}

bool BigData::IsLeftStrBig(char* pLeft, int LSize,const char* pRight, int RSize)
{
    if (LSize > RSize || LSize == RSize && strncmp(pLeft, pRight, RSize) >= 0)
    {
        return true;
    }

    return false;
}

char BigData::SubLoop(char* pLeft, int LSize,const char* pRight, int RSize)
{
    assert(pLeft != NULL && pRight != NULL);
    char cRet = '0'; // 记录减 的次数 加'0'
    while(true)
    {
        if (!IsLeftStrBig(pLeft, LSize, pRight, RSize))
        {
            break;
        }

        for (int iIdx = 1; iIdx < RSize; ++iIdx)
        {
            pLeft[LSize - iIdx] -= pRight[RSize - iIdx]; // ‘0’抵消了
            if ( pLeft[LSize - iIdx] < 0)
            {
                pLeft[LSize - iIdx - 1] -= 1;// 高位借位
                pLeft[LSize - iIdx] += 10;
            }

            // 还原成字符
            pLeft[LSize - iIdx] += '0'; 
        }

        // 减完后 前面 有 ‘0’ 去除
        // 防止无休止去除 如“3300000” - “33” 后面 “0000000000000” 无休止跳 商不添加‘0’加条件
        // 090  把0跳过去
     /*   while (*pLeft == '0' && LSize > 0)
        {
            pLeft++;
            LSize--;
        }*/

        cRet++; 
    }

    return cRet;
}


BigData BigData::operator/(const BigData& bigData)
{
    //2222222222222/33

    // 除数不能为0
    if ('0' == _strData[0])
    {
        assert(false);
    }
    // 两个 都没有溢出
    if (!IsINT64Overflow() && !bigData.IsINT64Overflow())
    {
        return _value / bigData._value;
    }

    // 左边 小于 右边
    if (_strData.size() < bigData._strData.size() || /*_strData.size() == bigData._strData.size() &&*/ strcmp(_strData.c_str() + 1, bigData._strData.c_str() + 1) < 0 )
    {
        return BigData(INT64(0));
    }

    // 右边 +-1 
    if (!bigData.IsINT64Overflow() && (1 == bigData._value || -1 == bigData._value))
    {
        if (1 == bigData._value)
        {
            return *this;
        }

         std::string ret = _strData;
        // -1
        if ('+' == ret[0])
        {
            ret[0] = '-';
        }
        else
        {
            ret[0] = '+';
        }

        return BigData(ret.c_str());
    }

    // 左边 等于 右边
    if (strcmp(_strData.c_str() + 1, bigData._strData.c_str() + 1) == 0)
    {
        std::string ret = "+1";
        if (_strData[0] != bigData._strData[0])
        {
            ret[0] = '-';
        }

        return BigData(ret.c_str());
    }
    // 其他
    return BigData(Div(_strData, bigData._strData).c_str());
}

std::string BigData::Div(std::string left, std::string right)
{
    //  前提 左边 大于 右边

    std::string sRet;
    sRet.append(1, '+');
    if (left[0] != right[0])
    {
        sRet[0] = '-';
    }
    //越过符号位
    char* pLeft = (char*)(left.c_str() + 1);
    char* pRight = (char*)(right.c_str() + 1);
    int LSize = left.size() - 1;
    int RSize = right.size() - 1;
    int DataLen = RSize; // 偏移 从pLeft向后总共可以看到多少位 刚开始可以为1 也可初始化为右边数值长度
    
  

    for (int iIdx = 0; iIdx < LSize;)
    {
          // 处理‘0’
        // 3300000000000/33  00  0000000000000
        if ('0' == *pLeft)
        {
            sRet.append(1, '0');
            pLeft++;
            iIdx++;
            continue;
        }


        if (!IsLeftStrBig(pLeft, DataLen, pRight,RSize))
        {
            // 左边 小于 右边 商补0
            sRet.append(1, '0');
            DataLen++; // 左边向后延长一位
            if (DataLen + iIdx > LSize) // >= 少算一位 防止越界超出左边的总长度
            {
                break;
            }
        }
        else // 左边大于右边
        {
            sRet.append(1, SubLoop(pLeft, DataLen, pRight, RSize));
            // 更新pLeft 因为上面SubLoop的pLeft用的是值传递 所以要在外面更新
            while (*pLeft == '0' && DataLen > 0 )
            {
                pLeft++;
                iIdx++;
              
                DataLen--; // 33333/33 left 33 变成00 <33 但Datalen没减的话 -> left 0033 》= 33  -> 商11 原本要商 101   少算中间的0    DataLen--防止少算0
                // 也防止 “330000000000”
            }
            // 22222222222222/33
            // "0242222222222222"
            //  "242222222222222"
            DataLen++; // 防止下载一次用24 和 33 比较 24 < 33 商多算了一个0
            if (DataLen + iIdx > LSize) // >= 少算一位
            {
                break;
            }
        }
    }


    return sRet;
}






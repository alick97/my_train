#define _CRT_SECURE_NO_WARNINGS 1
#include "BigData.h"
#include <iostream>
using namespace std;
void test_BigData()
{
    // "1235464678"
	// "+123456789"
    // "+"
    // "       "
    // "000012312313"
	// "-12131313123"
	// "123123asdad1231213"
	// "a4546546"
	// "000000000"
    BigData b1(23456);
    BigData b2("12345678");
    BigData b3("+1234567");

    BigData b4("+123456aaa");
    BigData b5("+"); // 0

    BigData b6("    ");
    BigData b7("-12345678");

    BigData b8("-000001245www");

    BigData b9 = "";
    BigData b10 = "0000000000";
    BigData b11("+asasa"); // 0  

    BigData b12(9223372036854775807);
    BigData b13(0 - 9223372036854775808);
    BigData b14(INT64(0));

}

void FunTest_ADD()
{
    BigData left(1234);
    BigData right(4321);
    BigData ret = left + right;
    cout<<ret<<endl;
    //9223372036854775807
    
    BigData left1(9223372036854775807);
    BigData right1(2);
    ret = left1 + right1;
    cout<<ret<<endl;

    // 都无溢出 相加结果溢出
    BigData left2(0-9223372036854775808);
    cout<<left2<<endl;
    BigData right2(-3);
   ret = left2 + right2;
    cout<<ret<<endl;
}

void FunTest_SUB()
{
 /*   BigData left2(1234);
    BigData right2(34);
    cout<<left2-right2<<endl;*/

    BigData left2("11");
    BigData right2("-78789997777777777777777777777777777");
    cout<<left2-right2<<endl;
}

void FunTest_MUL()
{

    // BigData left2("999");
    //BigData right2("99999999999999999999999999999999");
    //cout<<left2*right2<<endl;

    /* BigData left2("1111111111111111111111111111111111");
    BigData right2("-99");
    cout<<left2*right2<<endl;*/

     BigData left2("1000000000000000000000001");
    BigData right2("-22222222222222222222222222222222222222222");
    cout<<left2*right2<<endl;
}





int main()
{
	//test_BigData();
  //FunTest_ADD();
  FunTest_SUB();

   // FunTest2();
	return 0;
}

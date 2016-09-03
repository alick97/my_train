#include <stdio.h>

// 模拟 pow

bool g_invalidInput = false;


bool equal(double num1, double num2)
{
    if ((num1 - num2 > -0.000001) && (num1 -  num2) < 0.000001)
	{
		return true;
	}
	else
	{
	    return false;
	}
}

/**************************************
double PowerWithUnsingnedExponent(double base, unsigned int exponent)
{
	double result = 1.0;
	for (int i = 1; i <= exponent; ++i)
		result *= base;

	return result;
}
*******************************************/


/******
 * 更高效
 * ************/

double PowerWithUnsingnedExponent(double base, unsigned int exponent)
{
	if (exponent == 0)
	{
	 return 1;
	}

	if (exponent == 1)
	{
		return base;
	}

	//    a^n   =   a^(n/2) * a^(n/2)     n为偶数
	//    a^n   =   a^((n-1)/2) * a^((n - 1)/2) * a  n为奇数 
    double result = PowerWithUnsingnedExponent(base, exponent >> 1);
    result *= result;

	if (exponent & 0x1 == 1)
	{
		result *= base;
	}

	return result;
}




double Power(double base, int exponent)
{
	g_invalidInput = false;
//  除数为0
	if (equal(base, 0.0) && exponent < 0)
	{
		g_invalidInput = true;
		return 0.0;
	}

	unsigned int absExponent = (unsigned int)(exponent);
	if (exponent < 0)
	{
		absExponent = (unsigned int )(0 - exponent);
	}

	double result = PowerWithUnsingnedExponent(base, absExponent);

	if (exponent < 0)
	{
		result = 1.0 / result;
	}

	return result;
}

int main()
{

	double res = Power(-2, 5);
	printf("%f\n",res);
	 res = Power(2, -1);
	printf("%f\n",res);
	return 0;
}


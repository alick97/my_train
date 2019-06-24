#include <iostream>
#include <assert.h>

class Solution {
public:
    int divide(int dividend, int divisor) {
        if (dividend == INT32_MIN && divisor == -1) {
            return INT32_MAX;
        }
        long dividend_abs = labs(dividend);
        long divisor_abs = labs(divisor);
        long result = 0;
        int sign = dividend > 0 ^ divisor > 0 ? -1 : 1;
        while (dividend_abs >= divisor_abs) {
            long temp = divisor_abs, m = 1;
            while (temp << 1 <= dividend_abs) {
                temp <<= 1;
                m <<= 1;
            }
            result += m;
            dividend_abs -= temp;
        }
        return sign * result;
    }
};

void test_divide() {
    Solution s;
    assert(s.divide(10, 3) == 3);

    assert(s.divide(7, -3) == -2);

    assert(s.divide(INT32_MIN, 1) == INT32_MIN);

    assert(s.divide(1, 1) == 1);
}

int main() {
    test_divide();
    return 0;
}

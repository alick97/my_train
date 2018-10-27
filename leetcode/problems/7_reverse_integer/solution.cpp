#include<iostream>
#include<assert.h>
using namespace std;

class Solution {
public:
    int reverse(int x) {
        int rev = 0;
        while (0 != x) {
            int residual = x % 10;
            x /= 10;
            // check is overflower in max int type
            if (rev > INT32_MAX/10 || (rev == INT32_MAX && residual > 7)) return 0;
            if (rev < INT32_MIN/10 || (rev == INT32_MIN && residual < -8)) return 0;
            rev = rev * 10 + residual;
        }
        return rev;
    }
};

void test() {
 Solution s = Solution();
 assert(s.reverse(123)==321);
 assert(s.reverse(-123)==-321);
 assert(s.reverse(120)==21);
}

int main() {
    test();
    return 0;
}
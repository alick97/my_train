#include <iostream>
#include <cmath>
#include <climits>
#include <assert.h>
using namespace std;

class Solution {
public:
    int myAtoi(string str);
};

int Solution::myAtoi(string str) {
    long long int result = 0;
    int digit = 0;
    int symble = 1;
    int start = 0;
    bool is_start = true;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            is_start = false;
            digit += 1;
        } 
        else if  ( '-' == str[i] && is_start) {
            symble = -1;
            ++start;
            is_start = false;
        }
        else if  ( '+' == str[i] && is_start) {
            symble = 1;
            ++start;
            is_start = false;
        }
        else if (' ' == str[i] && is_start) {
            ++start;
        }
        else {
            break;
        }
    }

    for (int j=digit; j>0; j--) {
        result += (str[start + j - 1] - '0') * pow(10, digit - j) * symble;
        if ((result >= INT_MAX || result < 0) && symble == 1) {
            result = INT_MAX;
            break;
        }
        else if ((result <= INT_MIN || result > 0) && symble == -1) {
            result = INT_MIN;
            break;
        }
    }
    return result;
}

void test(){
    Solution s = Solution();
    // "42" -> 42
    assert(42 == s.myAtoi("42"));
    // "    -42" -> -42
    assert(-42 == s.myAtoi("      -42"));
    // "4193 with words" -> 4193
    assert(s.myAtoi("4193 with words") == 4193);
    // "words and 987" -> 0
    assert(s.myAtoi("words and 987") == 0);
    // "-91283472332" -> -2147483648
    assert(s.myAtoi("-91283472332") == -2147483648);
    // "20000000000000000000" -> 2147483647
    assert(s.myAtoi("20000000000000000000") == 2147483647);
}

int main() {
    test();
    return 0;
}
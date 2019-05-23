#include <iostream>
#include <assert.h>
using namespace std;

/*
    Symbol       Value
    I             1
    V             5      +
    X             10
    L             50     +
    C             100
    D             500    +
    M             1000   +
*/

class Solution {
public:
    int romanToInt(string s) {
        int result = 0; // 1-3999
        int i = 0;
        int current_total = 0;
        while (i < s.length()) {
            if ('M' == s[i]) {
                result += 1000;
            } else if ('D' == s[i]) {
                result += 500;
            } else if ('L' == s[i]) {
                result += 50;
            } else if ('V' == s[i]) {
                result += 5;
            } else if ('C' == s[i]) {
                if (i < s.length() - 1) {
                    if ('D' == s[i + 1] || 'M' == s[i + 1]) {
                        result -= current_total + 100;
                        current_total = 0;
                    } else if (s[i] != s[i + 1]) {
                        result += current_total + 100;
                        current_total = 0;
                    } else {
                        current_total += 100;
                    }
                } else {
                    result += current_total + 100;
                }
            } else if ('X' == s[i]) {
                if (i < s.length() - 1) {
                    if ('L' == s[i + 1] || 'C' == s[i + 1]) {
                        result -= current_total + 10;
                        current_total = 0;
                    } else if (s[i] != s[i + 1]) {
                        result += current_total + 10;
                        current_total = 0;
                    } else {
                        current_total += 10;
                    }
                } else {
                    result += current_total + 10;
                }
            } else if ('I' == s[i]) {
                if (i < s.length() - 1) {
                    if ('V' == s[i + 1] || 'X' == s[i + 1]) {
                        result -= current_total + 1;
                        current_total = 0;
                    } else if (s[i] != s[i + 1]) {
                        result += current_total + 1;
                        current_total = 0;
                    } else {
                        current_total += 1;
                    }
                } else {
                    result += current_total + 1;
                }

            }
            ++i;
        }
        return result;
    }
};


int main() {
    /*
    #### Example 1:
    ```
    Input: "III"
    Output: 3
    ```
    #### Example 2:
    ```
    Input: "IV"
    Output: 4
    Example 3:

    Input: "IX"
    Output: 9
    ```
    #### Example 4:
    ```
    Input: "LVIII"
    Output: 58
    Explanation: L = 50, V= 5, III = 3.
    ```
    #### Example 5:
    ```
    Input: "MCMXCIV"
    Output: 1994
    Explanation: M = 1000, CM = 
    */
    Solution s = Solution();
    assert(3 == s.romanToInt("III"));
    assert(4 == s.romanToInt("IV"));
    assert(9 == s.romanToInt("IX"));
    assert(58 == s.romanToInt("LVIII"));
    assert(1994 == s.romanToInt("MCMXCIV"));

    return 0;
}
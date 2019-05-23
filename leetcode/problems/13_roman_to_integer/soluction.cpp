#include <iostream>
#include <assert.h>
#include <map>
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
        int pre = 0;
        map<char, int> symbol_map;
        symbol_map['I'] = 1;
        symbol_map['V'] = 5;
        symbol_map['X'] = 10;
        symbol_map['L'] = 50;
        symbol_map['C'] = 100;
        symbol_map['D'] = 500;
        symbol_map['M'] = 1000;

        for (int i = s.length() - 1; i >= 0; --i) {
            if (symbol_map[s[i]] < pre) {
                result -= symbol_map[s[i]];
            } else {
                result += symbol_map[s[i]];
            }
            pre = symbol_map[s[i]];
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
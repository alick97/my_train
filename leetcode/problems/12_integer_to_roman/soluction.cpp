#include <iostream>
#include <assert.h>
using namespace std;
/*
    Symbol       Value
    I             1
    V             5
    X             10
    L             50
    C             100
    D             500
    M             1000
*/
class Solution {
public:
    string intToRoman(int num) {
        string s;
        int index_num = 0;
        index_num = num / 1000;
        if (index_num > 0) {
            s.append(string(index_num, 'M'));
        }
        num %= 1000;

        char symbol_arr[] = "MDCLXVI";
        int i = 0;
        int digit = 100;
        while (num > 0) {
            index_num = num / digit;
            if (index_num > 0) {
                if (index_num == 9) {
                    s.append(1, symbol_arr[i+2]);
                    s.append(1, symbol_arr[i]);
                } else if (index_num == 4) {
                    s.append(1, symbol_arr[i+2]);
                    s.append(1, symbol_arr[i+1]);
                } else if (index_num < 4) {
                    s.append(index_num, symbol_arr[i+2]);
                } else if (index_num == 5) {
                    s.append(1, symbol_arr[i+1]);
                } else {
                    s.append(1, symbol_arr[i+1]);
                    s.append(index_num - 5, symbol_arr[i+2]);
                }
            }
            num %= digit;
            digit /= 10;
            i += 2;
        }
        return s;
    }
};

void test() {
    Solution s = Solution();

    assert("III" == s.intToRoman(3));
    assert("IV" == s.intToRoman(4));
    assert("LVIII" == s.intToRoman(58));
    assert("MCMXCIV" == s.intToRoman(1994));
}

int main() {
    test();
    return 0;
}
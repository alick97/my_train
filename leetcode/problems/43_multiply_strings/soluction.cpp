#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

class Solution {
public:
    string multiply(string num1, string num2) {
       string sum(num1.size() + num2.size(), '0');

       for (int i = num1.size() - 1; i >= 0; --i) {
           int carry = 0;
           int multiplier = num1[i] - '0';
           for (int j = num2.size() - 1; j >= 0; --j) {
               int tmp = (sum[i + j + 1] - '0') + multiplier * (num2[j] - '0') + carry;
               sum[i + j + 1] = tmp % 10 + '0';
               carry = tmp / 10;
           }
           sum[i] += carry;
       } 

       size_t startpos = sum.find_first_not_of("0");
       if (string::npos != startpos) {
           return sum.substr(startpos);
       } else {
          return "0"; 
       }
    }
};

void test() {
    Solution s;
    string result = s.multiply("2", "3");
    assert("6" == result);
    
    result = s.multiply("123", "456");
    assert("56088" == result);

    result = s.multiply("31434121424", "000");
    assert("0" == result);
}

int main() {
    test();
    return 0;
}

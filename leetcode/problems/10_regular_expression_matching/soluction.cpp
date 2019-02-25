#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

/*
s = "aa" p = "a" Output: false
s = "aa" p = "a*" Output: true
s = "ab" p = ".*" Output: true
s = "aab" p = "c*a*b" Output: true
s = "mississippi" p = "mis*is*p*." Output: false
*/

class Solution {
public:
    bool isMatch(string s, string p) {
        if (p.empty()) {
            return s.empty();
        }
        bool first_match = (!s.empty() &&
            (p[0] == s[0] || p[0] == '.'));
        
        if (p.length() >= 2 && p[1] == '*') {
            return (isMatch(s, p.substr(2)) ||
                (first_match && isMatch(s.substr(1), p)));
        } else {
            return (first_match && isMatch(s.substr(1), p.substr(1)));
        }
    }
};

void test() {
   Solution s = Solution();
   assert(s.isMatch("aa", "a") == false);
   assert(s.isMatch("aa", "a*") == true);
   assert(s.isMatch("ab", ".*") == true);
   assert(s.isMatch("aab", "c*a*b") == true);
}

int main() {
    test();
    return 0;
}
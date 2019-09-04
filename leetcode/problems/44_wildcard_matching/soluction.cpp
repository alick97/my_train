#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
       const char *star = NULL;
       const char *s_ptr = s.c_str();
       const char *p_ptr = p.c_str();
       const char *ss = s_ptr;

        while (*s_ptr) {
            if (*p_ptr == '?' || *p_ptr == *s_ptr) {
                s_ptr++;
                p_ptr++;
                continue;
            }
 
            if (*p_ptr == '*') {
                star = p_ptr++;
                ss = s_ptr;
                continue;
            }
 
            if (star != NULL) {
                p_ptr = star + 1;
                s_ptr = ++ss;
                continue;
            }
 
            return false;
        }
 
        // check for remaining characters in pattern
        while (*p_ptr == '*') {
            ++p_ptr;
        }
 
        return !*p_ptr;
    }
};


void test() {
    Solution s;
    bool result = false;
// #### Example 1:
// ```
// Input:
// s = "aa"
// p = "a"
// Output: false
// Explanation: "a" does not match the entire string "aa".
// ```
    result = s.isMatch("aa", "a");
    assert(false == result);
// #### Example 2:
// 
// ```
// Input:
// s = "aa"
// p = "*"
// Output: true
// Explanation: '*' matches any sequence.
// ```
    result = s.isMatch("aa", "*");
    assert(true == result);
// #### Example 3:
// 
// ```
// Input:
// s = "cb"
// p = "?a"
// Output: false
// Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.
// ```
    result = s.isMatch("cb", "?a");
    assert(false == result);
// #### Example 4:
// 
// ```
// Input:
// s = "adceb"
// p = "*a*b"
// Output: true
// Explanation: The first '*' matches the empty sequence, while the second '*' matches the substring "dce".
// ```
    result = s.isMatch("adceb", "*a*b");
    assert(true == result);

// #### Example 5:
// 
// ```
// Input:
// s = "acdcb"
// p = "a*c?b"
// Output: false
    result = s.isMatch("acdcb", "a*c?b");
    assert(false == result);
}

int main() {
    test();
    return 0;
}

#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        vector<char> v;
        for (int i=0; i < s.size(); i++) {
            if (v.size() > 0) {
                char t = v.at(v.size() - 1);
                if (s[i] == '{' || s[i] == '[' || s[i] == '(') {
                    v.push_back(s[i]);
                } else if (s[i] == ']' && t == '['
                || s[i] == '}' && t == '{'
                || s[i] == ')' && t == '(') {
                    v.pop_back();
                } else {
                    break;
                }
            } else {
                v.push_back(s[i]);
            }
        }

        if (v.size() > 0) {
            return false;
        } else {
            return true;
        }
    }
};

void test() {
    Solution s;
// #### Example 1:
// ```
// Input: "()"
// Output: true
// ```
    assert(s.isValid("()") == true);

// #### Example 2:
// ```
// Input: "()[]{}"
// Output: true
// ```
    assert(s.isValid("()[]{}") == true);

// #### Example 3:
// ```
// Input: "(]"
// Output: false
// ```
    assert(s.isValid("(]") == false);

// #### Example 4:
// ```
// Input: "([)]"
// Output: false
// ```
    assert(s.isValid("([)]") == false);

// #### Example 5:
// ```
// Input: "{[]}"
// Output: true
// ```
    assert(s.isValid("{[]}") == true);
}

int main() {
    test();
    return 0;
}
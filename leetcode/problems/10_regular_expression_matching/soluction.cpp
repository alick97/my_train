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
    // bool isMatch(string s, string p) {
    //     if (p.empty()) {
    //         return s.empty();
    //     }
    //     bool first_match = (!s.empty() &&
    //         (p[0] == s[0] || p[0] == '.'));
        
    //     if (p.length() >= 2 && p[1] == '*') {
    //         return (isMatch(s, p.substr(2)) ||
    //             (first_match && isMatch(s.substr(1), p)));
    //     } else {
    //         return (first_match && isMatch(s.substr(1), p.substr(1)));
    //     }
    // }

    enum Result {
        R_TRUE, R_FALSE, R_NULL
    };

    bool isMatch(string s, string p) {
        Result **memo = new Result*[s.length() + 1];
        for (int i = 0; i <= s.length(); i++) {
            memo[i] = new Result[p.length() + 1];
            for (int j = 0; j <= p.length(); j++) {
                memo[i][j] = R_NULL;
            }
        }

        bool result = dp(0, 0, s, p, memo);

        // release
        for (int i = 0; i <= s.length(); i++) {
            delete[] memo[i];
        }
        delete[] memo;

        return result;
    }

    static bool dp(int i, int j, const string& text, const string& pattern, Result **memo) {
        if (memo[i][j] != R_NULL) {
            cout << "match: i=" << i << ", j=" << j << endl;
            return memo[i][j] == R_TRUE;
        }
        bool ans;
        if (j == pattern.length()) {
            ans = (i == text.length());
        } else {
            bool first_match = (i < text.length() &&
            (pattern[j] == text[i] || pattern[j] == '.'));

            if (j + 1 < pattern.length() && pattern[j+1] == '*') {
                ans = (dp(i, j+2, text, pattern, memo) ||
                    (first_match && dp(i+1, j, text, pattern, memo)));
            } else {
                ans = first_match && dp(i+1, j+1, text, pattern, memo);
            }
        }
        memo[i][j] = ans ? R_TRUE : R_FALSE;
        return ans;
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
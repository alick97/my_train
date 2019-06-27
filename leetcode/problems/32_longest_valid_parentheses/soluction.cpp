#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        /* ) ( ( ) ) ) ) ( ( ) ) ( ) ) 
        = >0 0 0 2 4 0 0 0 0 2 4 0 6 0
        */
        int size = s.size();
        vector<int> dp(size);
        int max_count = 0;
        for (int i = 1; i < size; ++i) {
            if (s[i] == ')') {
                if (s[i-1] == '(') {
                    dp[i] = (i - 2 >= 0 ? dp[i-2] : 0) + 2;
                }
                else if (i - dp[i-1] > 0 && s[i - dp[i-1] - 1] == '(') {
                    dp[i] = dp[i-1] + 2 + (i - dp[i-1] - 2 >= 0 ? dp[i-dp[i-1]-2] : 0);
                }

                max_count = max(max_count, dp[i]);
            }
        }

        return max_count;
    }
};

int main() {
    // for test
    Solution s;
    assert(2 == s.longestValidParentheses("(()"));
    assert(4==s.longestValidParentheses(")()())"));
    return 0;
}
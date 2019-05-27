#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.size() == 0) {
            return "";
        }

        for (int i = 0; i < strs[0].size(); ++i) {
            char c = strs[0][i];    
            for (int j = 1; j < strs.size(); ++j) {
                if (i == strs[j].size() || c != strs[j][i]) {
                    return strs[j].substr(0, i);
                }
            }
        }
        return strs[0];
    }
};

void test() {
    Solution s = Solution();
    vector<string> v;
    v.push_back("flower");
    v.push_back("flow");
    v.push_back("flight");
    assert("fl" == s.longestCommonPrefix(v));

    v.clear();
    v.push_back("dog");
    v.push_back("racecar");
    v.push_back("car");
    assert("" == s.longestCommonPrefix(v));
}

int main() {
    test();
    return 0;
}
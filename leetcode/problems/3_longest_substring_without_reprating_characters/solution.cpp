#include <iostream>
#include <string.h>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s);
};

int Solution::lengthOfLongestSubstring(string s) {
    int max_result = 0;
    bool ch_is_exist_map[256];
    for (int i = 0; i < 256; i++) {
        ch_is_exist_map[i] = false;
    }

    for(int start_index = 0; start_index < s.length(); ++start_index) {
        int cur_count = 1;
        for (int i = 0; i < 256; i++) {
            ch_is_exist_map[i] = false;
        }
        ch_is_exist_map[(unsigned int)s[start_index]] = true;
        for(int end_index=start_index+1; end_index < s.length(); ++end_index) {
            if (ch_is_exist_map[(unsigned int)s[end_index]] != true) {
                cur_count += 1;
                ch_is_exist_map[(unsigned int)s[end_index]] = true; 
            } else {
                break;
            }
        }
        if (cur_count > max_result) {
            max_result = cur_count;
        }
    }
    return max_result;
}

int main() {
    Solution s;
    // abcabcbb // 3
    cout << s.lengthOfLongestSubstring("abcabcbb") << endl;
    // bbbbb // 1
    cout << s.lengthOfLongestSubstring("bbbbb") << endl;
    // pwwkew // 3
    cout << s.lengthOfLongestSubstring("pwwkew") << endl;

    return 0;
}
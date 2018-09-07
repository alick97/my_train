#include <iostream>
#include <string.h>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s);
    int lengrhOfLongestSubstring2(string s);
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

int Solution::lengrhOfLongestSubstring2(string s) {
    // method O(n)
    int start = -1;
    int max_length = 0;
    int ch_index[256];
    for(int i = 0; i < 256; i++) {
        ch_index[i] = -1;
    }

    for(int index=0; index < s.length(); ++index) {
        if (ch_index[static_cast<unsigned int>(s[index])] > start) {
            start = ch_index[static_cast<unsigned int>(s[index])];
        }
        ch_index[static_cast<unsigned int>(s[index])] = index;
        max_length = max(max_length, index - start);
    }
    return max_length;
}

int main() {
    Solution s;
    // abcabcbb // 3
    cout << s.lengthOfLongestSubstring("abcabcbb") << endl;
    // bbbbb // 1
    cout << s.lengthOfLongestSubstring("bbbbb") << endl;
    // pwwkew // 3
    cout << s.lengthOfLongestSubstring("pwwkew") << endl;

    // abcabcbb // 3
    cout << s.lengrhOfLongestSubstring2("abcabcbb") << endl;
    // bbbbb // 1
    cout << s.lengrhOfLongestSubstring2("bbbbb") << endl;
    // pwwkew // 3
    cout << s.lengrhOfLongestSubstring2("pwwkew") << endl;
    return 0;
}
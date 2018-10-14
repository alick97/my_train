#include <iostream>
using namespace std;



class Solution {
public:
    string longestPalindrome(string s) {
        int start = 0;
        int end = 0;
        if (0 == s.length()) {
            return "";
        } else {
            for (int center=0; center < s.length(); ++center) {
                int odd_len = findPalindromeLen(center, center, s);
                int even_len = findPalindromeLen(center, center+1, s);
                if (odd_len > (end - start + 1)) {
                    start = center - (odd_len / 2);
                    end = center + (odd_len / 2);
                }

                if (even_len > (end - start + 1)) {
                    start = center + 1 - (even_len / 2);
                    end = center + (even_len / 2);
                }
            }
        }

        return s.substr(start, end-start+1);
    };
private:
    int findPalindromeLen(int l, int r, const string& s) {
        int len = 0;
        while(l >= 0 && r < s.length()) {
            if (s[l] == s[r]) {
                len = r - l + 1;
                l -= 1;
                r += 1;
            } else {
                break;
            }
        }
        return len;
    };
};

void test_longest_palindrome() {
    Solution s = Solution();
    // Input: "babad" Output: "bab"
    string s1 = "babad";
    string p1 = s.longestPalindrome(s1);
    cout << "result: " << p1 << "  ";
    if (p1.compare("bab") != 0) {
        cout << "failed: s1's palindrome not equal 'bab'" << endl;
    } else {
        cout << "ok" << endl;
    }
    // Input: "cbbd" Output: "bb"
    string s2 = "cbbd";
    string p2 = s.longestPalindrome(s2);
    cout << "result: " << p2 << "  ";
    if (p2.compare("bb") != 0) {
        cout << "failed: s2's palindrome not equal 'bb'" << endl;
    } else {
        cout << "ok" << endl;
    }
}

int main() {
    test_longest_palindrome();
    return 0;
}
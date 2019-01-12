#include <iostream>
#include <string>
#include <assert.h>

class Solution {
public:
    bool isPalindrome(int x) {
        if(x < 0) {
            return false;
        }

        std::string s = "";
        while (x > 0) {
            s += char('0' + (x % 10));
            x /= 10;
        }

        for(int i=0; i < s.size() / 2; i++) {
             if (s[i] == s[s.size() - 1 -i]) {
                 continue;
             } else {
                 return false;
             }
        }

        return true;
    }
};

void test() {
    Solution s = Solution();
    assert(s.isPalindrome(121) == true);
    assert(s.isPalindrome(-121) == false);
    assert(s.isPalindrome(1243) == false);
}

int main(int argc, char *argv[]) {
    test();
    return 0;
}
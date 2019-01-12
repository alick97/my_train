#include <iostream>
#include <string>
#include <assert.h>

class Solution {
public:
    bool isPalindrome(int x) {
        if(x < 0 || (x % 10 == 0 && x != 0)) {
            return false;
        }

        int reverted_number = 0;
        while(x > reverted_number) {
            reverted_number = reverted_number * 10 + x % 10;
            x /= 10;
        }

        return reverted_number == x || reverted_number/10 == x;
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
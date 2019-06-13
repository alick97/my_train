#include <string>
#include <iostream>
#include <assert.h>
using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        for (int i = 0; ; ++i) {
            for (int j = 0; ; ++j) {
                if(j == needle.size()) {
                    return i;
                } else if (i + j == haystack.size()) {
                    return -1;
                } else if (needle[j] != haystack[i + j]) {
                    break;
                }
            }
        }
    }
};


void run_test_case(const string& s1, const string& s2, int expect) {
    Solution sol;
    int result = sol.strStr(s1, s2);
    cout << "str1: " << s1 << ", str2: " << s2 << ", result: " << result \
    << ", expect: " << expect << endl;
    assert(result == expect);
    cout << endl;
}

void test() {
    run_test_case("hello", "ll", 2);
    run_test_case("aaaaa", "bba", -1);
    run_test_case("aaa", "aaaa", -1);
    run_test_case("mississippi", "issip", 4);
}

int main() {
    test();
    return 0;
}
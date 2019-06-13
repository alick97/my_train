#include <string>
#include <iostream>
#include <assert.h>
using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        size_t haystack_index = 0;
        size_t needle_index = 0;
        int result = -1;
        if (needle.size() == 0) {
            return 0;
        }

        while (haystack_index < haystack.size()) {
                if (haystack[haystack_index] == needle[0]) {
                     int i = haystack_index, j = 0;
                     while (i < haystack.size() && j < needle.size()) {
                         if (haystack[i] == needle[j]) {
                             ++i;
                             ++j;
                         } else {
                             break;
                         }
                     }
                     if (j == needle.size()) {
                         result = haystack_index;
                         break;
                     } else if (i == haystack.size()) {
                         result = -1;
                         break;
                     }
                }
                ++haystack_index;
        }

        return result;
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
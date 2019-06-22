#include <string.h>
#include <iostream>
#include <assert.h>
using namespace std;

class Solution {
public:
    // int strStr(string haystack, string needle) {
    //     for (int i = 0; ; ++i) {
    //         for (int j = 0; ; ++j) {
    //             if(j == needle.size()) {
    //                 return i;
    //             } else if (i + j == haystack.size()) {
    //                 return -1;
    //             } else if (needle[j] != haystack[i + j]) {
    //                 break;
    //             }
    //         }
    //     }
    // }

    int strStr(string haystack, string needle) {
        return index_kmp(haystack, needle, 0);
    }


protected:
    int index_kmp(const string& s, const string& t, int pos) {
        //use next() fun to reduce match count
        int i = pos, j = 0;
        int *next = (int *)malloc(t.size()*sizeof(int));
        memset(next, -1, t.size() * sizeof(int));
        get_next(t, next, t.size());
        while (i < (int)s.length() && j < (int)t.length()) {
            if (s[i] == t[j]) {
                ++i;
                ++j;
            } else {
                j = next[j];
                if(j == -1) {
                    ++i;
                    j = 0;
                }
            }
        }

        free(next);

        if (j == t.length()) {
            return i - t.length();
        } else {
            return -1;
        }
    }

    void get_next(const string& t, int next[], int size) {
        /*
        0 1 2 3 4 5 6 7 8
        a b a a b c a c
        */
        if (size == 0) return;

        int i = 0, j = -1;
        next[0] = -1;
        while (i < size -1) {
            if (-1 == j || t[i] == t[j]) {
                ++i;
                ++j;
                if (t[i] != t[j]) {
                    next[i] = j;
                } else {
                    // for decrease worse case next count, eg t = aaa, s = aab
                    next[i] = next[j];       
                }
            } else {
                j = next[j];
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
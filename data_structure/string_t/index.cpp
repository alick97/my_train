#include <iostream>
#include <string.h>
#include <assert.h>
using namespace std;

void get_next(const string& s, int next[], int size);

int index(const string& s, const string& t, int pos) {
    // return sub str t position in str s after pos, if not exist return 0
    // t is not empty, 0 <= pos
    // time: worst to O(n * m)
    int i = pos, j = 0;
    while (i < s.length() && j < t.length()) {
        if (s[i] == t[j]) {
            ++i;
            ++j;
        } else {
            i = i - j + 1;
            j = 0;
        }
    }
    if (j == t.length()) {
        return i - t.length();
    } else {
        return 0;
    }
}

void test_index() {
    int result;
    // test 1
    result = index("abcd", "bc", 0);
    assert(1 == result);
    // test 2
    result = index("abcdbcdad", "bc", 2);
    assert(4 == result);
    // test 3, not found
    result = index("abc", "1", 0);
    assert(0 == result);
}

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

void test_index_kmp() {
    int result;
    // test 1
    result = index_kmp("abcd", "bc", 0);
    assert(1 == result);
    // test 2
    result = index_kmp("abcdbcdad", "bc", 2);
    assert(4 == result);
    // test 3, not found
    result = index_kmp("abc", "1", 0);
    assert(-1 == result);
    // test worse case
    result = index_kmp("aaaaaaaab", "aab", 0);
    assert(6 == result);
    // test t length than s
    result = index_kmp("aab", "aabaaaaab", 0);
    assert(-1 == result);
    // tmpty
    result = index_kmp("", "aaadfdsf", 0);
    assert(-1 == result);
}

int main() {
    // test_index();
    test_index_kmp();
    return 0;
}
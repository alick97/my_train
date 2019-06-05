#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool is_ok(const string &s) {
        int count = 0;
        for (size_t i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                count += 1;
            } else {
                count -=1;
            }
            if (count < 0) {
                return false;
            }
        }

        if (count == 0) {
            return true;
        } else {
            return false;
        }
    }

    vector<string> generateParenthesis(int n) {
        vector<string> v1, v2;
        if (n < 0) {
            return v1;
        }
        v1.push_back("(");
        v1.push_back(")");
        for (int i = 1; i < n * 2; i++) {
            while (!v1.empty()) {
                string s = v1.at(v1.size() -1);
                v1.pop_back();

                v2.push_back(s + ")");
                v2.push_back(s + "(");
            }
            v1.swap(v2);
        }
        while (!v1.empty()) {
            string s = v1.at(v1.size() -1);
            v1.pop_back();
            if (is_ok(s)) {
                v2.push_back(s);
            }
        }
        return v2;
    }
};

void test() {
/*
  example, given n = 3, a solution set is:  
  [
    "((()))",
    "(()())",
    "(())()",
    "()(())",
    "()()()"
  ]
*/
   Solution s;
   vector<string> v = s.generateParenthesis(3);
   for (int i = 0; i < v.size(); i++) {
       cout << v[i] << endl;
   }
}

int main() {
    test();
    return 0;
}
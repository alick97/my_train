#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> v;
        if (n == 0) {
            v.push_back("");
            return v;
        }

        for (int left_count = 0; left_count < n; left_count++) {
            vector<string> left_str_v = generateParenthesis(left_count);
            vector<string> right_str_v = generateParenthesis(n - 1 - left_count);
            for (int i = 0; i < left_str_v.size(); i++) {
                for (int j = 0; j < right_str_v.size(); j++) {
                    // note: "(" + left_str_v[i] + right_str_v[j] + ")" will repeat
                    v.push_back(left_str_v[i] + "(" + right_str_v[j] + ")");
                }
            }
        }
        return v;
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
   vector<string> v = s.generateParenthesis(10);
   for (int i = 0; i < v.size(); i++) {
       cout << v[i] << endl;
   }
}

int main() {
    test();
    return 0;
}
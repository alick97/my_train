#include <iostream>
#include <vector>
#include <deque>
using namespace std;


class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if (digits.length() == 0) {
            vector<string> v;
            return v;
        }
        string s_map[] = {
            "abc",
            "def",
            "ghi",
            "jkl",
            "mno",
            "pqrs",
            "tuv",
            "wxyz"
        };
        deque<string> result;
        result.push_back("");
        for(int i=0; i < digits.length(); i++) {
            string s_option = s_map[digits[i] - '2'];
            int count = result.size();
            while (count > 0) {
                string s = result.front();
                result.pop_front();
                for(int j=0; j < s_option.length(); j++) {
                    result.push_back(s + s_option[j]);
                }
                count--;
            }
        }
        vector<string> v = vector<string>(result.begin(), result.end());
        return v;
    }
};

void test() {
    Solution s;
    string input_s = "23";
    vector<string> result = s.letterCombinations(input_s);
    for (int i=0; i < result.size(); i++) {
        cout << result[i] << endl;
    }

}

int main() {
    test();
    return 0;
}
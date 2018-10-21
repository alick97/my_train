#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        if (1 == numRows) return s;
        int currentRow = 0;
        vector<string> rows(min(int(s.length()), numRows));
        bool goingDown = false;
        for (char c : s) {
                rows[currentRow] += c;
                if ( numRows - 1  == currentRow || 0 == currentRow) {
                    goingDown = !goingDown;
                }
                currentRow += goingDown ? 1 : -1;
        }
        string ret;
        for(string row : rows) {
            ret += row;
        }
        return ret;
    }
};

void test() {
    Solution s = Solution();
//     Input: s = "PAYPALISHIRING", numRows = 3
//     Output: "PAHNAPLSIIGYIR"
    cout <<"test1 result: " << s.convert("PAYPALISHIRING", 3) << endl;

// Input: s = "PAYPALISHIRING", numRows = 4
// Output: "PINALSIGYAHRPI"
    cout <<"test2 result: " << s.convert("PAYPALISHIRING", 4) << endl;
}



int main() {
    test();
    return 0;
}
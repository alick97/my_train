#include<iostream>
#include <vector>
#include <map>
#include <assert.h>
using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        map<char, int> row_count_map[9], col_count_map[9], matrix_map[9];
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                char c = board[i][j];
                if ('.' != c &&
                (
                    0 < row_count_map[i][c]++ ||
                    0 < col_count_map[j][c]++ ||
                    0 < matrix_map[i/3*3 + j/3][c]++
                )) {
                    return false;
                }
            }
        }

        return true;
    }
};

void test() {
    Solution s;
    bool result;
    vector<vector<char>> v1{
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };
    result = s.isValidSudoku(v1);
    assert(true == result);

    vector<vector<char>> v2{
        {'8','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };
    result = s.isValidSudoku(v2);
    assert(false == result);
}

int main() {
    test();
    return 0;
}

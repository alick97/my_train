#include <iostream>
#include <vector>
using namespace std;


class Solution {
public:

    Solution(): box_size(3), N(box_size * box_size) , sudokuSolved(false){
        for (int i =0; i < N; i++) {
            rows.push_back(vector<int>(N+1, 0));
            columns.push_back(vector<int>(N+1, 0));
            boxes.push_back(vector<int>(N+1, 0));
        }
    }

    void solveSudoku(vector<vector<char>>& board) {
        this->board = board;

        // init rows, columns and boxes
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                char num = this->board[i][j];
                if ('.' != num) {
                    int d = num - '0';
                    placeNumber(d, i, j);
                }
            }
        }
        backtrack(0, 0);
        board = this->board;
    }
protected:
    void placeNumber(int d, int row, int col) {
        /*
        Place a number d in (row, col) cell
        */
       int index = (row / box_size * box_size + col / box_size);

       rows[row][d]++;
       columns[col][d]++;
       boxes[index][d]++;

       board[row][col] = static_cast<char>(d + '0');
    }

    void removeNumber(int d, int row, int col) {
        /*
        Remove a number which didn't lead to a soluctionl
        */
       int index = (row / box_size * box_size + col / box_size);

       rows[row][d]--;
       columns[col][d]--;
       boxes[index][d]--;

       board[row][col] = '.';
    }

    bool couldPlace(int d, int row, int col) {
        /*
        Check if one could place a number d in (row, col) cell
        */
       int index = (row / box_size * box_size + col / box_size);
       return rows[row][d] + columns[col][d] +  boxes[index][d] == 0;
    }

    void backtrack(int row, int col) {
        /*
        Backtracking
        */
        // if cell is empty
        if (board[row][col] == '.') {
            // iterate over all number from 1 to 9
            for (int d = 1; d < 10; d++) {
                if (couldPlace(d, row, col)) {
                    placeNumber(d, row, col);
                    placeNextNumbers(row, col);

                    // if sudoku is solved, there is no need to backtrack
                    // since the single unique solution is promised
                    if (!sudokuSolved) {
                        removeNumber(d, row, col);
                    }
                }
            }
        } else {
            placeNextNumbers(row, col);
        }
    }

    void placeNextNumbers(int row, int col) {
        /*
        Call backtrack function in recursion
        to continue to place numbers
        till the moment we have a soluction
        */
       // if we're in the last cell
       // that means we have the soluction
       if (col == N -1 && row == N -1) {
           sudokuSolved = true;
       }
       // if not yet
       else {
           // if we're in the end of row
           // go the next row
           if (col == N -1) {
               backtrack(row + 1, 0);
           } else {
               backtrack(row, col + 1);
           }
       }
    }
protected:
    const int box_size; // box size
    const int N; // row size
    vector<vector<int>> rows;
    vector<vector<int>> columns;
    vector<vector<int>> boxes;
    vector<vector<char>> board;
    bool sudokuSolved;
};

void test() {
    Solution s;
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
    s.solveSudoku(v1);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << v1[i][j] << " |";
        }
        cout << endl;
    }
}

int main() {
    test();
    return 0;
}
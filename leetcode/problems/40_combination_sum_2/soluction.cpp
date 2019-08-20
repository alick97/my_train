#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        sort(candidates.begin(), candidates.end());
        vector<int> local;
        findCombination(result, 0, target, local, candidates);
        return result;
    }

    void findCombination(vector<vector<int>>& result, const int order, const int target, vector<int>& local, const vector<int>& candidates) {
        if (0 == target) {
            result.push_back(local);
            return;
        } else {
            for (int i = order; i < candidates.size(); i++) {
                if (candidates[i] > target) return;
                if ( i && candidates[i] == candidates[i-1] && i > order) continue;

                local.push_back(candidates[i]);
                findCombination(result, i+1, target-candidates[i], local, candidates);
                local.pop_back();
            }
        }
    }
};

void show_v(const vector<vector<int>> &v) {
        for (int i = 0; i < v.size(); i++) {
            for (int j = 0; j < v[i].size(); j++) {
                cout << v[i][j] << ", ";
            }
            cout << endl;
        }
}

void test() {
    Solution s;
// Input: candidates = [10,1,2,7,6,1,5], target = 8,
// A solution set is:
// [
//   [1, 7],
//   [1, 2, 5],
//   [2, 6],
//   [1, 1, 6]
// ]
    vector<int> v1{10, 1, 2, 7, 6, 1, 5};
    show_v(s.combinationSum2(v1, 8));

// Input: candidates = [2,5,2,1,2], target = 5,
// A solution set is:
// [
//   [1,2,2],
//   [5]
// ]
    cout << "========" << endl;
    vector<int> v2{2, 5, 2, 1, 2};
    show_v(s.combinationSum2(v2, 5));
}

int main() {
    test();
    return 0;
}
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;


class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        for (int i = 0; i < candidates.size(); i++) {
            forward_walk(candidates, result, target, i);
        }
        result.erase(result.begin());
        return result;
    }
protected:
    static bool forward_walk(vector<int>& candidates, vector<vector<int>>& result, int target, int start) {
        if (result.size() == 0) {
            result.push_back(vector<int>{});
        }
        if (start >= candidates.size()) {
            return false;
        }
        int init_num = accumulate(result[0].begin(), result[0].end(), 0);

        if (candidates[start] + init_num == target) {
            result[0].push_back(candidates[start]);
            result.push_back(result[0]);
            result[0].pop_back();
            return true;
        } else if (candidates[start] + init_num > target) {
            return false;
        } else if (candidates[start] + init_num < target) {
            bool is_found = false;
            result[0].push_back(candidates[start]);

            for (int i = start; i < candidates.size(); i++) {
                is_found = forward_walk(candidates, result, target, i) || is_found;
            }
            
            if (!result[0].empty()) {
                result[0].pop_back();
            }
            return is_found;
        }
        return false;
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
//     Input: candidates = [2,3,6,7], target = 7,
// A solution set is:
// [
//   [7],
//   [2,2,3]
// ]
    vector<int> v1{2, 3, 6, 7};
    show_v(s.combinationSum(v1, 7));

// Input: candidates = [2,3,5], target = 8,
// A solution set is:
// [
//   [2,2,2,2],
//   [2,3,3],
//   [3,5]
// ]
    cout << "========" << endl;
    vector<int> v2{2, 3, 5};
    show_v(s.combinationSum(v2, 8));
}

int main() {
    test();
    return 0;
}
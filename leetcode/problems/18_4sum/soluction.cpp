#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;

/*
Given array nums = [1, 0, -1, 0, -2, 2], and target = 0.

A solution set is:
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]
*/

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> result;
        int n = nums.size();
        if (n < 4) {
            return result;
        }
        std::sort(nums.begin(), nums.end());
        for (int i = 0; i < n-3; i++) {
            if (i > 0 && nums[i] == nums[i-1]) {
                continue;
            }
            if (nums[i] + nums[i+1] + nums[i+2] + nums[i+3] > target) {
                break;
            }
            if (nums[i] + nums[n-1] + nums[n-2] + nums[n-3] < target) {
                continue;
            }

            for(int j = i+1; j < n - 2; j++) {
                if (j > i+1 && nums[j] == nums[j-1]) {
                    continue;
                }
                if (nums[i] + nums[j] + nums[j+1] + nums[j+2] > target) {
                    break;
                }
                if (nums[i] + nums[j] + nums[n-1] + nums[n-2] < target) {
                    continue;
                }
                int left = j + 1;
                int right = n - 1;
                while (left < right) {
                    int sum = nums[i] + nums[j] + nums[left] + nums[right];
                    if (sum < target) {
                        left++;
                    } else if (sum > target) {
                        right--;
                    } else {
                        result.push_back(vector<int>{nums[i], nums[j], nums[left], nums[right]});
                        do {left++;} while (nums[left] == nums[left-1] && left < right);
                        do {right--;} while (nums[right] == nums[right+1] && left < right);
                    }
                }
            }
        }
        return result;
    }
};


void test() {
    vector<int> v = vector<int> {1, 0, -1, 0, -2, 2};
    Solution s;
    vector<vector<int>> result = s.fourSum(v, 0);
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j] << " , ";
        }
        cout << endl;
    }
}

int main() {
    test();
    return 0;
}
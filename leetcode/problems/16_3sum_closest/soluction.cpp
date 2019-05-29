#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <assert.h>
using namespace std;

/*
Given array nums = [-1, 2, 1, -4], and target = 1.

The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
*/

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int min_result = INT32_MAX;
        if (nums.size() < 2) {
            return 0;
        }

        std::sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 2; i++) {
            if (i > 0 && nums[i] == nums[i-1]) {
                    continue;
            }
            int left_index = i + 1;
            int right_index = nums.size() - 1;
            bool is_find_result = false;
            while (left_index < right_index) {
                int sum = nums[i] + nums[left_index] + nums[right_index];
                // cout << sum << " | " << min_result << " | " << nums[i] << " | " << nums[left_index]
                // << " | " << nums[right_index] << endl;
                int diff = target - sum;
                if (abs(diff) < abs(min_result)) {
                    min_result = diff;
                }
                if (sum > target) {
                    while (right_index > left_index && nums[right_index] == nums[right_index-1]) {
                        --right_index;
                    }
                    --right_index;
                } else if (sum < target) {
                    while (left_index < right_index && nums[left_index] == nums[left_index+1]) {
                        ++left_index;
                    }
                    ++left_index;
                } else {
                    min_result = 0;
                    is_find_result = true;
                    break;
                }
            }

            if (is_find_result == true) {
                break;
            }

        }

        return target - min_result;
    }
};

void test() {
    Solution s;
    int num_arr[] = {-1, 2, 1, -4};
    vector<int> v(num_arr, num_arr + sizeof(num_arr)/sizeof(int));
    int result = s.threeSumClosest(v, 1);
    cout << result << endl;
    assert(result == 2);
}

int main() {
    test();
    return 0;
}
#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int left_index = 0, right_index = nums.size() - 1;
        vector<int> result{-1, -1};
        while (left_index <= right_index) {
            int mid_index = (left_index + right_index) / 2;
            if (target < nums[mid_index]) {
                right_index = mid_index - 1;
            } else if (target > nums[mid_index]) {
                left_index = mid_index + 1;
            } else {
                result[0] = result[1] = mid_index;
                break;
            }
        }

        // while (result[0] > 0 && nums[result[0] - 1] == target) {
        //     --result[0];
        // }

        // while (result[1] > 0
        //     && result[1] + 1 < nums.size()
        //     && nums[result[1] + 1] == target) {
        //         ++result[1];
        //     }
        left_index = 0;
        right_index = result[0];
        while (right_index >= 0  && left_index <= right_index) {
            int mid_index = (left_index + right_index) / 2;
            if (nums[mid_index] < target) {
                left_index = mid_index + 1;
            } else if (nums[mid_index] == target) {
                result[0] = mid_index;
                right_index = mid_index - 1;
            }
            // cout << "l";
        }

        right_index = nums.size() - 1;
        left_index = result[1];
        while (left_index >= 0 && left_index <= right_index) {
            int  mid_index = (left_index + right_index) / 2;
            if (nums[mid_index] > target) {
                right_index = mid_index - 1;
             } else if (nums[mid_index] == target) {
                 result[1] = mid_index;
                 left_index = mid_index + 1;
             }
            //  cout << "r";
        }

        return result;
    }
};


void show(const vector<int>& v) {
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
}

void test() {
    Solution s;
/*
Input: nums = [5,7,7,8,8,10], target = 8
Output: [3,4]
*/
    vector<int> v1{5,7,7,8,8,10};
    show(s.searchRange(v1, 8));
    cout << endl;
/*
Input: nums = [5,7,7,8,8,10], target = 6
Output: [-1,-1]
*/
    vector<int> v2{5,7,7,8,8,10};
    show(s.searchRange(v2, 6));
    cout << endl;
/*
nums = [5, 5, 5], target = 5
[0, 2]
*/
    vector<int> v3{5, 5, 5};
    show(s.searchRange(v3, 5));
    cout << endl;
/*
[5,7,7,8,8,10], 8
3, 4
*/
    vector<int> v4{5,7,7,8,8,10};
    show(s.searchRange(v4, 8));
    cout << endl;
}

int main() {
    test();
    return 0;
}
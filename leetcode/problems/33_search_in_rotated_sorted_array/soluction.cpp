#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left_index = 0;
        int right_index = nums.size() - 1;
        int result_index = -1;
        while (left_index <= right_index) {
            int mid_index = (left_index + right_index) / 2;

            if (target < nums[mid_index]) {
                if (nums[mid_index] >= nums[left_index]) {
                    if (target > nums[left_index]) {
                        right_index = mid_index - 1;
                    } else if (target < nums[left_index]) {
                        left_index = mid_index + 1;
                    } else {
                        result_index = left_index;
                        break;
                    }
                } else {
                    right_index = mid_index - 1;
                }
            } else if (target > nums[mid_index]) {
                if (nums[mid_index] < nums[right_index]) {
                    if (target < nums[right_index]) {
                        left_index = mid_index + 1;
                    } else if (target > nums[right_index]) {
                        right_index = mid_index - 1;
                    } else {
                        result_index = right_index;
                        break;
                    }
                } else {
                        left_index = mid_index + 1;
                }            
            } else {
                result_index = mid_index;
                break;
            }
        }

        // cout << result_index << endl;
        return result_index;
    }
};


void test() {
    Solution s;
/*
Example 1:

Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4
*/
    vector<int> v1{4,5,6,7,0,1,2};
    assert(4 == s.search(v1, 0));
/*
Example 2:

Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
*/
    vector<int> v2{4,5,6,7,0,1,2};
    assert(-1 == s.search(v2, 3));

/*
  nums 1 3,  target 3
  result 1
*/
    vector<int> v3{1, 3};
    assert(1 == s.search(v3, 3));
}


int main() {
    test();
    return 0;
}
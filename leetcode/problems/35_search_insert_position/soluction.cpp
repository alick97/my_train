#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        if (0 == nums.size()) {
            return 0;
        }
        int left = 0, right = nums.size() - 1;
        int result = -1;
        int mid = 0;
        while (left <= right) {
            mid = (left + right) / 2;
            if (target >  nums[mid]) {
                left = mid + 1;
            } else if (target < nums[mid]) {
                right = mid - 1;
            } else {
                result = mid;
                break;
            }
        }

        if (-1 == result) {
            result = target > nums[mid] ? mid + 1 : mid;
        }

        return result;
    }
};


void test() {
    Solution s;
/*
Example 1:

Input: [1,3,5,6], 5
Output: 2
*/
    vector<int> v1{1, 3, 5, 6};
    assert(2 == s.searchInsert(v1, 5));
/*
Example 2:

Input: [1,3,5,6], 2
Output: 1
*/
    vector<int> v2{1, 3, 5, 6};
    assert(1 == s.searchInsert(v2, 2));
/*
Example 3:

Input: [1,3,5,6], 7
Output: 4
*/
    vector<int> v3{1, 3, 5, 6};
    assert(4 == s.searchInsert(v3, 7));
/*
Example 4:

Input: [1,3,5,6], 0
Output: 0
*/
    vector<int> v4{1, 3, 5, 6};
    assert(0 == s.searchInsert(v4, 0));
}

int main() {
    test();
    return 0;
}
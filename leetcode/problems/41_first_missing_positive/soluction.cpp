#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
       int count = nums.size(); 
       for (int i = 0; i < count; ++i) {
           while (nums[i] > 0 && nums[i] <= count && nums[nums[i]-1] != nums[i]) {
               swap(nums[i], nums[nums[i] - 1]);
           }
       }

       for (int i = 0; i < count; ++i) {
           if (nums[i] != i + 1) {
               return i + 1;
           }
       }

       return count + 1;
    }
};



void test() {
    Solution s = Solution();
// Example 1:
// 
// Input: [1,2,0]
// Output: 3
    vector<int> v1{1, 2, 0};
    int result = s.firstMissingPositive(v1);
    assert(3 == result);

// Example 2:
// 
// Input: [3,4,-1,1]
// Output: 2
    vector<int> v2{3, 4, -1, 1};
    result = s.firstMissingPositive(v2);
    assert(2 == result);
// Example 3:
// 
// Input: [7,8,9,11,12]
// Output: 1
    vector<int> v3{7, 8, 9, 11, 12};
    result = s.firstMissingPositive(v3);
    assert(1 == result);
}

int main() {
    test();
    return 0;
}
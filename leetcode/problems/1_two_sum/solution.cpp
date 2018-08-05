#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target);
};


/*
Given nums = [2, 7, 11, 15], target = 9,
Because nums[0] + nums[1] = 2 + 7 = 9,
*/
vector<int> Solution::twoSum(vector<int>& nums, int target) {
    vector<int> result(2);
    for (int i = 0; i < nums.size(); ++i) {
        for (int j = i + 1; j < nums.size(); ++j ) {
            cout<< nums[i] << "," << nums[j] << endl;
            if ( nums[i] + nums[j] == target) {
                result[0] = i;
                result[1] = j;
                break;
            }
        }
    }
    return result;
}


int main() {
    Solution sl;
    vector<int> v = {2, 7, 11, 15};
    vector<int> result(2);
    int target = 9;
    result = sl.twoSum(v, target);
    if (result.size() == 2 && v[result[0]] + v[result[1]] == target) {
        cout << "PASS" << endl;
    } else {
        cout << "FAILED" << endl;
    }
    
    return 0;
}


#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <sys/time.h>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target);
    vector<int> twoSum_2(vector<int>& nums, int target);
};


/*
Given nums = [2, 7, 11, 15], target = 9,
Because nums[0] + nums[1] = 2 + 7 = 9,
complex: O(n^2)
*/
vector<int> Solution::twoSum(vector<int>& nums, int target) {
    vector<int> result(2);
    for (int i = 0; i < nums.size(); ++i) {
        for (int j = i + 1; j < nums.size(); ++j ) {
            // cout<< nums[i] << "," << nums[j] << endl;
            if ( nums[i] + nums[j] == target) {
                result[0] = i;
                result[1] = j;
                break;
            }
        }
    }
    return result;
}

/*
Given nums = [2, 7, 11, 15], target = 9,
Because nums[0] + nums[1] = 2 + 7 = 9,
complex: O(n)
*/
vector<int> Solution::twoSum_2(vector<int>& nums, int target) {
    vector<int> result(2);
    unordered_map<int, int> nums_index_map;
    for (int nums_index = 0; nums_index < nums.size(); ++nums_index) {
        int pair_num = target - nums[nums_index];
        if (nums_index_map.find(pair_num) != nums_index_map.end()) {
            result[0] = nums_index;
            result[1] = nums_index_map[pair_num];
            break;
        }
        else {
            nums_index_map.insert(make_pair(nums[nums_index], nums_index));
        }
    }
    return result;
}

int main() {
    Solution sl;
    struct timeval time_start, time_end;
    int time_use_s = -1;
    int time_use_us = -1;
    vector<int> v = {2, 7, 11, 15};
    vector<int> result(2);
    int target = 9;
    gettimeofday(&time_start, NULL);
    // result = sl.twoSum(v, target);
    result = sl.twoSum_2(v, target);
    gettimeofday(&time_end, NULL);
    time_use_s = time_end.tv_sec - time_start.tv_sec;
    time_use_us = time_end.tv_usec - time_start.tv_usec;

    cout << result[0] << ", " << result[1] << endl;
    if (result.size() == 2 && v[result[0]] + v[result[1]] == target) {
        cout << "PASS" << endl;
    } else {
        cout << "FAILED" << endl;
    }
    cout << "time_use: "<< time_use_s << "s| " << time_use_us << "us" << endl;
    return 0;
}


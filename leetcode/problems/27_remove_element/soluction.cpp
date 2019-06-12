#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        if (nums.size() == 0) {
            return 0;
        }
        int right_index = nums.size() - 1;
        int left_index = 0;
        while (left_index < right_index) {
            while (right_index > left_index && nums[right_index] == val) {
                --right_index;
            }
            if (left_index < right_index) {
                if (nums[left_index] == val) {
                    nums[left_index] = nums[right_index--];
                } else {
                    ++left_index;
                }
            }
        }

        if (nums[left_index] == val) {
            return left_index;
        } else {
            return left_index + 1;
        }
    }
};


void test() {
    /*
     Given nums = [3,2,2,3], val = 3,
 
     Your function should return length = 2, with the first two elements of nums being 2.
 
     It doesn't matter what you leave beyond the returned length.;
    */
    // vector<int> v{3,2,2,3};

    /*
     Given nums = [0,1,2,2,3,0,4,2], val = 2,

     Your function should return length = 5, with the first five elements of nums containing 0, 1, 3, 0, and 4.
    */
    vector<int> v{0,1,2,2,3,0,4,2};
    Solution s;
    int count = s.removeElement(v, 2);
    cout << "count: " << count << endl;
    for (int i = 0; i < count; ++i) {
        cout << v[i] << "<-";
    }
    cout << "end" << endl;
}

int main() {
    test();
    return 0;
}
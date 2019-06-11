#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int index_1 = 0, index_2 = 1;
        // if (nums.size() == 0) {
        //     return 0;
        // }

        while (index_1 < nums.size() && index_2 < nums.size()) {
            while (index_2 < nums.size() && nums[index_1] == nums[index_2]) {
                ++index_2;
            }

            if (index_2 < nums.size()) {
                if (index_2 - index_1 > 1) {
                    swap(nums[index_1 + 1], nums[index_2]);
                }
                ++index_1;
                ++index_2;
            } else {
                break;
            }               
        }

        return nums.size() == 0 ? 0 : index_1 + 1;
    }
};

void test() {
/*
[0,0,1,1,1,2,2,3,3,4] -> 5
*/
    // vector<int> v{0,0,1,1,1,2,2,3,3,4};
    vector<int> v{1, 1, 2};
    Solution s;
    int count = s.removeDuplicates(v);
    cout << "count: " << count << endl;
    for (int i = 0; i < count; ++i) {
        cout << v[i] << "<-";
    }
    cout << "end" << endl;
}

int main () {
    test();
    return 0;
}


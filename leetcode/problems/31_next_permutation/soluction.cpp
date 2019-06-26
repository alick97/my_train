#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int i = nums.size() - 2;
        while (i >= 0 && nums[i+1] <= nums[i]) {
            --i;
        }
        if (i >= 0) {
            int j = nums.size() - 1;
            while (j >= 0 && nums[j] <= nums[i]) {
                --j;
            }
            swap(nums[i], nums[j]);
        }
        reverse(nums.begin() + i + 1, nums.end());
    }
};

void show(const vector<int>& v) {
    for(int i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << endl;
}

void test() {
    /*
      1,2,3 → 1,3,2
      3,2,1 → 1,2,3
      1,1,5 → 1,5,1
    */
   Solution s;
   vector<int> v1{1, 2, 3};
   s.nextPermutation(v1);
   show(v1);

   vector<int> v2{3, 2, 1};
   s.nextPermutation(v2);
   show(v2);

   vector<int> v3{1, 1, 5};
   s.nextPermutation(v3);
   show(v3);
}

int main() {
    test();
    return 0;
}

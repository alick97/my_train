#include <vector>
#include <iostream>
#include <assert.h>
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int left_index = 0;
        int right_index = height.size() - 1;
        int max_area = 0;
        while (left_index < right_index) {
            max_area = max(max_area, min(height[left_index], height[right_index]) * (right_index - left_index));
            if (height[left_index] < height[right_index]) {
                left_index += 1;
            } else {
                right_index -= 1;
            }
        }

        return max_area;
    }
};


void test() {
    int arr[] = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    vector<int> v = vector<int>(arr, arr + sizeof(arr) / sizeof(int));
    Solution s = Solution();
    int result = s.maxArea(v);
    assert(result == 49);
}

int main() {
    test();
    return 0;
}

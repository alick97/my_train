#include <iostream>
#include <vector>
using namespace std;

class Solution {
    public:
        double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
            int nums1_len = nums1.size();
            int nums2_len = nums2.size();
            if (nums1_len > nums2_len) {
                swap(nums1, nums2);
                swap(nums1_len, nums2_len);
            }
            int i_min = 0, i_max = nums1_len;
            int half_len = (nums1_len + nums2_len + 1) / 2;
            int i = (i_min + i_max) / 2;
            int j = half_len - i;
            while ( i_min <= i_max) {
                i = (i_min + i_max) / 2;
                j = half_len - i;
                if ( i > i_min && nums1[i-1] > nums2[j]) {
                    // nums1 left part value is too big
                    i_max = i - 1;
                }
                else if (i < i_max && nums2[j-1] > nums1[i]) {
                    // nums1 right part value is too small
                    i_min = i + 1;
                } else {
                    // i poisition is ok
                    int left_max = 0, right_min = 0;
                    if ( i == 0) {
                        left_max = nums2[j-1];
                    } else if ( j == 0) {
                        left_max = nums1[i-1];
                    } else {
                        left_max = max(nums1[i-1], nums2[j-1]);
                    }

                    if ((nums1_len + nums2_len) % 2 == 1) {
                        return left_max;
                    }

                    if ( i == nums1_len) {
                        right_min = nums2[j];
                    } else if ( j == nums2_len) {
                        right_min = nums1[i];
                    } else {
                        right_min = min(nums1[i], nums2[j]);
                    }

                    return (left_max + right_min) / 2.0; 
                }
            }
            return 0.0;
        }
};


void test(){
    vector<int> v1, v2, v3, v4, v5;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);

    v2.push_back(7);
    v2.push_back(8);
    v2.push_back(9);
    Solution s;
    double result = s.findMedianSortedArrays(v1, v2);
    cout << result << endl; // 4

    v3.push_back(1);
    v3.push_back(2);

    v4.push_back(3);
    v4.push_back(4);
    result = s.findMedianSortedArrays(v3, v4);
    cout << result << endl; // 2.5

    v5.push_back(-1);
    v5.push_back(3);
    result = s.findMedianSortedArrays(v3, v5);
    cout << result << endl; // 1.5
}

int main() {
    test();
    return 0;
}
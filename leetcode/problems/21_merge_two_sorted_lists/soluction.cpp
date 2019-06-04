#include <iostream>
#include <assert.h>
using namespace std;
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {};
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *head = NULL, **cur_p = &head;
        while (l1 != NULL && l2 != NULL) {
            if (l1->val <= l2->val) {
                *cur_p = l1;
                l1 = l1->next;
            } else {
                *cur_p = l2;
                l2 = l2->next;
            }
            cur_p = &(*cur_p)->next;
        }

        if (l1 == NULL) {
            *cur_p = l2;
        } else {
            *cur_p = l1;
        }
        return head;
    }
};


void test() {
    /*
        Input: 1->2->4, 1->3->4
        Output: 1->1->2->3->4->4
    */
   ListNode l1_1(1), l1_2(2), l1_3(4);
   ListNode l2_1(1), l2_2(3), l2_3(4);
   l1_1.next = &l1_2;
   l1_2.next = &l1_3;
   
   l2_1.next = &l2_2;
   l2_2.next = &l2_3;

   int arr[] = {1, 1, 2, 3, 4, 4};
   Solution s;
   ListNode* p = s.mergeTwoLists(&l1_1, &l2_1);
   for (int i = 0; i < sizeof(arr)/sizeof(int); i++) {
       cout << arr[i] << "--" << p->val << endl;
    //    assert(arr[i] == p->val);
       p = p->next;
   }
}


int main() {
    test();
    return 0;
}
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {};
};

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode *pp = head;
        while (pp != NULL) {
            if (pp->next != NULL) {
                swap(pp->val, pp->next->val);
                pp = pp->next->next;
            } else {
                break;
            }
        }

        return head;
    }
};

void test() {
/*
Given 1->2->3->4, you should return the list as 2->1->4->3.
*/
    int arr[] = {1, 2, 3, 4};
    ListNode *head = new ListNode(0);
    ListNode *p = head;
    for (int i = 0; i < sizeof(arr)/sizeof(int); i++) {
        p->next = new ListNode(arr[i]);
        p = p->next;
    }

    Solution s;
    ListNode *new_head = s.swapPairs(head->next);

    if (head != NULL) {
        delete head;
    }
    p = new_head;

    while (p != NULL) {

        cout << p->val << "->";
        ListNode *tmp = p;
        p = p->next;
        delete tmp; 
    }
    cout << "end" << endl;
}

int main() {
    test();
    return 0;
}
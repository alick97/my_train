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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode *p_head = head, *p_tail = head, *p_tail_next = NULL;
        ListNode *p_result = head, *pre_head = NULL;
        while (p_tail != NULL) {
            int count = k;
            p_tail = p_head;
            while (count > 1 && p_tail != NULL) {
                p_tail = p_tail->next;
                --count;
            }
            if (p_tail != NULL && count == 1) {
                if (pre_head != NULL) {
                    pre_head->next = p_tail;
                } else {
                    p_result = p_tail;
                }
                p_tail_next = p_tail->next;
                reverseList(p_head, p_tail);
                pre_head = p_head;
                p_head = p_tail_next;
            } else if (p_tail == NULL) {
                if (pre_head != NULL) {
                    pre_head->next = p_tail_next;
                }
                break;
            } else {
                break;
            }
        }
        return p_result;
    }

    ListNode* reverseList(ListNode* head, ListNode* tail) {
        if (head == tail) {
            return head;
        }
        ListNode *p_reverse_end = reverseList(head->next, tail);
        p_reverse_end->next = head;
        return head;
    }
};

void test() {
    /*Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5*/
    int arr[] = {1, 2, 3, 4, 5};
    ListNode *head = new ListNode(0);
    ListNode *p = head;
    for (int i = 0; i < sizeof(arr)/sizeof(int); i++) {
        p->next = new ListNode(arr[i]);
        p = p->next;
    }

    Solution s;
    ListNode *new_head = s.reverseKGroup(head->next, 3);
    delete head;
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
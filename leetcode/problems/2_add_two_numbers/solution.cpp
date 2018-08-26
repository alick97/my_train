#include <iostream>
using namespace std;
/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:

    // Test case	Explanation
    // l1=[0,1]l1=[0,1]
    // l2=[0,1,2]l2=[0,1,2]	When one list is longer than the other.
    // l1=[]l1=[]
    // l2=[0,1]l2=[0,1]	When one list is null, which means an empty list.
    // l1=[9,9]l1=[9,9]
    // l2=[1]l2=[1]
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode result_head =  ListNode(0);
        ListNode* curr = &result_head;
        ListNode* p=l1,*q=l2;
        int carry = 0;
        int x=0,y=0;
        while (NULL != p || NULL != q) {
            if (NULL != p) {
                x = p->val;
                p = p->next;
            } else {
                x = 0;
            }

            if (NULL != q) {
                y = q->val;
                q = q->next;
            } else {
                y = 0;
            }
            int sum = carry + x + y;
            carry = sum / 10;
            curr->next = new ListNode(sum % 10);
            curr = curr->next;
        }
        if (carry > 0) {
            curr->next = new ListNode(carry);
        }
        return result_head.next;
    }
};

ListNode* add_tail(ListNode* head, int val) {
    ListNode* curr = head;
    while (NULL != curr && NULL != curr->next) {
        curr = curr->next;
    }
    if (NULL != curr) {
        curr->next = new ListNode(val);
    }
    return head;
}

void print_list_node(ListNode* head) {
    while (NULL != head) {
        cout << head->val << endl;
        head = head->next;
    }
}

void test() {
    ListNode head1 = ListNode(0);
    ListNode head2 = ListNode(0);
// Input: head1 (2 -> 4 -> 3) + head2 (5 -> 6 -> 4)
// Output: 7 -> 0 -> 8
// Explanation: 342 + 465 = 807.
    add_tail(&head1, 2);
    add_tail(&head1, 4);
    add_tail(&head1, 3);
    cout << "head1:" << endl;
    print_list_node(head1.next);
    add_tail(&head2, 5);
    add_tail(&head2, 6);
    add_tail(&head2, 4);
    cout << "head2:" << endl;
    print_list_node(head2.next);
    ListNode* result = NULL;
    result = Solution().addTwoNumbers(head1.next, head2.next);
    cout << "result:" << endl;
    print_list_node(result);
}


int main() {
    test();
    return 0;
}
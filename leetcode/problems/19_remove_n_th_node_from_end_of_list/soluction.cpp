#include <iostream>
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
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode **p1 = &head, *p2 = head;
        while (n > 0) {
            p2 = p2->next;
            n--;
        }
        while (p2 != NULL) {
            p2 = p2->next;
            p1 = &(*p1)->next;
        }
        p2 = *p1;
        *p1 = (*p1)->next;
        delete p2;
        return head;
    }
};


void show(ListNode* p) {
   while (p != NULL) {
       cout << p->val << "->";
        p = p->next;
   }
   cout << "end" << endl;
}

void test() {
/**
 * Example:
 * Given linked list: 1->2->3->4->5, and n = 2.
 * After removing the second node from the end, the linked list becomes 1->2->3->5.
 */
    ListNode* head = new ListNode(1);
    ListNode* pre = head;
    for (int i = 1; i < 5; i++) {
        pre->next = new ListNode(i+1);
        pre = pre->next;
    }
    show(head);

    Solution s;
    head = s.removeNthFromEnd(head, 1);
    show(head);
    head = s.removeNthFromEnd(head, 4);
    show(head);
    cout << endl;
}

int main() {
    test();
    return 0;
}
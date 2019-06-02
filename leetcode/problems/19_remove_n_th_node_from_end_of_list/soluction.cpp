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
        if (n < 1 || head == NULL) {
            return NULL;
        }
        ListNode* tmp_p = head;
        int len = 1;
        while (tmp_p->next != NULL) {
            len++;
            tmp_p = tmp_p->next;
        }
        int count = len - n;
        if (count == 0) {
            tmp_p = head->next;
            delete head;
            return tmp_p;
        }

        tmp_p = head;
        ListNode* pre = head;
        while (count > 0) {
            pre = tmp_p;
            tmp_p = tmp_p->next;
            count--;
        }

        tmp_p = pre->next->next;
        delete pre->next;
        pre->next = tmp_p;
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
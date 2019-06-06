#include <iostream>
#include <vector>
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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode *head = NULL;
        while (!lists.empty()) {
            head = mergeTwoList(head, lists[lists.size() - 1]);
            lists.pop_back();
        }
        return head;
    }

    ListNode* mergeTwoList(ListNode *l1, ListNode *l2) {
        if (NULL == l1) {
            return l2;
        }
        if (NULL == l2) {
            return l1;
        }

        if (l1->val < l2->val) {
            l1->next = mergeTwoList(l1->next, l2);
            return l1;
        } else {
            l2->next = mergeTwoList(l1, l2->next);
            return l2;
        }
    }
};

void test() {
/*
Input:
[
  1->4->5,
  1->3->4,
  2->6
]
Output: 1->1->2->3->4->4->5->6
*/
    vector<ListNode*> vl;
    vector<vector<int>> arr;
    arr.push_back(vector<int>{1, 4, 5});
    arr.push_back(vector<int>{1, 3, 4});
    arr.push_back(vector<int>{2, 6});
    for (int i = 0; i < arr.size(); i++) {
        ListNode *l = new ListNode(0);
        ListNode *p = l;
        for (int j = 0; j < arr[i].size(); j++) {
            p->next = new ListNode(arr[i][j]);
            p = p->next;
        }
        vl.push_back(l->next);
        delete l;
    }

    Solution s;
    ListNode *head = s.mergeKLists(vl);
    ListNode *tmp = NULL;

    while (head != NULL) {
        cout << head->val << "->";
        tmp = head;
        head = head->next;
        delete tmp;
    }
    cout << "end" << endl;
}

int main() {
    test();
    return 0;
}
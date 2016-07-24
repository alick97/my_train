#pragma once
#include <iostream>
using namespace std;
struct ListNode
{
    int _data;
    ListNode* _next;

    ListNode(int data = 0)
        :_data(data)
        ,_next(NULL)
    {}
 };


/******************
 * test1:  从尾到头打印单链表
*****/
void PrintListFromEnd(ListNode* pList)
{
    if (pList == NULL)
    {
        return;
    }

    PrintListFromEnd(pList->_next);
    cout<<pList->_data<<"-";
}

void test_PrintListFromEnd()
{
    ListNode* l1 = new ListNode(1);
    ListNode* l2 = new ListNode(2);
    ListNode* l3 = new ListNode(3);
    ListNode* l4 = new ListNode(4);

    l1->_next = l2;
    l2->_next = l3;
    l3->_next = l4;

    PrintListFromEnd(l1);
}



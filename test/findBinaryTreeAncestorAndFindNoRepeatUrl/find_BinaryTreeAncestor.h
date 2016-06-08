#pragma once
#include <iostream>
using namespace std;

/****************
 * 二叉树中 找两个结点的最近的公共祖先结点
******************/

struct Node
{
    Node* left;
    Node* right;
    int value;

    Node(int v)
        :value(v)
        ,left(NULL)
        ,right(NULL)
    {}
};

// 方法一 int count 计数
int _find_ancestor(Node* root, Node* & ancestor, const Node* a, const Node* b)
{
    if (root == NULL)
    {
        return 0;
    }
    int count = 0;
  

    count += _find_ancestor(root->left, ancestor, a , b);

    if (root == a || root == b)
    {
        count += 1;
    }
    /*if (count == 2)
    {
        ancestor = root;
    }*/

   count += _find_ancestor(root->right, ancestor, a, b);

    if (count == 2)
    {
        ancestor = root ;
        count = 0; // 防止返回 时 上面count的值还是2 导致 ancestor不准确 被覆盖
    }
    
    return count;

}

void test_find_ancestor()
{
   //     1
    //  2   3
    // 4  5
    Node n1(1);
    Node n2(2);
    Node n3(3);
    Node n4(4);
    Node n5(5);

    n1.left = &n2;
    n1.right = &n3;
    n2.left = &n4;
    n2.right = &n5;

    Node* ancestor = NULL;
    // 4 5
   // _find_ancestor(&n1, ancestor,&n4, &n5); 

    // 2 5
   // _find_ancestor(&n1, ancestor,&n2, &n5); 

    // 5 3
     _find_ancestor(&n1, ancestor,&n5, &n3); 
}


// 方法二 bool判别
bool find_ancestor_bool(Node* root, Node* & ancestor, const Node* a, const Node* b)
{
    if (root == NULL)
    {
        return false;
    }
  
    bool  b_left = find_ancestor_bool(root->left, ancestor, a, b);

    bool b_right = find_ancestor_bool(root->right, ancestor, a, b);
    
    
    if (root == a || root == b)
    {
        if (b_left || b_right)
        {
            ancestor = root;
        }

        return true;
    }

    if (b_left && b_right)
    {
        ancestor = root;
    }

    return b_left || b_right;

}


void test_find_ancestor_bool()
{
   //     1
    //  2   3
    // 4  5
    Node n1(1);
    Node n2(2);
    Node n3(3);
    Node n4(4);
    Node n5(5);

    n1.left = &n2;
    n1.right = &n3;
    n2.left = &n4;
    n2.right = &n5;

    Node* ancestor = NULL;
    // 4 5
    //find_ancestor_bool(&n1, ancestor,&n4, &n5); 

    // 2 5
   // find_ancestor_bool(&n1, ancestor,&n2, &n5); 

    // 5 3
    // find_ancestor_bool(&n1, ancestor,&n5, &n3); 
     // 1 5
     find_ancestor_bool(&n1, ancestor,&n1, &n5); 
}

// 方法3 利用栈 数组或 链表 记录 找到结点的 路径  最后 遍历两个 栈（数组或链表） 找到第一次出现比相同的点的前一个 即为公共祖先
// 注意 如果当前不是 返回时 要将当前压栈的 元素弹出 栈用引用传入
// 这里以 vector 为例 方便遍历
#include<vector>

void find_ancestor_vector_R(Node* root, vector<Node*>& va,vector<Node*>& vb, Node* a, Node* b, Node* &ancestor)
{
    if (root == NULL)
    {
        return;
    }

    va.push_back(root);
    vb.push_back(root);

    find_ancestor_vector_R(root->left, va, vb, a, b, ancestor);
    find_ancestor_vector_R(root->right, va, vb, a, b, ancestor);
    
    if (va.back() != a)
    {
        va.pop_back();    
    }

    if (vb.back() != b)
    {
        vb.pop_back();
    }
}

Node* find_ancestor_vector(Node* root, Node* a, Node* b)
{
    vector<Node*> va,vb;
    Node* ancestor = NULL;

    find_ancestor_vector_R(root, va, vb, a, b, ancestor);

    // 找va vb 的分叉点 之前的点 
    int i = 0;
    while (i < va.size() && i < vb.size() && va[i] == vb[i])
    {
        ancestor = va[i];
        i++;
    }

    return ancestor;
}

void  test_find_ancestor_vector()
{
    //     1
    //  2   3
    // 4  5
    Node n1(1);
    Node n2(2);
    Node n3(3);
    Node n4(4);
    Node n5(5);

    n1.left = &n2;
    n1.right = &n3;
    n2.left = &n4;
    n2.right = &n5;

    Node* ancestor = NULL;
    // 4 5
    ancestor = find_ancestor_vector(&n1, &n4, &n5); 

    // 2 5
    ancestor = find_ancestor_vector(&n1, &n2, &n5); 

    // 5 3
    ancestor = find_ancestor_vector(&n1, &n5, &n3); 
     // 1 5
     ancestor = find_ancestor_vector(&n1, &n1, &n5); 
}


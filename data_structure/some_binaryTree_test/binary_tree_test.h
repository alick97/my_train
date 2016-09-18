#pragma once
#include <iostream>
#include <vector>
using namespace std;
/********************
 *    
 *    二叉树 相关面试题
 *
 *************************/


// 二叉树结点信息
struct Node
{
    Node* _left;
    Node* _right;
    Node* parent;
    int _value;

    Node (int n = 0)
        :_left(NULL)
        ,_right(NULL)
        ,parent(NULL)
        ,_value(n)
    {}
};


/////////////////////////////////////////////////////////////////
/* 1、求二叉树中两个结点的最低公共祖先结点                    */



/************************ 
 * 情况1 结点是三叉链的情况   （结点中有指向父亲的parent指针）
 * 解决方式 ： 找到两个结点后 快慢指针向上找 或vector记录路径
 * 这里用快慢指针 时间复杂度 (最坏情况 O(N))
 ************************/

Node* find_ancestor_1_1(const Node* root, const Node* p1, const Node* p2)
{
    if (p1 == NULL || p2 == NULL || root == NULL)
    {
        return NULL;
    }

    int p1_count = 0;
    int p2_count = 0;
    const Node* cur = p1;
    while (cur != NULL)
    {
        cur = cur->parent;
        ++p1_count;
    }
    
    cur = p2;
    while (cur != NULL)
    {
        cur = cur->parent;
        ++p2_count;
    }

    int diff = p1_count - p2_count;
    if (diff < 0)
    {
        diff = 0 - diff;
        swap(p1, p2);
    }

    while (diff-- != 0)
    {
        p1 = p1->parent;
    }

    while (p1 && p2 && p1 != p2)
    {
        p1 = p1->parent;
        p2 = p2->parent;
    }

    if (p1 == p2)
    {
        return (Node*)p1;
    }
   
    return NULL;
}
struct Nodeaddr
{
    Node* p1;
    Node* p2;
    Node* p3;
    Node* p4;
    Node* p5;
    Node* p6;
};

void creat_binarytree(Nodeaddr* pa)
{
    //          1
    //    2           5
    //  3    4     6
    Node* p1= new Node(1);
    Node* p2= new Node(2);
    Node* p3= new Node(3);
    Node* p4= new Node(4);
    Node* p5= new Node(5);
    Node* p6= new Node(6);

    p1->parent = NULL;
    p1->_left = p2;
    p2->parent = p1;

    p1->_right = p5;
    p5->parent = p1;

    p2->_left = p3;
    p3->parent = p2;


    p2->_right = p4;
    p4->parent = p2;

    p5->_left = p6;
    p6->parent = p5;

    pa->p1 = p1;
    pa->p2 = p2;
    pa->p3 = p3;
    pa->p4 = p4;
    pa->p5 = p5;
    pa->p6 = p6;
}


void test_find_ancestor_1_1()
{
    Nodeaddr pa;
    creat_binarytree(&pa);
    Node* p = find_ancestor_1_1(pa.p1, pa.p3, pa.p5);// p1

    cout<<p->_value<<endl;

    p = find_ancestor_1_1(pa.p1, pa.p2, pa.p4);// p2

    cout<<p->_value<<endl;

}

/************************ 
 * 情况2_1 普通的二叉树的情况   （结点中没有有指向父亲的parent指针【这里用不用parent指针表示 普通的二叉树】）
 * 解决方式1 ： 递归 利用find
 *              效率极低 （时间复杂度 O(N^2)）
 ************************/

bool find(const Node* root, const Node *pnode)
{
    if (root == NULL)
    {
        return false;
    }

    if (root == pnode)
    {
        return true; 
    }

    return find(root->_left, pnode) || find(root->_right, pnode);
}

Node* find_ancestor_2_1(const Node* root, const Node* p1, const Node* p2)
{
    
    if (p1 == root || p2 == root)
    {
        return (Node*)root;
    }

    bool p1_in_left = find(root->_left, p1);
    bool p2_in_right = find(root->_right, p2);

    // root不是p1 p2 但root的左右孩子 是p1 p2   那么root就是祖先结点
    if (p1_in_left && p2_in_right)
    {
        return (Node*)root;
    }
    // 在左子树
    bool p2_in_left = find(root->_left, p2);
    if (p2_in_left && p1_in_left)
    {
        return find_ancestor_2_1(root->_left , p1, p2);
    }
    //  在右子树
    bool p1_in_right = find(root->_right, p1);

    if (p1_in_right && p2_in_right)
    {
        return find_ancestor_2_1(root->_right, p1, p2);
    }

    return NULL;

}

void test_find_ancestor_2_1()
{
    Nodeaddr pa;
    creat_binarytree(&pa);
    Node* p = find_ancestor_2_1(pa.p1, pa.p3, pa.p5);// p1

    cout<<p->_value<<endl;

    p = find_ancestor_2_1(pa.p1, pa.p2, pa.p4);// p2

    cout<<p->_value<<endl;

}

/************************ 
 * 情况2_2 普通的二叉树的情况   （结点中没有有指向父亲的parent指针【这里用不用parent指针表示 普通的二叉树】）
 * 解决方式2 ： 递归 利用vector保存路径   用空间换时间
 *             （时间复杂度 O(N)）
 ************************/
bool get_path(const Node* root, const Node* p,vector<const Node*>& path)
{
    if (root == NULL)
    {
        return false;
    }

    path.push_back(root);
    if (root == p)
    {
        return true;
    }

    if (get_path(root->_left , p, path))
    {
        return true;
    }

    if (get_path(root->_right, p, path))
    {
        return true;
    }

    path.pop_back();
    return false;
}


Node* find_ancestor_2_2(const Node* root, const Node* p1, const Node* p2)
{
    vector<const Node*> path_p1;
    vector<const Node*> path_p2;
    if (get_path(root, p1, path_p1) && get_path(root, p2, path_p2))
    {
        int i = 0;
        for(; i < path_p1.size() && i < path_p2.size(); i++)
        {
            if (path_p1[i] != path_p2[i])
            {
                break;
            }
        }
        return (Node*)path_p1[i - 1];
    }

    return NULL;
}

void test_find_ancestor_2_2()
{
    Nodeaddr pa;
    creat_binarytree(&pa);
    Node* p = find_ancestor_2_2(pa.p1, pa.p3, pa.p5);// p1

    cout<<p->_value<<endl;

    p = find_ancestor_2_2(pa.p1, pa.p2, pa.p4);// p2

    cout<<p->_value<<endl;

}

/************************ 
 * 情况3 树是 二叉搜索树
 * 解决方式 ： 将情况2_1 的find替换    因为二叉搜索树 判断左右有没有 比较值就可以了 左小右大
 ************************/


Node* find_ancestor_3(const Node* root, const Node* p1, const Node* p2)
{
    if (root == p1 || root == p2)
    {
        return (Node*)root;
    }
    // left right
    if (p1->_value < root->_value && p2->_value > root->_value)
    {
        return (Node*)root;
    }
    if (p1->_value > root->_value && p2->_value < root->_value)
    {
        return (Node*)root;
    }

    // left left
    if (p1->_value < root->_value && p2->_value < root->_value)
    {
        return find_ancestor_3(root->_left, p1, p2);
    }

    // right right
    if (p1->_value > root->_value && p2->_value > root->_value)
    {
        return find_ancestor_3(root->_right, p1, p2);
    }

    return NULL;
}


void test_find_ancestor_3()
{

     //          4
    //    2          6
    //  1    3    5
    Node* p1= new Node(4);
    Node* p2= new Node(2);
    Node* p3= new Node(1);
    Node* p4= new Node(3);
    Node* p5= new Node(6);
    Node* p6= new Node(5);

    p1->parent = NULL;
    p1->_left = p2;
    p2->parent = p1;

    p1->_right = p5;
    p5->parent = p1;

    p2->_left = p3;
    p3->parent = p2;


    p2->_right = p4;
    p4->parent = p2;

    p5->_left = p6;
    p6->parent = p5;
    Nodeaddr pa;
    pa.p1 = p1;
    pa.p2 = p2;
    pa.p3 = p3;
    pa.p4 = p4;
    pa.p5 = p5;
    pa.p6 = p6;


    Node* p = find_ancestor_3(pa.p1, pa.p3, pa.p6);// p1 4

    cout<<p->_value<<endl;

    p = find_ancestor_3(pa.p1, pa.p2, pa.p3);// p2

    cout<<p->_value<<endl;

}






/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* 2、求二叉树中两个结点的最远距离(两个结点之间的最长边数 即 所有结点的两个子树高度和的最大值【通俗】)    */

/***********************
情景1           1
          2             3
      4             5        6
                                   7
     最远距离为  4   和 7  之间的距离 5
情景2
                  1            
             2
        3       4
    5             6
    最远距离为 5  和 6 之间的距离 4   而不是根节点的两边   
    所以 不能直接光计算root下面两个节点的所有情况  还要计算所有结点下面的两个结点之间的距离

************************/


/* 解法2_1 同判断二叉树是否平衡 以及计算高度差方式一样  时间复杂度 O(N^2)*/

int max_len = 0;

int get_height(const Node* root)
{
    if (root == NULL)
    {
        return 0;
    }

    int left_height = get_height(root->_left);
    int right_height = get_height(root->_right);
    
    return left_height > right_height ? left_height + 1: right_height + 1;
}


void get_max_len(const Node* root)
{
    if (root == NULL)
        return;

    int left_height = get_height(root->_left);
    int right_height = get_height(root->_right);

    if (left_height + right_height > max_len)
    {
        max_len = left_height + right_height;
    }

    get_max_len(root->_left);
    get_max_len(root->_right);
}


void test_get_max_len_1()
{
   //          1
    //    2           5
    //  3    4     6
     Nodeaddr pa;
    creat_binarytree(&pa);
    get_max_len(pa.p1);
    cout<<"len:"<<max_len<<endl;
}

/* 解法2_2 改进的方式 用后序遍历 返回时 返回值带出高度给上级 避免get_height的每次重复向下遍历  时间复杂度 O(N)*/

int max_len_2(const Node* root)
{
    if (root == NULL)
    {
        return 0;
    }

    int left_height = max_len_2(root->_left);
    int right_height = max_len_2(root->_right);

    if (left_height + right_height > max_len)
    {
        max_len = left_height + right_height;
    }

    return left_height > right_height ? left_height + 1: right_height + 1;

}

void test_get_max_len_2()
{
   //          1
    //    2           5
    //  3    4     6
     Nodeaddr pa;
    creat_binarytree(&pa);
    max_len_2(pa.p1);
    cout<<"len:"<<max_len<<endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* 3 判断一棵树是否是完全二叉树   （层序遍历的变种）   */

/* 完全二叉树 n层  1-（n-1） 层是满的 n层可以不满  但第n层空结点一定是从右向左连续的*/
/*  思路：这里利用flag 标志位 如果一个结点左边（右边）为空， 那么从左子（右子）节点到后面的所有子节点都为空， 不能再出现子节点*/
#include <queue>

bool flag = true; // 表示前面子节点都不为空

bool is_complete_binary_tree(const Node* root)
{
    queue<const Node*> q;
    if (root)
    {
        q.push(root);
    }

    while (!q.empty())
    {
        const Node* front = q.front();
        q.pop();

        if (front->_left)
        {
            if (flag == false) // 前面出现空  当前不为空
            {
                return false;
            }
            q.push(front->_left);
        }
        else
        {
            flag = false;
        }

        if (front->_right )
        {
            if (flag == false)
            {
                return false;
            }
            q.push(front->_right);
        }
        else
        {
            flag = false;
        }
    }

    return true;
}

void test_is_complete_binary_tree()
{
    //          1
    //    2           5
    //  3    4     6
     Nodeaddr pa;
    creat_binarytree(&pa);
    cout<<"isComplete_binaryTree:"<<is_complete_binary_tree(pa.p1)<<endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* 4 由前序和中序 构建二叉树 （假定结点数字不重复）   */
/* 思路： 前序找根节点 中序由找到的根节点的左为左树   右边为右树 递归构造   区间是一个结点就返回*/
#include <assert.h>
Node* rebulid(int*& prev, int* in1, int* in2) // prev 是前序序列指针（注意  这里用的是& 引用）  in1 in2 是中序序列区间的 起始和末尾[] 闭区间
{
    assert(prev && in1 && in2);
    Node* root = new Node(*prev);
    int* pos = in1;
    while (*pos != *prev)
    {
        ++pos;
    }

    // [)
    if (in1 < pos)
    {
        root->_left = rebulid(++prev, in1, pos - 1);
    }
    // (]
    if (pos < in2)
    {
        root->_right = rebulid(++prev, pos + 1, in2);
    }

    return root;
}


void test_rebulid()
{
    int prev_arr[] = {1,2,3,4,5,6};
    int inorder_arr[] = {3,2,4,1,6,5};
    /*

            1 2 3 4 5 6
            3 2 4 1 6 5

                               1
                         2          5
                    3        4    6
    */
   int* p = prev_arr;
    Node* root = rebulid(p, inorder_arr, inorder_arr + sizeof(inorder_arr)/sizeof(inorder_arr[0]) - 1);
    queue<Node*> q;
    q.push(root);
    while (!q.empty())
    {
        root = q.front();
        if (root->_left)
        {
            q.push(root->_left);
        }

        if (root->_right)
        {
            q.push(root->_right);
        }

        cout<<root->_value<<" ";
        q.pop();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* 5 将二叉搜索树转换为 一个排序的双向链表 要求不能创建新的结点， 只能调整树中的结点的指针的指向   */
/* 思路： 类似与中序线索化*/

void _to_list(Node* root, Node*& prev)
{
    if (root == NULL)
    {
        return;
    }

    _to_list(root->_left, prev);

    if (prev)
    {
        prev->_right = root; //  ->
    }
    root->_left = prev;      //   <-
    prev = root;
    _to_list(root->_right , prev);
}

Node* to_list(Node* root)
{
    if (root == NULL)
    {
        return NULL;
    }

    Node* prev  =NULL;
    _to_list(root, prev);
    Node* head = root;
    // 找头
   // 方法1 中序右子树最左就是
    // 方法2  直接就在 链中找
    while (head->_left)
    {
        head = head->_left;
    }

    return head;
}


void test_to_list()
{
    
     //          4
    //    2          6
    //  1    3    5
    Node* p1= new Node(4);
    Node* p2= new Node(2);
    Node* p3= new Node(1);
    Node* p4= new Node(3);
    Node* p5= new Node(6);
    Node* p6= new Node(5);

    p1->parent = NULL;
    p1->_left = p2;
    p2->parent = p1;

    p1->_right = p5;
    p5->parent = p1;

    p2->_left = p3;
    p3->parent = p2;


    p2->_right = p4;
    p4->parent = p2;

    p5->_left = p6;
    p6->parent = p5;
    Nodeaddr pa;
    pa.p1 = p1;
    pa.p2 = p2;
    pa.p3 = p3;
    pa.p4 = p4;
    pa.p5 = p5;
    pa.p6 = p6;


    Node* root = to_list(pa.p1);
    while (root)
    {
        cout<<root->_value<<" ";
        root = root->_right;
    }
    cout<<endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* 6 求二叉树的镜像  */
void get_mirror(Node* root)
{
    if (root == NULL)
    {
        return;
    }

    swap(root->_left , root->_right);
    get_mirror(root->_left);
    get_mirror(root->_right);
}


void test_get_mirror()
{
     Nodeaddr pa;
    creat_binarytree(&pa);
    get_mirror(pa.p1);

    Node* root = pa.p1;
    queue<Node*> q;
    q.push(root);
    while (!q.empty())
    {
        root = q.front();
        if (root->_left)
        {
            q.push(root->_left);
        }

        if (root->_right)
        {
            q.push(root->_right);
        }

        cout<<root->_value<<" ";
        q.pop();
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* 7 判断二叉树是否是 平衡二叉树  */

//  类似于 求二叉树两个节点的最远距离 这里直接用后续  O(N)的时间复杂度
bool b_is_balance = true;
int _is_balance(Node* root)
{
    if (root == NULL)
    {
        return 0;
    }

    int left_height = _is_balance(root->_left);
    int right_height = _is_balance(root->_right);

    if (abs(left_height - right_height) > 1)
    {
        b_is_balance = false;
    }

    return left_height > right_height ? left_height + 1 : right_height + 1;
}

bool is_balance(Node* root)
{
    b_is_balance = true;
    _is_balance(root);
    if (b_is_balance)
    {
        return true;
    }
    else
    {
        return false;
    }
}


void test_is_balance()
{
     Nodeaddr pa;
    creat_binarytree(&pa);
    get_mirror(pa.p1);

    cout<<"is_balance:"<<is_balance(pa.p1)<<endl;
}

/*
   8
    
    给出二叉树接口为

        class node
        {
            node *get_left();
            node *get_right();
            int get_data();
        }
        找出值为val的最浅节点所在层数。
        1
        int find(node *root, int val).


*/

//层序遍历
 /* http://www.nowcoder.com/questionTerminal/578d5c28037c472bbcbc53057b80b6a7 */
int find(TreeNode root, int val){
        int deep = 0;
        if(root == null)
            return -1;
        Queue<TreeNode> queue = new LinkedList<TreeNode>();
        queue.add(root);
        boolean found = false;
        while(!queue.isEmpty()){
            Queue<TreeNode> cur = new LinkedList<TreeNode>();
            while(!queue.isEmpty()){
                TreeNode temp = queue.poll();
                if(temp.val == val){
                    found = true;
                    break;
                }
                if(temp.left != null)
                    cur.add(temp.left);
                if(temp.right != null)
                    cur.add(temp.right);
            }//while
            deep++;
            while(!cur.isEmpty()){
                queue.add(cur.poll());
            }//while
        }//while
        if(!found)
            return -1;
        return deep;
    }
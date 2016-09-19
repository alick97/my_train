#define _CRT_SECURE_NO_WARNINGS 1


//  renren
#include <iostream>
using namespace std;

// 判断一个字符串是不是回文
bool is_plalindrome(char* str, int n)
{
    if (str == NULL || n <= 0)
    {
        return false;
    }

    char* left = str + (n>>1) - 1;
    char* right = (n%2 == 0 ? left + 1 : left + 2); // 分奇偶
    bool is = true;
    while (left >= str)
    {
        if (*left != *right)
        {
            is = false;
            break;
        }
        left--;
        right++;
    }

    return is;
}

void test()
{
    char *s1_1 = "ababa";
    char *s1_2 = "aaaba";
    char *s2_1 = "abba";
    char *s2_2 = "abea";

    cout<<is_plalindrome(s1_1, 5)<<endl;
    cout<<is_plalindrome(s1_2, 5)<<endl;
    cout<<is_plalindrome(s2_1, 4)<<endl;
    cout<<is_plalindrome(s2_2, 4)<<endl;
}




int main()
{
    test();
    return 0;
}





/////-----------------------------------




    
#include <iostream>
using namespace std;


/*

  不用加减 号 作加运算 （利用移位、按位与和 异或）
  按位与之后 左移一位 表示 进位
  异或表示 除了进位的相应位的加
*/


int get_sum(int a,int b)
{
    int sum;
    int jinwei;
    do
    {
       sum = a^b;
       jinwei = (a&b)<<1;
       a = sum;
       b = jinwei;
    }while (jinwei != 0); // error while (jinwei > 0)

    return sum;
}


int main()
{
    cout<<get_sum(1,2)<<endl;
    cout<<get_sum(-1,-2)<<endl;

    return 0;
}




/*
          人人 2016 C++
有一排台阶，每个台阶上有一个非负整数，代表在该台阶上时能最多向前跳几个台阶。从第0个台阶开始跳，实现一个函数，判断是否能到达最后一个台阶。
例如： 4 2 2 1 0 2 返回 false
            2 1 3 1 1 0 返回 true
1
2
3
bool jump(int array[], int size)
{                 
}


*/

//    从后向前 用到标志位 
#include <iostream>
using namespace std;
#include <vector>


bool jump(int array[], int size)
{       bool can = false;           
    vector<bool> is(size, false);
    is[size - 1] = true;
    for (int i = size - 2; i >= 0; i--)
    {
        for (int j =1; j <= array[i]; j++)
        {
            if (i + j <= size - 1)
            {
                if (is[i + j] == true)
                {
                    is[i] = true;
                    break;
                }
            }

        }

        if (i == 0 && is[i] == true)
        {
            can = true;
        }

    }

    return can;
}

void test_jump()
{
    int arr1[6] = {4 ,2, 2 ,1, 0, 2};
    int arr2[6] = {2 ,1 ,3 ,1 ,1 ,0};
    cout<<jump(arr1,6)<<endl;
    cout<<jump(arr2,6)<<endl;
}



int main()
{
    test_jump();
    return 0;
}


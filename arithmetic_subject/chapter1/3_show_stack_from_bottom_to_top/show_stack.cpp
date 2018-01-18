#include <iostream>
#include <stack>

using namespace std;

int get_and_remove_last_element(stack<int>& s)
{
    int result = s.top();
    s.pop();
    if (s.empty())
    {
        return result;
    }
    else
    {
        int last = get_and_remove_last_element(s);
        s.push(result);
        return last;
    }
}

void reverse_stack(stack<int>& s)
{
    if (s.empty())
    {
        return;
    }
    int i = get_and_remove_last_element(s);
    reverse_stack(s);
    s.push(i);
}

int main()
{
    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    reverse_stack(s);
    // 1 2 3
    while (!s.empty())
    {
        cout<<s.top()<<endl;
        s.pop();
    }
    return 0;
}
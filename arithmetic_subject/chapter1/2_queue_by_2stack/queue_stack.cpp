#include <iostream>
#include <stack>
using namespace std;

class TwoStackQueue
{
public:
    void add(int value)
    {
        this->push_stack.push(value);
    }

    int poll()
    {
        if (pop_stack.empty() && push_stack.empty())
        {
            throw "queue is empty";
        }
        else if (pop_stack.empty())
        {
            while (!push_stack.empty())
            {
                int top = push_stack.top();
                pop_stack.push(top);
                push_stack.pop();
            }
        }
        int result = pop_stack.top();
        pop_stack.pop();
        return result;
    }
private:
    stack<int> push_stack;
    stack<int> pop_stack;
};

int main()
{
    TwoStackQueue q;
    q.add(1);
    q.add(2);
    q.add(3);
    cout << q.poll() << endl;
    cout << q.poll() << endl;
    cout << q.poll() << endl;
    return 0;
}
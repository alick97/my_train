#include <iostream>
#include <vector>
#include <exception>
using namespace std;

class MinStask
{
public:
    void push(int new_num)
    {
        if (this->stack_min.empty())
        {
            this->stack_min.push_back(new_num);
        } else if (new_num <= this->get_min())
        {
            this->stack_min.push_back(new_num);
        }
        this->stack_data.push_back(new_num);
    }

    int pop()
    {
        if (this->stack_data.empty())
        {
            throw "stack_data is empty";
        }

        int value = this->stack_data.back();
        this->stack_data.pop_back();
        if (value == this->get_min())
        {
            this->stack_min.pop_back();
        }
        return value;
    }

    int get_min()
    {
        if (this->stack_min.empty())
        {
            throw "stack min is empty";
        }
        return this->stack_min.back();
    }

private:
    vector<int> stack_data;
    vector<int> stack_min;    
};


int main()
{
    MinStask min_stack;
    try
    {
        // 3 4 5 1 2 1
        min_stack.push(3); // min 3
        min_stack.push(4); // min 3
        min_stack.push(5); // min 3
        min_stack.push(1); // min 1
        min_stack.push(2); // min 1
        min_stack.push(1); // min 1
        cout<<min_stack.get_min()<<":min should be 1"<<endl;
        min_stack.pop();
        cout<<min_stack.get_min()<<":min should be 1"<<endl;
        min_stack.pop();
        cout<<min_stack.get_min()<<":min should be 1"<<endl;
        min_stack.pop();
        cout<<min_stack.get_min()<<":min should be 3"<<endl;
        min_stack.pop();
        cout<<min_stack.get_min()<<":min should be 3"<<endl;
        min_stack.pop();
        cout<<min_stack.get_min()<<":min should be 3"<<endl;        
    } catch(const char * e)
    {
        cout<<e<<endl;
    }

    return 0;
}
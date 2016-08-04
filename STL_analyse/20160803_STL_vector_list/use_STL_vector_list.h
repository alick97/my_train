#pragma once
#include <iostream>
using namespace std;
#include <vector>
#include <list>


/***************
  * STL 中的 vector 和 list 的使用练习
  *

***********************/



void test_vector()
{
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    int i = 0;
    for (i = 0; i < v.size(); i++)
    {
        cout<<v[i]<<" ";
    }
    cout<<endl;


    vector<int>::iterator iter ;
    iter = v.begin();
    while (iter != v.end())
    {
        cout<<(*iter)<<" ";
        iter++;
    }
    cout<<endl;

    iter = v.end();
    //cout<<(*iter)<<endl; // err    v.end()  是最后一个的下一个 是无效的*引用 会出错
    
    iter--;
    cout<<(*iter)<<endl; 
 
    vector<int>::reverse_iterator reverse_iter  = v.rbegin();
    
    while (reverse_iter  < v.rend())
    {
        cout<<*(reverse_iter ++)<<" ";
    }
    cout<<endl;



    vector<int> v2 = v;
    cout<<"v2.size::"<<v2.size()<<endl;
    cout<<"v2.capacity"<<v2.capacity()<<endl;
    cout<<"-----------------------"<<endl;
    v2.reserve(10);
    cout<<"v2.size::"<<v2.size()<<endl;
    cout<<"v2.capacity"<<v2.capacity()<<endl;
    cout<<"-----------------------"<<endl;
    v2.resize(10);
    cout<<"v2.size::"<<v2.size()<<endl;
    cout<<"v2.capacity"<<v2.capacity()<<endl;
    cout<<"-----------------------"<<endl;

    int sum = 0;
    while (!v2.empty())
    {
        sum += v2.back();
            v2.pop_back();
    }
    cout<<"sum:"<<sum<<endl;
    
    v2 = v;
    cout<<v2.at(0)<<endl;

    cout<<"front"<<v2.front()<<endl;
    cout<<"back"<<v2.back()<<endl;


    vector<int> v4;
    vector<int> v5;
    vector<int> v6;

    v4.assign(5,99);
    vector<int>::iterator it;
    v4[0] = 98;
    it = v4.begin() + 1;
    v5.assign(it, v4.end());
    int a[] = {1,2,3};

    v6.assign(a, a + 3);
    v6.insert(v6.end(), 4);
    v6.insert(v6.begin(),2,-2);
    v6.insert(v6.begin(), v4.begin(), v4.begin() + 3);

    v6.clear();
    v6.assign(a, a+3);
    v6.erase(v6.begin());
    v6.erase(v6.begin(),v6.end());

    v4.swap(v6);
}


void test_list()
{
    list<int> mylist1;
      for (int i=1; i<=4; i++)
     mylist1.push_back(i);      // mylist1: 1 2 3 4

      list<int> mylist2;
      mylist2.splice(mylist2.begin(), mylist1, mylist1.begin(), mylist1.end());

}

#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <assert.h>
using namespace std;
//#include "use_STL_vector_list.h"
#include "MyList.h"
#include "MyVectory.h"
#include "MyIterator.h"

//template<class T>
//struct S
//{T _value;};
//template <class T>
//struct A
//{S<T> s;
//    const S<T>* operator->() const
//    {
//        return &s;
//    }
//};

//struct A
//{
//    char* pstr;
//    char*const& getptr() const
//    {
//        return pstr;
//    }
//};
//
//void test()
//{
//    A a;
//    char* pstr = a.getptr();
//    pstr = "sadasd";
//}

void test()
{
    List<int> l1;
    l1.PushBack(1);
    l1.PushBack(2);
    l1.PushBack(3);
    l1.PushBack(4);
    cout<<"List Distance"<<Distance(l1.Begin(), l1.End())<<endl;


    Vector<int> v1;
    v1.PushBack(1);
    v1.PushBack(2);
    v1.PushBack(3);
    v1.PushBack(4);
    cout<<"Vector Distance"<<Distance(v1.Begin(), v1.End())<<endl;
    
}

int main()
{
    //test_vector();
    //test_list();
    //test_iterator();
    //test_list();

    //TestVector();
    test();
    return 0;
}

#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <assert.h>
using namespace std;
//#include "use_STL_vector_list.h"
#include "MyList.h"
#include "MyIterator.h"
#include "MyVectory.h"
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

void test_Advance()
{
    List<int> l;
    l.PushBack(1);
    l.PushBack(2);
    l.PushBack(3);
    l.PushBack(4);

    List<int>::Iterator listIt = l.Begin();

    Advance(listIt, 3);
    cout<<"list advance 3 step is"<<*listIt<<endl;


    Vector<int> v1;
    v1.PushBack(1);
    v1.PushBack(2);
    v1.PushBack(3);
    v1.PushBack(4);

    Vector<int>::Iterator vectorIt = v1.Begin();
    Advance(vectorIt, 3);
    cout<<"vector advance 3 step is "<<*vectorIt<<endl;
}

void test_Distance()
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
   // test_Advance();
    test_list_reverseIterator();
    return 0;
}

#include <iostream>
using namespace std;



//////////////////////////////////////////////////////////////
// 实现一个只在【堆】上生成的对象
//////////////////////////////////////////////////////////////


class B
{
public:
    static B* GetObj()
    {
        return new B;
    }
    ~B()
    {
        cout<<"~B()"<<endl;
    }

protected:
    B(){};
    
    B(const B&); // ----------------------拷贝构造也要防止 如 不防止拷贝构造 B* pb = B::GetObj(); B b2(*pb);是成功的  而 【b2是在栈上的】
};

void testB()
{
   // error  B b;
   // error B* pb = new B;
   //error B b(B());
    B* pb = B::GetObj();
    //B b2(*pb);  一定要B(const B&);为protected
 
    delete pb;
}









///////////////////////////////////////////////////////////////
// 实现一个只在【栈】上生成的对象
///////////////////////////////////////////////////////////////


// 方案一 A() A（constA&）;声明为protected 返回 &(A())
// 有缺陷  不能防止别人声明全局的东西 全局的实现的方式不同
// 如 A* pa = new AA;  pa是全局的 则是成功的（不过我测试 vs2012是不行的 全局的也是不行的）
class A
{
public:
    static A* GetA()
    {
        return &(A());
    }

    ~A()
    {
        cout<<"~A()"<<endl;
    }
    int a;
protected:
    A(){};    // 这里不能光声明 如 A();    不然报错 找不到链接的外部符号
    A(const A& a);// 简单粗暴 ，不允许拷贝 若不声明protected  则A* paa = new A(*pa);是可以执行的 生成的是堆上的
    
};
 // vs2012  error  A* pa = new A; 可能vs2013可以

void test1()
{

   //error  A a;
   // error  A* pa = new A;
    A* pa = A::GetA();
    pa->a = 2;
    cout<<pa->a<<endl;

   // error  A* paa = new A(*pa);
}


// 方案二 【 】
// new 的实现是先调用 operator new(size_t) 或 operator new[](size_t) 然后调用相应的构造函数
// operator new 有两种 一种是局部的  类中的静态函数   一种是全局的  如果声明 的类是全局的则调用的是全局的operator new
// 这里就是阻止new   所以将所有的operator new声明为protected的
class C
{
public:
    void CSay()
    {
        cout<<"I am c"<<endl;
    }
    int val;
    C()
    {
        cout<<"C()"<<endl;
    }

protected:
    void* operator new(size_t);
    void operator delete(void*);

    void* operator new[](size_t);
    void operator delete[](void*);
};

// error C* pc = new C();

void testC()
{
   //error  C* pc = new C;

   //error C* pc =(C*)malloc(sizeof(C));
  //  new (pc) C;

    /* ok   阻止不了这种 要阻止就要像方案一一样将构造函数控制起来
    C* pc = (C*)malloc(sizeof(C));
    pc->CSay();
    pc->val = 1;
    cout<<pc->val<<endl;
    
    C* pc = (C*)malloc(sizeof(C));
    pc->C::C();
    */
    C c;

}

// 方案3  前两种方案的结合
class E
{
public:
    static E* GetE()
    {
        return &(E());
    }  
protected:
    E(){};
    E(const E& objE){};
protected:
    void* operator new(size_t);
    void operator delete(void*);

    void* operator new[](size_t);
    void operator delete[](void*);
};
void testE()
{
    //error E* pe = new E();
    E* pe = E::GetE();
}


// 验证 调用的是全局的operator  还是 类中局部的
// 重载全局的operator new
// 参考url :      http://blog.csdn.net/qq_29227939/article/details/51638241
void * operator new(size_t size)
{
cout << "全局内存分配"<<endl;
return malloc(size);
}

int *pa = new int; // 调用全局的operator new

class FF
{};

FF* pff = new FF; // 调用的是全局的operator new

class GG
{
public:
    void * operator new(size_t size)
{
cout << "局部内存分配"<<endl;
return malloc(size);
}

};

GG* pgg1 = new GG;  // 调用局部    局部实现调用的是局部的 如果局部没实现调用的是全局的
void testgg()
{
    GG* pgg2 = new GG; // 调用的是局部的   如果局部没实现调用的是全局的 和在testgg中无关系
}



int main()
{
   // test1();
    testB();
   // testC();
    //testE();
   // testgg();
    return 0;
}



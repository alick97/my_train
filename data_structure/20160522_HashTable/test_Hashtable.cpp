#define _CRT_SECURE_NO_WARNINGS 1
//#include"HashTable.hpp
#include"HashTableBucket.hpp"
void test_HashTable()
{
    // test_namespace_First();
    // test_namespace_Second();
}

void test_HashTableBucket1()
{
    HashTableBucket<int,int> ht;
    ht.Insert(1,1);
    ht.Insert(2,2);
    ht.Insert(3,3);
    ht.Insert(4,4);
    ht.Insert(53 + 1,53);
    ht.PrintTables();

    HashTableBucket<int,int>ht2(ht);
    ht2.PrintTables();

    HashTableNode<int,int>* pht2 = ht2.Find(4);
    
    bool brm = ht2.Remove(4);
    pht2 = ht2.Find(4);
    brm = ht2.Remove(5); // false
  
    ht = ht2;
    ht.PrintTables();

     HashTableBucket<int,int> ht3;
    //扩容测试 _CheckExpand() //
    for (size_t i = 0; i < 53; i++)
    {
        ht3.Insert(i,1);
    }
    // 增容
    ht3.Insert(53,4);
    std::cout<<"-------------------"<<std::endl;
    ht3.PrintTables();

   

}

void test_HashTableBucket2()
{
     // 特殊类型测试
    HashTableBucket<std::string,std::string> ht;
    ht.Insert("one","一");
    ht.Insert("two","二");
    ht.Insert("three","三");
    ht.Insert("four","四");
    ht.PrintTables();

    HashTableBucket<std::string,std::string>ht2(ht);
    ht2.PrintTables();

    HashTableNode<std::string,std::string>* pht2 = ht2.Find("two");
    
    bool brm = ht2.Remove("two");
    pht2 = ht2.Find("two");
    brm = ht2.Remove("five"); // false
  
    ht = ht2;
    ht.PrintTables();

     HashTableBucket<std::string,std::string> ht3;
    //扩容测试 _CheckExpand() //
    for (size_t i = 0; i < 53; i++)
    {
        ht3.Insert(std::string().append(i,'0'),"ooooo");
    }
    // 增容
    ht3.Insert("53","4");
    std::cout<<"-------------------"<<std::endl;
    ht3.PrintTables();
}



int main()
{
   test_HashTableBucket2();
    return 0;
}

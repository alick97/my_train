#pragma once
#include <string>
#include <iostream>
using namespace std;
namespace First
{
    enum State
    {
        EMPTY,
        DELETE,
        EXIST,
    };

    template<class K>
    struct __HashFunc // 产生键值(如把string的转化成数字) 默认的返回哈希键值key的 仿函数
    {
        size_t operator()(const K& key)
        {
            return key;
        }
    };

    template<class K>
    class HashTable
    {
        // Key形式的线性探测
    public:
        HashTable(size_t capacity = 10)
            :_tables(new K[capacity])
            ,_size(0)
            ,_capacity(capacity)
            ,_states(new State[capacity])
        {
            // memset 有问题 是以字节为单位初始化的 但第二个参数值为int
            // 会出问题 本来初始化为0x00000001 结果初始化为0x01010101
            //memset(_states, EMPTY, sizeof(State) * capacity);
            for (size_t i = 0; i < capacity; i++)
            {
                _states[i] = EMPTY;
            }
        }

        HashTable(const HashTable<K>& ht)
            :_tables(new K[ht._capacity])
            ,_size(0)
            ,_capacity(ht._capacity)
            ,_states(new State[ht._capacity])
        {
            for (size_t i = 0; i < ht._capacity; i++)
            {
                if (EXIST == ht._states[i])
                {
                    Insert(ht._tables[i]);
                }
            }
        }

       
        
        HashTable& operator=(const HashTable<K>& ht)
        {
            if (ht._tables != _tables && ht._states != _states)
            {
                HashTable<K> tmp(ht);
                Swap(tmp);
            }

            return *this;
        }

        ~HashTable()
        {
            if (NULL != _tables)
            {
                delete[] _tables;
            }

            if (NULL != _states)
            {
                delete[] _states;
            }
        }

        bool Insert(const K& key)
        {
            // 静态哈希表 不扩容的
            /*if (_size == _capacity)
            {
                cout<<"HashTable is full"<<endl;
                return false;
            }*/

            _CheckCapacity();  

            size_t index = _HashFunc(key);

            while (EXIST == _states[index])
            {
                index++;
                if (_capacity == index)
                {
                    index=0;
                }
            }

            _tables[index] = key;
            _states[index] = EXIST;
            _size++;
            return true;
        }

        int Find(const K& key)
        {
            size_t index = _HashFunc(key);
            size_t start = index;
            // 存在 或者 被删除 两种状态
            while (EMPTY != _states[index])
            {
                if (_tables[index] == key)
                {
                    if (_states[index] == EXIST)
                    {
                        return index;
                    }
                    else // 被删除 DELETE
                    {
                        return -1;
                    }
                }

                index++;

                if (index == _capacity)
                {
                    index = 0;
                }
                // 找一圈 没找到就停止 防止死循环
                if (index == start)
                {
                    return -1;
                }
            }

            return -1;
        }

        bool Remove(const K& key)
        {
            int index = Find(key);
            if (-1 != index)
            {
                _states[index] = DELETE;
                --_size;
                return true;
            }

            return false;
        }

        
        // 线性探测计算出存放位置（假设不哈希冲突）
        size_t _HashFunc(const K& key)
        {
            __HashFunc<K> hf;
            return hf(key) % _capacity; //  仿函数hf() 
            // 匿名对象
            // return __HashFunc<K>()(key) % _capacity;
        }

        void Print()
        {
            for (size_t i = 0; i < _capacity; i++)
            {
                if (EXIST == _states[i])
                {
                    cout<< i << "EXIST:" << _tables[i] << endl;
                }
                else if (DELETE == _states[i])
                {
                    cout<< i << "DELETE:" << _tables[i] << endl;
                }
                else
                {
                    cout << i << "EMPTY" << _tables[i] <<endl;
                }
            }
        }

        void Swap(HashTable<K>& ht)
        {
            swap(_size, ht._size);
            swap(_states, ht._states);
            swap(_tables, ht._tables);
            swap(_capacity, ht._capacity);
        }

    protected:
        void _CheckCapacity() // 扩容
        {
            // 动态的 可扩容的
            // 高效哈希表的载荷因子大概在0.7-0.8较好
            if (10 * _size / _capacity >= 7)  // _size/_capacity为0 因为都是整形 所以乘10
                // 保证载荷因子在0.7之内
            {
                HashTable<K> tmp(2 * _capacity);
                for (size_t i = 0; i < _capacity; i++)
                {
                    if (EXIST == _states[i])
                    {
                         tmp.Insert(_tables[i]);
                    }
                }
                Swap(tmp);
            }
        }

    protected:
        K* _tables;     //  哈希表
        State* _states; //  状态表
        size_t _size;
        size_t _capacity;
    };

}

void test_namespace_First()
{
    using namespace First;
    HashTable<int> ht;
    ht.Insert(89);
    ht.Insert(18);
    ht.Insert(49);
    ht.Insert(58);
    ht.Insert(9);
    ht.Print();

    int ret = ht.Find(49);
    cout<<ret<<endl;

    ht.Remove(89);
    ht.Print();  
    
    ht.Remove(18);
    ht.Print();
    cout<<"---------------------------"<<endl;

    HashTable<int> ht2 = ht;
    ht2.Print();
    cout<<"---------------------------"<<endl;
    ht = ht2;
    ht.Print();
    cout<<"---------------------------"<<endl;

}

//============================================================================




namespace Second
{
    enum State
    {
        EMPTY,
        DELETE,
        EXIST,
    };
    //  Key/Value
    template<class K, class V>
    struct HashTableNode
    {
        K _key;
        V _value;
    };

    template<class K>
    struct __HashFunc // 默认的返回哈希键值key的 仿函数
    {
        size_t operator()(const K& key)
        {
            return key;
        }
    };

    // 特化string的__HashFunc 仿函数
    template<>
    struct __HashFunc<string>
    {
        //下面这种缺点 产生重复key 如“abcd” 与 “bcda”
        size_t operator()(const string& str)
        {
             size_t key = 0;
            for (size_t i = 0; i < str.size(); i++)
            {
                key += str[i];
            }

            return key;
        }
    };

    // 实现哈希表的Key/Value形式的二次探测
    template<class K, class V, class HashFunc = __HashFunc<K>>
    class HashTable
    {
        typedef HashTableNode<K,V> Node;
     public:
        HashTable(size_t capacity = 10)
            :_tables(new Node[capacity])
            ,_size(0)
            ,_capacity(capacity)
            ,_states(new State[capacity])
        {
            // memset 有问题 是以字节为单位初始化的 但第二个参数值为int
            // 会出问题 本来初始化为0x00000001 结果初始化为0x01010101
            //memset(_states, EMPTY, sizeof(State) * capacity);
            for (size_t i = 0; i < capacity; i++)
            {
                _states[i] = EMPTY;
            }
        }

        HashTable(const HashTable<K, V, HashFunc>& ht)
            :_tables(new Node[ht._capacity])
            ,_size(0)
            ,_capacity(ht._capacity)
            ,_states(new State[ht._capacity])
        {
            for (size_t i = 0; i < ht._capacity; i++)
            {
                if (EXIST == ht._states[i])
                {
                    Insert(ht._tables[i]._key, ht._tables[i]._value);
                }
            }
        }

       
        
        HashTable& operator=(const HashTable<K, V, HashFunc>& ht)
        {
            if (ht._tables != _tables && ht._states != _states)
            {
                HashTable<K, V, HashFunc> tmp(ht);
                Swap(tmp);
            }

            return *this;
        }

        ~HashTable()
        {
            if (NULL != _tables)
            {
                delete[] _tables;
            }

            if (NULL != _states)
            {
                delete[] _states;
            }
        }

        bool Insert(const K& key, const V& value)
        {
            // 静态哈希表 不扩容的
            /*if (_size == _capacity)
            {
                cout<<"HashTable is full"<<endl;
                return false;
            }*/

            _CheckCapacity();  

            //size_t hashKeyStart = _HashFunc(key);
            //size_t add_more = 1;
            //size_t index = hashKeyStart;
            //// ****************************************
            //// 二次探测    Hash(key) + 0 Hash(key) + 1^2 Hash(key) + 2^2

            //while (EXIST == _states[index])
            //{
            //    index = hashKeyStart + add_more * add_more;
            //    add_more++;
            //    if (index >= _capacity)
            //    {
            //          index = index % _capacity;
            //    }  
            //}

             // ****************************************

            // 改进 用GetNextIndex 解决哈希冲突
            size_t index = _HashFunc(key);
            // 二次探测   
            size_t i = 1;
            while (EXIST == _states[index])
            {
                index = _GetNextIndex(index, i++);
                if (index >= _capacity)
                {
                      index = index % _capacity;
                }  
            }
            _tables[index]._key = key;
            _tables[index]._value = value;
            _states[index] = EXIST;
            _size++;
            return true;
        }

        int Find(const K& key)
        {
            size_t index = _HashFunc(key);
            size_t start = index;
            size_t i = 1;
            // 存在 或者 被删除 两种状态
            while (EMPTY != _states[index])
            {
                if (_tables[index]._key == key)
                {
                    if (_states[index] == EXIST)
                    {
                        return index;
                    }
                    else // 被删除 DELETE
                    {
                        return -1;
                    }
                }

                index = _GetNextIndex(index, i++);

                if (index >= _capacity)
                {
                    index = index % _capacity;
                }

                // 因为有填充因子 不为100%  不会出现全满且key！=_key 导致死循环的情况
            }

            return -1;
        }

        bool Remove(const K& key)
        {
            int index = Find(key);
            if (-1 != index)
            {
                _states[index] = DELETE;
                --_size;
                return true;
            }

            return false;
        }

        
       // 二次探测计算出存放位置
        size_t _HashFunc(const K& key)
        {
           // __HashFunc<K> hf;
            HashFunc hf;
            return hf(key) % _capacity; //  仿函数hf() 
            // 匿名对象
            // return __HashFunc<K>()(key) % _capacity;
        }

        //   哈希冲突时 得到下一个index的可以利用上一个index的值 这样能提高效率 比如 string的index计算就比较费时
          size_t _GetNextIndex(size_t prev, size_t i) 
         {
             //二次探测
             // 公式推导 Hash(i) = Hash(0) + i^2
             //          Hash(i-1) = Hash(0) + (i -1)^2=Hash(0)+i^2-2i+1
             //  上面两式相减 得 Hash(i) = Hash(i-1) + +2*i - 1;
             return prev + 2*i - 1;
         }


        void Print()
        {
            for (size_t i = 0; i < _capacity; i++)
            {
                if (EXIST == _states[i])
                {
                    cout<< i << "EXIST:" <<_tables[i]._key << "-------" <<_tables[i]._value <<endl;
                }
                else if (DELETE == _states[i])
                {
                    cout<< i << "DELETE:" << _tables[i]._key << "-------" << _tables[i]._value <<endl;
                }
                else
                {
                  cout << i << "EMPTY:" << _tables[i]._key << "-------" << _tables[i]._value <<endl;
                }
            }
        }

        void Swap(HashTable<K, V, HashFunc>& ht)
        {
            swap(_size, ht._size);
            swap(_states, ht._states);
            swap(_tables, ht._tables);
            swap(_capacity, ht._capacity);
        }

    protected:
         void _CheckCapacity() // 扩容
        {
            // 动态的 可扩容的
            // 高效哈希表的载荷因子大概在0.7-0.8较好
            if (10 * _size / _capacity >= 7)  // _size/_capacity为0 因为都是整形 所以乘10
                // 保证载荷因子在0.7之内
            {
                HashTable<K, V, HashFunc> tmp(2 * _capacity);
                for (size_t i = 0; i < _capacity; i++)
                {
                    if (EXIST == _states[i])
                    {
                         tmp.Insert(_tables[i]._key, _tables[i]._value);
                    }
                }
                Swap(tmp);
            }
        }

    protected:
        Node* _tables;     //  哈希表
        State* _states; //  状态表
        size_t _size;
        size_t _capacity;
    };

}




void test_namespace_Second()
{
    using namespace Second;
    HashTable<string, string> ht;
    ht.Insert("one","一");
    ht.Insert("two","二");
    ht.Insert("three","三");
    ht.Insert("four","四");
    ht.Insert("five","五");
    ht.Print();

     int ret = ht.Find("two");
    cout<<ret<<endl;

    ret = ht.Find("hfjks");
    cout<<ret<<endl;

    ht.Remove("one");
    ht.Print();  
    
    ht.Remove("two");
    ht.Print();
    cout<<"---------------------------"<<endl;

    HashTable<string, string> ht2 = ht;
    ht2.Print();
    cout<<"---------------------------"<<endl;
    ht = ht2;
    ht.Print();
    cout<<"---------------------------"<<endl;

}


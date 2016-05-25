#pragma once
#include<iostream>
#include<vector>
#include<string>
/*********
 * 哈希桶 （处理哈希冲突的开链法）
 *
 ****************/
template<class K, class V>
struct HashTableNode
{
    K _key;
    V _value;
    HashTableNode* _next;
    HashTableNode()
        :_next(NULL)
    {}

    HashTableNode(const K& key, const V& value)
        :_key(key)
        ,_value(value)
        ,_next(NULL)
    {}
};

template<class K>
struct DefaultHashFunc
{
    size_t operator()(const K& key)
    {
        return key ;
    }

};

template<>
struct DefaultHashFunc<std::string>
{
    size_t operator()(const std::string& str)
    {
        size_t key = 0;
        for (size_t i = 0; i < str.size(); i++)
        {
            key += str[i];
        }
        return key;
    }

};


template<class K, class V, class HashFunc = DefaultHashFunc<K>>
class HashTableBucket
{
    typedef HashTableNode<K, V> Node;
public:
    HashTableBucket()
        :_size(0)
    {}

    HashTableBucket(const HashTableBucket<K, V, HashFunc>& ht)
        :_size(ht._size)
    {
        _tables.resize(ht._tables.size());

        for (size_t i = 0; i < ht._tables.size(); i++)
        {
            Node* cur = ht._tables[i];

            while (NULL != cur)
            {
                Node* newNode = new Node(cur->_key, cur->_value);
                newNode->_next = _tables[i];
                _tables[i] = newNode;
                cur = cur->_next;
            }
        }
    }

    HashTableBucket& operator=(const HashTableBucket& ht)
    {
        if (this != &ht)
        {
            HashTableBucket tmp(ht);
            _tables.swap(tmp._tables);
            std::swap(_size, tmp._size);
        }
        return *this;
    }


    ~HashTableBucket()
    {
        for (size_t index = 0 ; index < _tables.size(); index++)
        {
            Node* cur = _tables[index];

            while (NULL != cur)
            {
                Node* del = cur;
                cur = cur->_next;
                delete del;
            }
        }
        _size = 0;
    }


    bool Insert(const K& key, const V& value)
    {
        // 检测容量
        _CheckExpand();

        size_t index = _HashFunc(key, _tables.size());
        Node* cur = _tables[index];
        // 防止冗余
        while (NULL != cur)
        {
            // 键值重复
            if (key == cur->_key)
            {
                return false;
            }
            cur = cur->_next;
        }

        // 头插 (同一单链表上 顺序无关)
        Node* newNode = new Node(key, value);
        newNode->_next = _tables[index];
        _tables[index] = newNode;
        ++_size;

        return true;
    }

    Node* Find(const K& key)
    {
        size_t index = _HashFunc(key, _tables.size());
        Node* cur = _tables[index];

        while (NULL != cur)
        {
            if (key == cur->_key)
            {
                return cur;
            }

            cur = cur->_next;
        }

        return NULL;
    }

    bool Remove(const K& key)
    {
        size_t index = _HashFunc(key, _tables.size());
        Node* cur = _tables[index];
        Node* prev = cur;

        if (NULL == cur)
        {
            return false;
        }

        // 一个结点
        if (NULL == cur->_next && cur->_key == key)
        {
            delete cur;
            _tables[index] = NULL;
            --_size;
            return true;
        }

        cur = cur->_next;

        while (NULL != cur)
        {
            if (key == cur->_key)
            {
                prev->_next = cur->_next;
                delete cur;
                --_size;
                return true;
            }
            prev = cur;
            cur = cur->_next;
        }

        return false;
    }

    void PrintTables()
    {
        for (size_t index = 0; index < _tables.size(); index++)
        {
            Node* cur = _tables[index];

            while (NULL != cur)
            {
                std::cout<<index<<"  {"<<cur->_key<<"---"<<cur->_value<<"} ";
                cur = cur->_next;

                if (NULL == cur)
                {
                     std::cout<<std::endl;
                }

            }
        }
    }

protected:
    size_t _HashFunc(const K& key, const size_t size)
    {
        // _table.size90 哈希桶空间大小 vector 数组大小（相当于哈希表的空间）
        return HashFunc()(key) % size;
    }

    size_t _GetNextPrime() // 得到下一个扩容的素数
    {
        static const size_t _PrimeSize = 28;
       static const unsigned long _PrimeList [_PrimeSize] =
    {
        53ul,         97ul,         193ul,       389ul,       769ul,
        1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
        49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
        1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
        50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
        1610612741ul, 3221225473ul, 4294967291ul
    };

        for (size_t i = 0; i < _PrimeSize; i++)
        {
            if (_PrimeList[i] > _size)
            {
                return _PrimeList[i];
            }
        }

        return _PrimeList[_PrimeSize - 1];
    }

    void _CheckExpand() // 扩容(容量都是素数)
    {
       if (_size == _tables.size())
       {
           size_t newSize = _GetNextPrime();
           std::vector<Node*> newTables;
           newTables.resize(newSize);

           // newTables.resize() 已经初始化成0x00000000
           /*for (size_t i = 0; i < newSize; i++)
           {
               newTables[i] = NULL;
           }*/


           // 将每个单链表上的元素摘下来 挂到新表上
           for (size_t i = 0; i < _tables.size(); i++)
           {
               Node* cur = _tables[i];

               while (NULL != cur)
               {
                   // 摘结点
                   Node* pTmp = cur;
                   cur = cur->_next;
                   // 挂结点
                   size_t index = _HashFunc(pTmp->_key, newSize);
                   pTmp->_next = newTables[index];
                   newTables[index] = pTmp;    
               }

               _tables[i] = NULL;
           }
       _tables.swap(newTables);
       }
    }

protected:
    std::vector<Node*> _tables;  //   存放头指针
    size_t _size; // _tables中已有元素(头指针)的个数
};

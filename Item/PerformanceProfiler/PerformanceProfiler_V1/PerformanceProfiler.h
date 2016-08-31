#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <assert.h>
#include <stdarg.h>
#include <Windows.h>
// C++ 11
#include <unordered_map>
using namespace std;

//PerformanceProfiler
struct PPNode
{
    string _filename;
    string _function;
    size_t _line;
    string _desc; // 附加描述信息

    PPNode(const char *filename, const char *function, const size_t line, const char *desc)
        :_filename(filename)
        ,_function(function)
        ,_line(line)
        ,_desc(desc)
    {}
    // unordered_map 中 用到operator==
    bool operator==(const PPNode& node) const
    {
        if (_line == node._line
            && _function == node._function
               && _desc == node._desc
               && _filename == node._filename) 
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

typedef long long LongType;
struct PPSection
{
    PPSection()
        :_costTime(0)
        ,_callCount(0)
    {}
    // 不是线程安全的
    void Begin()
    {
        _beginTime = clock(); // <ctime>
    }

    void End()
    {
        _costTime += clock()  - _beginTime;
        ++_callCount;
    }

    LongType _beginTime; // 开始时间
    LongType _costTime;   // 花费时间
    LongType _callCount;  // 调用的次数
};


// 生成 hash键值 的 仿函数结构体  用于stl容器undered_map 的第三个模板参数
//
//template < class Key,                                    // unordered_map::key_type
//           class T,                                      // unordered_map::mapped_type
//           class Hash = hash<Key>,                       // unordered_map::hasher
//           class Pred = equal_to<Key>,                   // unordered_map::key_equal
//           class Alloc = allocator< pair<const Key,T> >  // unordered_map::allocator_type
//           > class unordered_map;


struct PPNodeHash
{
    static size_t BKDRHash(const char *str)
    {
        unsigned int seed = 131; // 31 131 1313 13131 131313
        unsigned int hash = 0;
        while (*str)
        {
            hash = hash * seed + (*str++);
        }

        return (hash & 0x7FFFFFFF);
    }

    size_t operator()(const PPNode& node) const
    {
        static string hash;
        hash = node._desc;
        hash += node._function;

        return BKDRHash(hash.c_str());
    }
};

class SaveAdapter   //    纯虚函数      -----接口
{
public:
    virtual void Save(const char *format, ...) = 0;
};

// 向控制台 打印消息
class ConsoleSaveAdapter: public SaveAdapter
{
public:
    virtual void Save(const char *format, ...) // 实现纯虚函数
    {
        // 可变参数列表   <stdarg.h>
        va_list args;
        va_start(args, format);
        ////////////////////////
        vfprintf(stdout, format, args);
        va_end(args);
    }

};

// 向文件 打印消息
class FileSaveAdapter: public SaveAdapter
{
public:
    FileSaveAdapter(const char* filename)
    {
        _fout = fopen(filename, "w");
        assert(_fout);
    }
    ~FileSaveAdapter()
    {
        if (_fout)
        {
            fclose(_fout);
        }

    }

    virtual void Save(const char *format, ...)
    {
        va_list args;
        va_start(args, format);
        vfprintf(_fout, format, args);
        va_end(args);
    }

protected:
    // 防拷贝  因为有指向外部空间的指针 _fout   防止深浅拷贝的发生  这里简单粗暴 直接禁止 拷贝构造 和operator= 类似于智能指针的Scopedptr
    FileSaveAdapter(const FileSaveAdapter&);
    FileSaveAdapter& operator=(FileSaveAdapter&);

protected:
    FILE* _fout;
};

// 单例  ： 全局只有唯一的一个实例
// 单例的基类 -- 饿汉模式--定义时直接生成实例（也可以换成懒汉模式--用时生成实例）
template<class T>
class Singleton
{
public:
    // 获得实例指针
    static T* GetInstance()
    {
        assert(_sInstence);
        return _sInstence;
    }
protected:
    static T* _sInstence;
};

template<class T>
T* Singleton<T>::_sInstence = new T; // 直接创建模板类 T  的实例   （饿汉模式）

//////////////////////  利用继承 ///////////////////////////////////

class PerformanceProfiler : public Singleton<PerformanceProfiler>
    // Singleton<PerformanceProfiler> 不会产生定义递归效果  只是告诉模板 参数 模板会在编译之前 匹配好具体的值 生成Singleton类 
    // 就像结构体node 中包含node* _next一样  只是node*指针 不会产生递归 如果是node中是node next才会递归定义
{
    friend class Singleton<PerformanceProfiler>;

    // 时间复杂度 O(1)
    //                    K           V        HashKey()
    typedef unordered_map<PPNode, PPSection*, PPNodeHash> PP_MAP;
public:
    PPSection* CreatSection(const char *filename, const char *function,const size_t line, const char* desc)
    {
        PPNode node(filename, function, line, desc);
        PPSection *section = NULL;
        PP_MAP::iterator it = _ppMap.find(node);
        if (it != _ppMap.end())
        {
            section = it->second;
        }
        else
        {
            section = new PPSection;
            _ppMap.insert(pair<PPNode, PPSection*>(node, section));
        }
        
        return section;
    }

    // 内部结构体
    struct Report
    {
        ~Report()
        {
            // 父类方法  GetInstance  获取子类指针 调用子类方法 OutPut
            GetInstance()->OutPut();
        }
    };

    void OutPut()
    {
        ConsoleSaveAdapter csa;
        _OutPut(csa);  ///////////////////利用多态 同一方法 不同处理 写控制台

        FileSaveAdapter fsa("PerFormanceProfilerReport.txt");
        _OutPut(fsa);  ///////////////////利用多态 不同对象 同一方法 不同处理 写文件
    }

    void _OutPut(SaveAdapter& sa)  // 用基类的引用  实现【多态】
    {
        int num = 1;
        PP_MAP::iterator ppIt = _ppMap.begin();
        while (ppIt != _ppMap.end())
        {
        // error  onst PPNode& node = ppIt->first;  要用const  因为node是undered_mapde 的key,key是不允许修改的
            const PPNode& node = ppIt->first;
            PPSection* section = ppIt->second;

            sa.Save("No.%d, Desc: %s\n", num++, node._desc.c_str());
            sa.Save("Filename: %s, Line: %d, Function: %s\n",
                node._filename.c_str()
                , node._line
                ,node._function.c_str());
            sa.Save("CostTime:%.2f, CallCount:%lld\n\n"
                ,(double)section->_costTime/1000/* 秒*/
                ,section->_callCount);
            
            ++ppIt;
        }
    }

protected:
    PerformanceProfiler(){};
    PerformanceProfiler(const PerformanceProfiler&);
    PerformanceProfiler& operator=(const PerformanceProfiler&);
protected:
    // map<PPNode, PPSection*> +ppMap; // 统计资源信息的容器  
    // map 底层红黑树 时间复杂度 O(logN)  
    // PP_MAP->unordered_map 底层 用的是 hashtable  时间复杂度为O(1)  更快    
    // 其实都行  只是 unordered_map 更快
    PP_MAP _ppMap;
};

//PerformanceProfiler::Report report; // 用于最后程序结束 调用析构函数 打印报告

#define PERFORMANCE_PROFILER_EE_BEGIN(sign, desc)\
    PPSection* ps##sign = PerformanceProfiler::GetInstance()->CreatSection(__FILE__, __FUNCTION__, __LINE__ , desc);\
    ps##sign->Begin();

#define PERFORMANCE_PROFILER_EE_END(sign)\
    ps##sign->End();






void TestPP2()
{
    PerformanceProfiler::Report report; // 用于最后程序结束 调用析构函数 打印报告
    // 这里用sleep 模拟运行的时间
    // network  mid   sql  只是宏中的变量名的一部分
    PERFORMANCE_PROFILER_EE_BEGIN(network, "网络");
    // 网络
    Sleep(200);   // 毫秒 <Windows.h>
    PERFORMANCE_PROFILER_EE_END(network);


    PERFORMANCE_PROFILER_EE_BEGIN(mid, "中间逻辑");
    // 中间逻辑
    Sleep(300);
    PERFORMANCE_PROFILER_EE_END(mid);

    PERFORMANCE_PROFILER_EE_BEGIN(sql, "数据库");
    // 数据库
    Sleep(400);
    PERFORMANCE_PROFILER_EE_END(sql);
}


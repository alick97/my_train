#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <string>
#include <stdarg.h>
#include <iostream>
using namespace std;
/*
    空间配置器
*/


/* Trace   调试*/
#define __DEBUG__

static string GetFileName(const string& path)
{
    char ch = '/';
#ifdef _WIN32
    ch = '\\';
#endif
    size_t pos=path.rfind(ch);
    if (pos == string::npos)
        return path;
    else
        return path.substr(pos + 1);
}

// 用于调试追溯的trace log
inline static void __trace_debug(const char* function, const char *filename, int line, char* format, ...)
{
#ifdef __DEBUG__
    // 输出调用函数的信息
    fprintf(stdout, "[ %s:%d]%s", GetFileName(filename).c_str(), line, function);

    // 输出用户打的trace信息
    va_list args;
    va_start(args, format);
    vfprintf(stdout, format, args); // format格式化字符指针   args 是对用的变量
    va_end(args);
#endif
}

#define __TRACE_DEBUG(...) __trace_debug(__FUNCTION__, __FILE__, __LINE__, __VA_ARGS__)


/////////////////////////////////////////
//             一级空间配置器(malloc/realloc/free 的封装)

// 内存分配失败以后的句柄函数handler类型
typedef void(* ALLOC_OOM_FUN)();
template<int inst>
class __MallocAllocTemplate
{
private:
    static ALLOC_OOM_FUN __sMallocAllocOomHander;

    static void* OomMalloc(size_t n)
    {
        ALLOC_OOM_FUN handler = NULL;
        void *result;
        //
        //1 :分配内存成功， 则直接返回
        //2 ：若分配失败，则检查是否设置处理的handler
        //  有则调用以后再分配。 不断重复这个过程，直到分配成功为止。
        // 没有是设置处理的handler， 则直接结束程序。
        //
        while (true)
        {
            handler=__sMallocAllocOomHander;
            if (handler == NULL)
            {
                cerr<<"out of memory"<<endl;
                exit(-1);
            }

            handler();

            result=malloc(n);
            if (result)
                return result;
        }
    }

    static void OomRealloc(void *p, size_t n)
    {
        // 同上
        ALLOC_OOM_FUN handler;
        void* result = NULL;

        for (;;)
        {
            handler=__sMallocAllocOomHander;
            if (0 == handler)
            {
                cerr<<"out of memory"<<endl;
                exit(-1);
            }
            (*handler)();
            result=realloc(p, n);
            if (result) return result;

        }

    }

public:
    static void *Allocate(size_t n)
    {
        __TRACE_DEBUG("(n:%u)\n", n);

        void *result=malloc(n);
        if (NULL == result)
            result = OomMalloc(n);
        return result;
    }

    static void* Reallocate(void *p, size_t new_sz)
    {
        void *result = realloc(p, new_sz);
        if (result == NULL)
        {
            result = OomRealloc(p, new_sz);
        }

        return result;
    }

    static void Deallocate(void *p, size_t /* n */)  // 这里n无用 但这个参数要和 二级的一致 因为class SimpleAlloc封装一二级空间配置器时 调用形式一样
	{
		__TRACE_DEBUG("一级空间配置释放空间:0x%p\n", p);
		free(p);
	}

    //复杂写法  static void(* SetMallocHandler(void(*f)()))()
    // 设置获取空间的 句柄函数
    static ALLOC_OOM_FUN SetMallocHandler(ALLOC_OOM_FUN f)
    {
        ALLOC_OOM_FUN old = __sMallocAllocOomHander;
        __sMallocAllocOomHander = f;
        return old;
    }
};

// 分配内存失败时处理函数的句柄函数指针
// 初始化静态函数

template <int inst>
ALLOC_OOM_FUN __MallocAllocTemplate<inst>::__sMallocAllocOomHander = NULL;





/////////////////////////////  二级空间配置器  /////////////////////////////////////////
//
template<bool threads, int inst>// inst没用 可能以后扩展用 预留的
class __DefaultAllocTemplate
{
private:
    enum {__ALIGN = 8};                 // 排列基准值（排列的间隔 ）
    enum {__MAX_BYTES = 128};            // 最大值
    enum {__NFREELISTS = __MAX_BYTES/__ALIGN};  // 排列链的大小
    // 找 内存向上取整 在 那个范围   如 1,2,3,4,5,6,7，8 ----》 8
    static size_t ROUND_UP(size_t bytes)
    {
        // 对齐
        // 7 8 9
        // 8 8 16
        return ((bytes + __ALIGN - 1) & ~(__ALIGN - 1));
    }

    // 找 内存大小在链表的下标
    static size_t FREELIST_INDEX(size_t bytes)
    {
        // bytes == 9    -----> 1
        // bytes == 8     ---->  0
        // bytes == 7     ----->  0
        return ((bytes + __ALIGN - 1)/ __ALIGN - 1);
    }

    union Obj
    {
        union Obj* _freeListLink; // 指向写一块内存块的指针
        char _clientData[1]; /* the client sees this 调试用的  这里没有用*/
    };


    static Obj* volatile _freeList[__NFREELISTS]; // 自由链表
    static char *_startFree;             // 内存池 水位线开始
    static char *_endFree;             // 内存池水位线结束
    static size_t _heapSize;          // 从系统堆分配的总大小

    // 获取大块内存 插入到自由链表中
     static void *Refill(size_t n);
    // 从内存池分配大块内存
    static char* ChunkAlloc(size_t size, int &nobjs); // nobjs 只是建议的大小 函数里面可能会修改
public:
    static void *Allocate(size_t n);
    static void Deallocate(void *p, size_t n);
    static void *Reallocate(void *p, size_t old_sz, size_t new_sz);
};


// 初始化全局静态对象
template<bool threads, int inst>
typename __DefaultAllocTemplate<threads, inst>::Obj* volatile __DefaultAllocTemplate<threads, inst>::_freeList[__DefaultAllocTemplate<threads, inst>::__NFREELISTS] = {0};

template<bool threads, int inst>
char* __DefaultAllocTemplate<threads, inst>::_startFree = 0;

template<bool threads, int inst>
char* __DefaultAllocTemplate<threads, inst>::_endFree = 0;
template<bool threads, int inst>
size_t __DefaultAllocTemplate<threads, inst>::_heapSize = 0;


/*   假定这个参数 n   就是已经aligned 对齐的*/
template<bool threads, int inst>
void* __DefaultAllocTemplate<threads, inst>::Refill(size_t n)
{
    __TRACE_DEBUG("(n:%u)\n", n);

    // 分配一个n bytes的内存
    // 如果不够  则能分配多少分配多少


    /*链表上没有，需要从内存池申请，本来 n bytes就行  防止下次还要 ， 每次就不是取n字节  而是 取n*nobjs字节 返回n字节 剩下的挂到链表上。*/
    /*这里nobjs=20 只是建议 
因为ChunkAlloc（）中nobjs参数传的是引用 里面 可能比20少*/
    int nobjs = 20;
    char* chunk = ChunkAlloc(n, nobjs);

    // 如果只分配一块， 则直接把这块内存 返回
    if (nobjs == 1)
    {
        return chunk;
    }

    Obj *result, *cur;
    size_t index = FREELIST_INDEX(n);
    result = (Obj*)chunk;

    // 把剩余的块 链接到自由链表上
    cur = (Obj*)(chunk + n);
    _freeList[index] = cur;
    /*看起来是挂在链上其实 内存还是连续一片*/
    for (int i = 2; i < nobjs; i++)
    {
        cur->_freeListLink = (Obj*)(chunk + n*i);
        cur =  cur->_freeListLink;
    }

    cur->_freeListLink = NULL;

    return result;
}


template<bool threads, int inst>
char* __DefaultAllocTemplate<threads, inst>::ChunkAlloc(size_t size, int &nobjs)
{
    __TRACE_DEBUG("(szie： %u, nobjs:%d)\n", size , nobjs);

    char *result;
    size_t bytesNeed = size * nobjs;
    size_t bytesLeft = _endFree - _startFree;

    // 1. 内存池中内存足够，bytesLeft>=bytesNeed，则直接从内存池中取。
    // 2. 内存池中的内存不足， 但是够一个,bytesLeft>=size, 则直接取能够取出来的。
    // 3.内存池中的内存不足， 则从系统堆分配大块的内存到内存池
    
    if (bytesLeft >= bytesNeed)
    {
        __TRACE_DEBUG("内存池中内存足够分配%d个对象\n", nobjs);
        result = _startFree;
        _startFree += bytesNeed;
    }
    else if (bytesLeft >= size)
    {
        __TRACE_DEBUG("内存池中内存不够分配%d个对象， 只能分配%d个对象\n", nobjs,bytesLeft/size);
        result = _startFree;
        nobjs = bytesLeft/size;
        _startFree += nobjs * size;
    }
    else
    {
        // 若内存池中还有小块的剩余内存（不足size），则将它头插到合适的自由链表中
        if (bytesLeft > 0)
        {
            size_t index = FREELIST_INDEX(bytesLeft);//bytesLeft 一定是 aligned 对齐的
            ((Obj*)_startFree)->_freeListLink = _freeList[index];
            _freeList[index] = (Obj*)_startFree;
            _startFree = NULL;

            __TRACE_DEBUG("将内存池中剩余的空间， 分配给freeList[%d]\n", index);
        }

        // 从系统堆分配两倍+已经分配的heapSize/16 的内存到内存池中
        size_t bytesToGet = 2 * bytesNeed + ROUND_UP(_heapSize >> 4); // >>4    /16
        _startFree = (char*)malloc(bytesToGet);
        __TRACE_DEBUG("内存池空间不足， 系统堆分配%u bytes内存\n",bytesToGet);

        // 【无奈之举】
        // 如果在系统堆中内存分配失败， 则尝试到自由链表中更大的节点中分配

        if (_startFree == NULL)
        {
            __TRACE_DEBUG("系统堆已经没有足够的内存， 无奈之下， 只能到自由链表中看看\n");

            // 在 它 和 比他字节大的 自由链节点上找
            // i=size  从自己当前自由链表开始找  是因为 多线程环境 可能会有别的线程还回内存
            for (int i = size; i <= __MAX_BYTES; i += __ALIGN)
            {
                Obj *head = _freeList[FREELIST_INDEX(size)];
                if (head)
                {
                    _startFree = (char*)head;
                    // 摘下 一个内存节点
                    head = head->_freeListLink;
                    //////////////////////////
                    _freeList[FREELIST_INDEX(size)] = head;
                    // 形式上 是在 链上挂着  其实 实际存储还是 数组 是连续的
                    // 内存池 多了一块空间 分配的事情交给 ChunkALLoc 递归  一定可以走到前面的逻辑里面
                    _endFree = _startFree + i;
                    return ChunkAlloc(size, nobjs);
                }
            }
            _endFree = NULL;///////////////////////////////////防止 以及空间适配器__MallocAllocTemplate<inst>::Allocate(bytesToGet);
                                                /////////////// 出现异常 不走下面逻辑  这样 如果异常被捕获  继续执行 可能 算出来的heapSize不为0
                                                ////////////// 因为 _endFree不为NULL  而 startFree为空  _endFree - _startFree ！= 0 其实没空间 但                                          //////////////////////是算出来有空间 这空间不是自己的  用的时候一定出错   _endFree 是野指针
            
            
            // 【山穷水尽， 最后一根稻草(一级空间适配器）】
            // 自由链表中也没有分配到内存， 则再到一级配置器中分配内存，
            // 一级配置器中 可能有 设置的内存处理函数 或许能分配到内存

            __TRACE_DEBUG("系统堆和 自由链表都已没有内存， 一级配置器做最后一根稻草\n");
            _startFree = (char*)__MallocAllocTemplate<inst>::Allocate(bytesToGet);
        }

        // 从系统堆分配的总字节数。（可以用于下次分配时进行调节）
        _heapSize += bytesToGet;
        _endFree = _startFree + bytesToGet;

        // 递归调用获取内存 将执行到前面的逻辑（处理分配）
        return ChunkAlloc(size, nobjs);
    }
    return result;
}


template<bool threads, int inst>
void *__DefaultAllocTemplate<threads, inst>::Allocate(size_t n)
{
    __TRACE_DEBUG("(n:%u)\n", n);

    // 若 n > __MAX_BYTES 则直接在以及空间配置器中获取
    // 否则在二级配置器中获取
     if (n > __MAX_BYTES)
     {
         return  __MallocAllocTemplate<inst>::Allocate(n);
     }

     size_t index = FREELIST_INDEX(n);

     // 1. 如果自由链表中没有内存则通过Refill进行填充
     // 2. 如果自由链表中有则直接返回一个节点块内存
     // ps: 多线程环境要考虑加锁

     Obj *head = _freeList[index];
     if (head == NULL)
     {
         return Refill(ROUND_UP(n));
     }
     else
     {
        __TRACE_DEBUG("自由链表取内存:_freeList[%d]\n", index);
         _freeList[index] = head->_freeListLink;
         return head;
     }
}

template<bool threads, int inst>
void __DefaultAllocTemplate<threads, inst>::Deallocate(void *p, size_t n)
{
    __TRACE_DEBUG("(p:%p, n:%u)\n", p ,n );

    // 若n > __MAX_BYTES则直接归还给一级配置器
    // 否则再放回二级配置器的自由链表

    if (n > __MAX_BYTES)
    {
    __MallocAllocTemplate<inst>::Deallocate(p, n);
    }
    else
    {
        // ps: 多线程环境要考虑加锁
        size_t index = FREELIST_INDEX(n);

        //头插回自由链表
        Obj *tmp = (Obj*)p;
        tmp->_freeListLink = _freeList[index];
        _freeList[index] = tmp;
    }
}

template<bool threads, int inst>
void *__DefaultAllocTemplate<threads, inst>::Reallocate(void* p, size_t old_sz, size_t new_sz)
{
    void *result;
    size_t copy_sz;
    if (old_sz > (size_t)__MAX_BYTES && new_sz > (size_t)__MAX_BYTES)
    {
        // 直接调用一级
        return (__MallocAllocTemplate<inst>::Reallocate(p, new_sz));
    }

    // 在同一个范围 不用处理
    if (ROUND_UP(old_sz) == ROUND_UP(new_sz))
    {
        return p;
    }

    result = Allocate(new_sz);
    copy_sz = new_sz > old_sz? old_sz: new_sz;
    memcpy(result, p, copy_sz);
    Deallocate(p, old_sz);
    return result;
}


/////////////////////////////////////////////
//     封装空间配置器

#ifdef _USE_MALLOC   // 知否指定 只使用一级空间配置器
typedef __MallocAllocTemplate<0> Alloc;
#else
typedef __DefaultAllocTemplate<0,0> Alloc;
#endif

template<class T, class cAlloc = Alloc> 
class SimpleAlloc
{
public:
    static T* Allocate(size_t n) // n是个数
    {
        return 0 == n? 0 :(T*)cAlloc::Allocate(n * sizeof(T));
    }

    static T* Allocate(void) // 只开一个空间
    {
        return (T*)cAlloc::Allocate(sizeof(T));
    }

    static void Deallocate(T *p, size_t n) // n是个数
    {
        if (0 != n)
        {
            cAlloc::Deallocate(p, n * sizeof(T));
        }
    }

    static void Deallocate(T *p)
    {
        cAlloc::Deallocate(p, sizeof(T));
    }
};





// 通过 __TRACE_DEBUG 做白盒测试
// 测试内存池的一级、二级配置器功能

void TestAllocate()
{

    // 测试调用一级配置器分配内存
	cout<<" 测试调用一级配置器分配内存 "<<endl ;
	char*p1 = SimpleAlloc< char, Alloc>::Allocate (129);
	SimpleAlloc<char , Alloc>:: Deallocate(p1 , 129);

    // 测试调用二级配置器分配内存
	cout<<" 测试调用二级配置器分配内存 "<<endl;          //  开 128*20*2 bytes
	char*p2 = SimpleAlloc< char, Alloc>::Allocate (128);
	char*p3 = SimpleAlloc< char, Alloc>::Allocate (128);
	char*p4 = SimpleAlloc< char, Alloc>::Allocate (128);
	char*p5 = SimpleAlloc< char, Alloc>::Allocate (128);
	SimpleAlloc<char , Alloc>:: Deallocate(p2 , 128);
	SimpleAlloc<char , Alloc>:: Deallocate(p3 , 128);
	SimpleAlloc<char , Alloc>:: Deallocate(p4 , 128);
	SimpleAlloc<char , Alloc>:: Deallocate(p5 , 128);

    for (int i = 0; i < 21; ++i) // 前20次 链表取  第21次 refill从内存池取
	{
		printf(" 测试第%d次分配 \n", i +1);
		char*p = SimpleAlloc< char, Alloc>::Allocate (128);
	}
}

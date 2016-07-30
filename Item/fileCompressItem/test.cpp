#define _CRT_SECURE_NO_WARNINGS 1
#include"Heap.h"
#include"FileCompress.h"

//const string name = "test_1.txt";
const string name = "Input.BIG";
void test_FileCompress()
{
    FileCompress fc;
   // fc.Compress("test.txt");
    fc.Compress(name.c_str());
}

void test_FileUncompress()
{
    FileCompress fc;
  //  fc.Uncompress("test.txt");
    fc.Uncompress(name.c_str());
}

#include<Windows.h>
int main()
{
    int begin = GetTickCount();
    test_FileCompress();
    int end = GetTickCount();
    cout<<"压缩文件时间:"<<end - begin<<endl;
  
    begin = GetTickCount();
    test_FileUncompress();
    end = GetTickCount();
    cout<<"解压缩文件时间:"<<end - begin<<endl;

    system("pause");
    return 0;
}

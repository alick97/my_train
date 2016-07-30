#pragma once
#include<iostream>
#include<string>

using namespace std;
#include"HuffmanTree.h"
typedef unsigned long LongType;
struct CharInfo
{
    unsigned char _ch; // 字符
    LongType _count; // 字符出现次数
    string _code; // 哈夫曼编码

    CharInfo(const LongType count = 0)
        :_count(count)
    {}

    CharInfo(const char ch)
        :_ch(ch)
    {};

    CharInfo operator+(const CharInfo& c) const
    {
        return CharInfo(_count + c._count);
    }

    bool operator!=(const CharInfo& c) const
    {
        return _count != c._count;
    }

    bool operator<(const CharInfo& c) const
    {
        return _count < c._count;
    }


};

class FileCompress
{
public:
    FileCompress()
    {}

    // 压缩
    void Compress(const char* filename)
    {
       // 初始化
        for (size_t i = 0; i < 256; ++i)
        {
            _infos[i]._ch = i;
            _infos[i]._count = 0;
        }

        FILE* fOut = fopen(filename, "rb");
        assert(fOut);


        // 1 统计文件中字符出现的次数
        char ch = fgetc(fOut);

       // while (ch != EOF)
        while (!feof(fOut))
        {
            _infos[(unsigned char)ch]._count++; // 【注意】作下表 用无符号
            ch = fgetc(fOut);
        }

        // 构建HuffmanTree
        CharInfo invalid; // 默认值作为 无效值
        HuffmanTree<CharInfo> h_tree(_infos, 256, invalid);
        HuffmanNode<CharInfo>* h_root = h_tree.GetRootNode(); 
        // 生成Huffman编码
        string str; // 记录编码
        GenerateHuffmanCode(h_root, str); 


     
        char data = 0; // 写入压缩文件的数据
        int bitcount = 7; // 标记移位信息
        string compressFilename(filename); // 压缩文件名称
        compressFilename += ".compress";
        FILE* fIn = fopen(compressFilename.c_str(), "wb");

           // 文件指针 调到开头
        fseek(fOut, 0, SEEK_SET);
        ch = fgetc(fOut);

       // while (ch != EOF)
        while (!feof(fOut))
        {
            const char* cur = _infos[(unsigned char)ch]._code.c_str();

            while (*cur)
            {
                if (bitcount >= 0)
                {
                    data <<= 1; // 左移 向高位移动
                    data = data | (*cur - '0');  
                    bitcount--;
                }

                if (bitcount < 0) // 8 位满
                {
                    fputc(data, fIn);
                    bitcount = 7;
                    data = 0;
                }

                cur++;
            }

            ch = getc(fOut);
        }

        // 最后没写满一个字节 
        data <<= bitcount + 1;
        fputc(data, fIn);

        // 写配置文件
        string configFile = filename;
        configFile += ".config";
        FILE* fConfig = fopen(configFile.c_str(), "wb");
        assert(fConfig);
        string line;
        char buffer[150];
        for (size_t i = 0; i < 256; i++)
        {
            if (_infos[i]._count > 0)
            {
                line += _infos[i]._ch;
                line += ",";

                _itoa(_infos[i]._count, buffer, 10); // 10 十进制
                line += buffer;
                line += '\n';

                fputs(line.c_str(), fConfig);
            }

            line.clear();
        }

        fclose(fConfig);
        fclose(fIn);
        fclose(fOut);
    }
    
    bool ReadLine(FILE* fOut, string& line)
    {
        char ch = fgetc(fOut);
        //if (ch == EOF)
        if (feof(fOut))
        {
            return false;
        }

        while ((!feof(fOut)) && ch != '\n')
        {
            line += ch;
            ch = fgetc(fOut);
        }

        return true;
    }



    // 解压缩
    void Uncompress(const char* filename)
    {
        // 初始化
        for (size_t i = 0; i < 256; ++i)
        {
            _infos[i]._ch = i;
            _infos[i]._count = 0;
        }

        // 读配置文件，得到字符出现的次数
        string configFile = filename;
        configFile += ".config";
        FILE* fConfig = fopen(configFile.c_str(), "rb");
        assert(fConfig);
        string line;
        while (ReadLine(fConfig, line))
        {
            // 【注意】解决‘\n’统计的问题
            if (line.empty())
            {
                line += '\n';
            }
            else
            {
                _infos[(unsigned char)line[0]]._count = atoi(line.substr(2).c_str()); 
                line.clear();
            }
        }

        // 构建HuffmanTree
        CharInfo invalid;
        HuffmanTree<CharInfo> h_tree(_infos, 256, invalid);

        // 【注意】防止多解压填充的字符 树顶的_count 正好就是所有字符的个数 用这个变量来记录结束
        int uncompress_ch_count = (h_tree.GetRootNode())->_weight._count;

        // 读取压缩文件，进行还原
        string compressFile = filename;
        compressFile += ".compress";
        FILE* fOut = fopen(compressFile.c_str(), "rb");
        assert(fOut);

        // 还原文件
        string uncompressFile = filename;
        uncompressFile += ".uncompress";
        FILE* fIn = fopen(uncompressFile.c_str(), "wb");
        assert(fIn);

        HuffmanNode<CharInfo>* h_root = h_tree.GetRootNode();
        HuffmanNode<CharInfo>* cur = h_root;
        char ch = fgetc(fOut);
        int pos = 7;

       // while (ch != EOF)
        while (!feof(fOut)) // 【注意】feof用总字节个数的方式来判断文件结束 而 EOF 使用文件结尾的EOF(-1)标记位 【缺点 对于ascii为-1（中文要2、3个字节编码 其中有一个字节就可能是 -1）的字符 误判 为结束】
        {
            if (ch & (1 << pos)) // 左0 右1
            {
                cur = cur->_right;
            }
            else
            {
                cur = cur->_left;
            }

            if (cur->_left == NULL && cur->_right == NULL)
            {
                if (uncompress_ch_count == 0) // 防止最后写入填充的字符
                {
                    break;
                }

                // 写解压字符
                fputc(cur->_weight._ch, fIn);
                uncompress_ch_count--;
                cur = h_root;
            }

            if (pos == 0)
            {
                ch = fgetc(fOut);
                pos = 8;
            }

            --pos;
        }

        fclose(fOut);
        fclose(fIn);
    }


protected:
    void  GenerateHuffmanCode(HuffmanNode<CharInfo>* root, string code) // str 值传递不用引用 退栈不用考虑str去除多余
    {
        if (root == NULL)
        {
            return;
        }

        // 左边 0  右边1
        GenerateHuffmanCode(root->_left, code + '0'); 
        GenerateHuffmanCode(root->_right, code + '1'); 

        if (root->_left == NULL && root->_right == NULL)
        {
            _infos[(root->_weight)._ch]._code = code;
        }
    }

private:
    CharInfo _infos[256];
};

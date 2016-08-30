/*************************************************************************
	> File Name: comm.cpp
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月24日 星期三 22时45分30秒
 ************************************************************************/
#include "comm.h"
const int _SIZE_ = 1024;


void print_log(const char *errorstr,const char *fun, int line)
{
	printf("fun:%s[line:%d]  %s \n", fun,line, errorstr);
}

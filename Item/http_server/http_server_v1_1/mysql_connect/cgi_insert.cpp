/*************************************************************************
	> File Name: sql_insert.cpp
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月15日 星期一 15时44分54秒
 ************************************************************************/
#include "sql_api.h"
#include <string.h>
//arg= "name=bozi&class=class1"
//

void myinsert(char *arg)
{
	sql_api * sql = new sql_api;
	std::string cols = "(name, class)";
	char* buf[3];
	buf[2]= NULL;
	int index = 1;

	char *end = arg + strlen(arg) - 1;
	while (end > arg)
	{
		if (*end == '=')
		{
			buf[index--] = end + 1;
		}

		if (*end == '&')
		{
			*end = '\0';
		}
		end--;
	}
	// ("---", "---")
	std::string data = "(\"";
	data += buf[0];
	data += "\",\"";
	data += buf[1];
	data += "\")";

	sql->my_connect_mysql();
	if (sql->my_insert(cols, data, "student_tb") == 0)
	std::cout<<"insert success"<<std::endl;
	else
		std::cout<<"insert failed"<<std::endl;
	delete sql;
}

int main()
{
	//char arg[] = "name=in&class=class5";
	char method[1024];
	char arg[1024];
	char content_len[1024];
	int len = -1;
	if (getenv("REQUEST_METHOD"))
	{
		strcpy(method, getenv("REQUEST_METHOD"));
	}

	if (strcasecmp(method,"GET") == 0 )
	{
		if (getenv("QUERY_STRING"))
		{
			strcpy(arg, getenv("QUERY_STRING"));
		}
	}
	else // post
	{
		if (getenv("CONTENT_LENGTH"))
		{
			strcpy(content_len, getenv("CONTENT_LENGTH"));
			len = atoi(content_len);
		}
		////////////////////////   读取name：value值
		int i = 0;
		for (; i < len; i++)
		{
			read(0, &arg[i], 1);
		}

		arg[i] = '\0';
	}
	myinsert(arg);
	return 0;
}

/*************************************************************************
	> File Name: sql_select.cpp
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月15日 星期一 15时55分58秒
 ************************************************************************/

#include "sql_api.h"

void myselect()
{
	sql_api *sql = new sql_api;
	sql->my_connect_mysql();
	sql->my_select("student_tb");

	delete sql;
}

int main()
{
	myselect();
	return 0;
}

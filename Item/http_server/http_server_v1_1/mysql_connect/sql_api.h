/*************************************************************************
	> File Name: sql_api.cpp
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月14日 星期日 21时13分18秒
 ************************************************************************/
#pragma once

#include<iostream>
#include <string>
#include "mysql.h"

class sql_api
{
	public:
		sql_api(const std::string &_host="127.0.0.1", const std::string &_user="root", const std::string &_passwd="", const std::string &_db="test_http");
		int my_connect_mysql();
		int my_insert(const std::string &cols, const std::string &data,const std::string &table);
		int my_select(const std::string &table);
		~sql_api();

	private:
		MYSQL *conn;
		MYSQL_RES *res;
		std::string host;
		std::string user;
		std::string passwd;
		std::string db;
		int port;
};


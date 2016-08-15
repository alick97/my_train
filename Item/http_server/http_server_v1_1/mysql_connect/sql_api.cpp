/*************************************************************************
	> File Name: sql_api.cpp
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月14日 星期日 22时14分15秒
 ************************************************************************/
#include "sql_api.h"

sql_api::sql_api(const std::string &_host, const std::string &_user, const std::string &_passwd, const std::string &_db)
	:host(_host)
	 ,user(_user)
	 ,passwd(_passwd)
	 ,db(_db)
{
	port = 3306;
	res = NULL;
	conn = mysql_init(NULL);
}

int sql_api::my_connect_mysql()
{
	int ret = -1;
	if (!mysql_real_connect(conn, host.c_str(), user.c_str(), passwd.c_str(), db.c_str(), port, NULL, 0))
	{
		std::cerr<<"connect faild!"<<std::endl;
	}
	else
	{
		std::cout<<"connect success!"<<std::endl;
		ret = 0;
	}
	return ret;
}
	int sql_api::my_insert(const std::string &cols, const std::string &data,const  std::string& table)
{
	std::string sql = "INSERT INTO " + table + " ";
	sql += cols;
	sql += " VALUES ";
	sql += data;

	std::cout<<sql<<std::endl;

	if (mysql_query(conn, sql.c_str()) == 0)  
	{
	//	std::cout<<"insert success"<<std::endl;
		return 0;
	}
	else
	{
		std::cerr<<"insert faild"<<std::endl;
		return -1;
	}

}
	int sql_api::my_select(const std::string & table)
{
	std::string sql = "SELECT * FROM " + table ;
	if (mysql_query(conn, sql.c_str()) == 0)
	{
		std::cout<<"select success "<<std::endl;
	}
	else
	{
		std::cerr<<"select  failed "<<std::endl;
		return -1;
	}
	
	res = mysql_store_result(conn);
	if (res)
	{
		int lines = mysql_num_rows(res);
		int cols = mysql_num_fields(res);

		std::cout<<"line :"<<lines<<" "<<"cols :"<<cols<<std::endl;

		MYSQL_FIELD *_fn = NULL;
		for (; _fn = mysql_fetch_field(res); ) // 获取 表头
		{
			std::cout<<_fn->name<<'\t';
		}

		std::cout<<std::endl;

		int i = 0;
		for (; i < lines; i++)
		{
			MYSQL_ROW row = mysql_fetch_row(res);
			int j = 0;
			for (; j< cols; j++)
			{
				std::cout<<row[j]<<'\t';
			}
			std::cout<<std::endl;
		}
		///////////  一定记得 free    否则 内存泄漏      ////////////////////
		free(res);

		std::cout<<std::endl;
		
	}
}
	sql_api::~sql_api()
{
	mysql_close(conn);
}


//int main()
//{
//	sql_api mysql;
//	mysql.my_connect_mysql();
//
//	std::string cols = "(name, class)";
//	std::string data = "('xiaoQ', 'class 5')";
//	mysql.my_insert(cols, data, "student_tb");
//	mysql.my_select("student_tb");
//
//	std::cout<<"client info: "<<mysql_get_client_info()<<std::endl;
//	return 0;
//}

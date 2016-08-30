/*************************************************************************
	> File Name: udp_data.cpp
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月23日 星期二 22时56分27秒
 ************************************************************************/
#include "udp_data.h"

udp_data::udp_data()
	:_cmd("None")
{}

udp_data::~udp_data()
{}

void udp_data::to_string(std::string &out)// 序列化
{
	Json::Value val;
	val["name"] = _name;
	val["msg"] = _msg;
	val["school"] = _school;
	val["cmd"] = _cmd;
	my_json::serialize(out,val);
}

void udp_data::to_value(std::string &in)// 反序列化
{
	Json::Value val;
	my_json::unserialize(val, in);
	_name = val["name"].asString();
	_msg = val["msg"].asString();
	_school = val["school"].asString();
	_cmd = val["cmd"].asString();
}

#ifdef __DEBUG__
int main()
{
	std::string out_str;
    udp_data _data;
	_data._name = "bozi";
	 _data._msg = "nihao";
	 _data._school = "kd";
	 _data._cmd = "None";
	_data.to_string(out_str);

	std::cout<<out_str<<std::endl;

	return 0;
}
#endif

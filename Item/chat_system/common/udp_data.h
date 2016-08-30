/*************************************************************************
	> File Name: udp_data.h
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月23日 星期二 22时53分15秒
 ************************************************************************/
#pragma once
#include<iostream>
#include <string>
#include "my_json.h"

class udp_data
{
public:
	udp_data();
	~udp_data();
	void to_string(std::string &out);// 序列化
	void to_value(std::string &in);// 反序列化
//prtected:
	std::string _name;
	std::string _school;
	std::string _msg;
	std::string _cmd;
};

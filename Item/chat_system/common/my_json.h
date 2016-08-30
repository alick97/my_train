/*************************************************************************
	> File Name: my_json.h
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月23日 星期二 22时38分37秒
 ************************************************************************/
#pragma once
#include<iostream>

#include <string.h>
#include "json/json.h"

class my_json
{
	public:
		my_json();
		~my_json();
		// 序列化    value->string
		static void serialize(std::string& out, Json::Value& val);
		// 反序列化 string -> value
		static void  unserialize(Json::Value& val, std::string& in);
};

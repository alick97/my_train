/*************************************************************************
	> File Name: my_json.cpp
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月23日 星期二 22时45分52秒
 ************************************************************************/
#include "my_json.h"


// 序列化 成 out_str
 void  my_json::serialize(std::string& out, Json::Value& val)
{
#ifdef _DEBUG_
	Json::FastWriter write;
	out = write.write(val);
#else
	Json::StyledWriter write;   // StyleWriter 比 FastWriter 多一些\n  格式好看 方便调试
	out = write.write(val);
#endif
}

// 反 序列化 成 val
 void  my_json::unserialize(Json::Value& val, std::string& in)
{
	Json::Reader read;
	read.parse(in, val, false);
}




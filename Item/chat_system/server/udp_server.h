#pragma once
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>


#include <map>
#include "data_pool.h"
#include "comm.h"
#include "udp_data.h"

class udp_server
{
public:
	udp_server(const std::string &ip = "127.0.0.1", const short &port =9999);
	~udp_server();
	void init();
	int recv_data(std::string &out);
	int send_data(struct sockaddr_in &client, socklen_t len, std::string& msg);
	int broadcast_data();
	void add_user( struct sockaddr_in &client);
	bool is_user_exist(const std::string &key);
	int del_user(struct sockaddr_in &cli);
private:
	std::string _ip;
	int _sock;
	short int _port;
	std::map<std::string,struct sockaddr_in > _online_user;// 在线用户socket 用于广播 这里用ip作为key

	data_pool _data_pool; // 数据池
};

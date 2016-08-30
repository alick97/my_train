/*************************************************************************
	> File Name: udp_client.h
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月23日 星期二 21时02分39秒
 ************************************************************************/
#pragma once

#include<iostream>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include "comm.h"
#include <stdio.h>
#include <vector>
#include "cwindow.h"
#include "udp_data.h"

class udp_client
{
public:
	udp_client(const std::string& ip="127.0.0.1", const short int& port = 9999);
	~udp_client();
	void add_friend(const std::string &_win_f);
	void del_friend(const std::string &_win_f);
	void init();
	int recv_data(std::string & out);
	int send_data(const std::string& in);
	std::vector<std::string> clif;
protected:
	std::string _ip;
	short int _port;
	int _sock;
};

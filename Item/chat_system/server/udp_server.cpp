#include "udp_server.h"
#include "comm.h"
#include "data_pool.h"



udp_server::udp_server(const std::string &ip , const short int &port)
    :_ip(ip)
	 ,_port(port)
	,_sock(-1)
	,_data_pool(64)
{
	init();
}

udp_server::~udp_server()
{
	if (_sock > 0)
	{
		close(_sock);
		_sock = -1;
	}
}

void udp_server::init()
{
	_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (_sock < 0)
	{
		print_log("create socket error!", __FUNCTION__, __LINE__);
		exit(1);		
	}

	struct sockaddr_in local;
	socklen_t len = sizeof(local);
	local.sin_family = AF_INET;
	local.sin_port = htons(_port);
	if (_ip == "any")
	{
		local.sin_addr.s_addr = htons(INADDR_ANY);
	}
	else
	{
		local.sin_addr.s_addr = inet_addr(_ip.c_str());
	}

	if (bind(_sock, (struct sockaddr *)&local, len) < 0)
	{
		print_log(strerror(errno), __FUNCTION__, __LINE__);
		exit(2);
	}
}

int udp_server::recv_data(std::string &out) // out arg
{
	char buf[_SIZE_];
	struct sockaddr_in client;
	socklen_t len = sizeof(client);


	ssize_t size = recvfrom(_sock, buf, sizeof(buf) - 1, 0, (struct sockaddr*)&client, &len);
	if (size > 0)
	{
		buf[size] = '\0';
		out=buf;
		std::string key_ip = inet_ntoa(client.sin_addr);
		print_log(key_ip.c_str(), __FUNCTION__,__LINE__);
		// 更新 用户 列表
		add_user(client);

		// 删除退出的用户
		udp_data data;
		data.to_value(out);
		if (data._cmd == "QUIT")
		{
			del_user(client);
		}
		else
		{
		// 数据放到数据池
		_data_pool.put_data(out);

		}
	}
	else if ( size == 0)
	{
		print_log("client close !!!", __FUNCTION__,__LINE__);
	}
	else
	{
		print_log("recvfrom error", __FUNCTION__, __LINE__);
	}
	return size;
}

int udp_server::send_data(struct sockaddr_in &client, socklen_t len, std::string& msg)// 1->1
{
	ssize_t size = sendto(_sock, msg.c_str(), msg.size(), 0, (struct sockaddr*) &client, len);
	if (size < 0)
	{
		print_log(strerror(errno), __FUNCTION__, __LINE__);
	}
	return size;
}

int udp_server::broadcast_data()// 1->n
{
	//std::string msg = "server broadcast test";
	std::string  msg;
	_data_pool.get_data(msg);//从数据池取出数据 然后向所有用户一个一个发送 相当于广播
	
	std::map<std::string , struct sockaddr_in>::iterator iter = _online_user.begin();

		///////////////////////debug/////////////////
		printf("online user size:%d\n",_online_user.size());
	while (iter != _online_user.end())
	{
		send_data((*iter).second, sizeof((*iter).second), msg);
		iter++;
	}
	return 0;
}

void udp_server::add_user( struct sockaddr_in &cli)
{
	std::string key_ip = inet_ntoa(cli.sin_addr);
	std::cout<<"cli ip"<<key_ip<<std::endl;
	//std::map<std::string, struct sockaddr_in>::iterator iter = _online_user.find(key_ip);
	//if (iter  == _online_user.end())
	//{
	//	_online_user.insert(std::pair<std::string, struct sockaddr_in>(key_ip, cli));
	//}
	// 更 高效   缺陷  同一ip 只允许一个用户 因为用IP作键值 同一ip后进入的的客户端会将前面的替换掉 导致前面的客户端收不到消息
	_online_user[key_ip] = cli ;
		///////////////////////debug/////////////////
		printf("add user online user size:%d\n",_online_user.size());
}


bool udp_server::is_user_exist(const std::string &key)
{
    std::map<std::string, struct sockaddr_in>::iterator iter = _online_user.find(key);
	if (iter == _online_user.end())
	{
		return false;
	}
	else
	{
		return true;
	}
}

int udp_server::del_user(struct sockaddr_in &cli)
{
	std::string key = inet_ntoa(cli.sin_addr);
	///////////////////////////op?/////////////////////////
	if (is_user_exist(key))
	{
		_online_user.erase(key);
		return 0;
	}
	return -1;
}



void Usage(const char* proc)
{
	std::cout<<"Usage:"<<proc<<"[ip] [port]"<<std::endl;
}

static void* recv(void *arg)
{
	udp_server * ser=(udp_server*)arg;
	std::string out;
	udp_data data;
	while (1)
	{
		ser->recv_data(out); // out arg
		printf("client: %s", out.c_str());
	//	data.to_value(out);
	//	std::cout<<data._name<<std::endl;
	//	std::cout<<data._school<<std::endl;
	//	std::cout<<data._msg<<std::endl;
	//	std::cout<<data._cmd<<std::endl;
	}
}

static void* broad_cast(void *arg)
{
	udp_server *ser = (udp_server *)arg;
	while (1)
	{
		ser->broadcast_data();
	}
}

int main(int argc , const char *argv[])
{
	if (argc != 3)
	{
		Usage(argv[0]);
		exit(1);
	}

	std::string ip = argv[1];
	short int port = atoi(argv[2]);
	udp_server _ser(ip, port);
    pthread_t tid1;
	pthread_t tid2;
	pthread_create(&tid1, NULL, recv, (void*)&_ser);
	pthread_create(&tid2, NULL, broad_cast, (void*)&_ser);
    
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

//	std::string out;
//	while (1)
//	{
//		_ser.recv_data(out);
//		std::cout<<"client# "<<out<<std::endl;
//	}
	return 0;
}

/*************************************************************************
	> File Name: udp_client.cpp
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月23日 星期二 21时02分49秒
 ************************************************************************/
#include "udp_client.h"
#include "comm.h"
#include <signal.h>

void  sig_cli_exit(int sig);

udp_client::udp_client(const std::string& ip, const short int& port)
	:_ip(ip)
	 ,_port(port)
	 ,_sock(-1)
{
	init();
}

udp_client::~udp_client()
{
    if (_sock > 0)
	{
		close(_sock);
		_sock = -1;
	}
}

void udp_client::init()
{
	_sock=socket(AF_INET, SOCK_DGRAM, 0);
	if (_sock < 0)
	{
		print_log(strerror(errno), __FUNCTION__, __LINE__);
		exit(1);
	}
}


int udp_client::recv_data(std::string &out) //out arg
{
	struct sockaddr_in server;
	socklen_t len = sizeof(server);
	char buf[_SIZE_];
	ssize_t size = recvfrom(_sock, buf, sizeof(buf) - 1, 0, (struct sockaddr*)&server, &len);
	if (size >  0)
	{
		buf[size] = '\0';
		out = buf;
	}
	else if (size == 0)
	{
		print_log("server closed...", __FUNCTION__, __LINE__);
	}
	else
	{
		print_log(strerror(errno), __FUNCTION__, __LINE__);
	}
	return size;
}

int udp_client::send_data(const std::string& in)
{
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(_port);
	server.sin_addr.s_addr = inet_addr(_ip.c_str());
	socklen_t len = sizeof(server);
	ssize_t size = sendto(_sock, in.c_str(), in.size(), 0, (struct sockaddr*)&server, len);
	if (size < 0)
	{
		print_log(strerror(errno), __FUNCTION__,__LINE__);
	}
	return size;
}


void Usage(const char* proc)
{
	assert(proc);
	std::cout<<"Usage:"<<proc<<"[ip] [port]"<<std::endl;
}


void udp_client::add_friend(const std::string &_win_f)
{
	std::vector<std::string>::iterator it = clif.begin();
	for (; it != clif.end(); ++it)
	{
		if (*it == _win_f)
		{
			return;
		}
	}
	clif.push_back(_win_f);
}

void udp_client::del_friend(const std::string &_win_f)
{
	std::vector<std::string>::iterator it = clif.begin();
	for (; it != clif.end();)
	{
		if (*it == _win_f)
		{
			it = clif.erase(it);
			break;
		}
		else
		{
			it++;
		}
	}
}
//////////////////////////////////////////////
/////////////////////////////////////////////
//
//
udp_client *cli_p = NULL;
std::string nick_name;
std::string school;
cwindow *g_win = NULL;

static void *draw_header(void *arg)
{
	cwindow *p_win = (cwindow*)arg;
	p_win->create_header();

	bool done = false;
    std::string line = "welcome to chat";
	int max_y;
	int max_x;
	getmaxyx(p_win->header, max_y, max_x);// 获取对应窗体的高 和 宽

	int y = max_y/2;
	int x = 1;

	while (!done)
	{
		p_win->put_str_to_win(p_win->header, y, x, line);
		cwindow::myflush(p_win->header);
		usleep(100000);
		p_win->clear_win_line(p_win->header, y, 2);
		x++;
		if (x > max_x)
		{
			x -= max_x;
		}
	}
}

static void *draw_output(void *arg)
{
	std::string msg;
	cwindow *p_win = (cwindow*)arg;
	p_win->create_output();
	int max_y;
	int max_x;
	getmaxyx(p_win->output, max_y, max_x);


	udp_data data;
//	std::string _nick_name;
//	std::string _msg;
//	std::string _school;
//	std::string _cmd;
	std::string win_out;
	std::string win_u;

	bool done = false;
	int y = 1;
	while (!done)
	{
		cli_p->recv_data(msg);
		////////////////////////////////////////////////////
		//std::string t2 = "ima in test";
		//cli_p->send_data(t2);
    	data.to_value(msg);
        win_out = data._name;
		win_out += "-";
		win_out += data._school;

		win_u = win_out;

		win_out += "# ";
		win_out += data._msg;
		cli_p->add_friend(win_u);

		////////////////////////debug////////////////////////////
		//std::string t = "test";
		//cli_p->send_data(t);
		if (y >= max_y - 1)
		{
			y = 1;
			p_win->clear_win_line(p_win->output, 1, max_y - 1);
		}
		p_win->put_str_to_win(p_win->output, y++, 3, win_out);

    	cwindow::myflush(p_win->output);

	}
}

static void *draw_friend(void *arg)
{

	cwindow *p_win = (cwindow*)arg;

	p_win->create_userlist();
	int max_uy;
	int max_ux;
	int height = max_uy - 3;
	getmaxyx(p_win->userlist, max_uy, max_ux);
		int size = (cli_p->clif).size();
		int page = size/(height);
		int mod = size%(height);
		if (mod != 0)
		{
			page++;
		}
		int page_index = 0;
		// 简单版 不分页 有瑕疵
//		while(1)
//		{
//			int i = 0;
//	    	for (i = 0; i < cli_p->clif.size();i++)
//			{
//	
//		      	p_win->put_str_to_win(p_win->userlist, i+1 , 3, cli_p->clif[i]);
//				cwindow::myflush(p_win->userlist);
//				sleep(1);
//			}
//	
//		}
//
//
//
//
while (1)
{


    int i = 0;
	int j = 1;
	for (i = 0; i < cli_p->clif.size(); i++)
	{
	    p_win->put_str_to_win(p_win->userlist, j, 3, cli_p->clif[i]);
		cwindow::myflush(p_win->userlist);
		j++;
		if (i % height == 0)
		{
			sleep(1);
			j = 1;
            p_win->clear_win_line(p_win->userlist,1, height);
		}
	}

}

       // while (1)
	   // {
       //     p_win->clear_win_line(p_win->userlist,1, height);
	   //    
	   //    int max;
	   //    if (page_index * height  >= size)
	   //    {
	   //   	 max = mod;
	   //   	 page_index = 0;
	   //    }
	   //    else
	   //    {
	   //   	 max = height;
	   //    }
	   //    int i = (page_index) * (height);
       //    int j = 1;
	   //    while (i < size && j <= max)
	   //    {
	   //   	p_win->put_str_to_win(p_win->userlist, j, 3, cli_p->clif[i]);
	   // 	cli_p->send_data(cli_p->clif[i]);
	   // 	i++;
	   // 	j++;
	   //    }
	   //    cwindow::myflush(p_win->userlist);
  	   //    sleep(2);
	   // }
}


static void *draw_input(void *arg)
{
	cwindow *p_win = (cwindow*)arg;
	p_win->create_input();
	std::string line = "Please Enter# ";
	int max_y;
	int max_x;
	getmaxyx(p_win->input, max_y, max_x);

	udp_data data;
	std::string out;
	data._school = school;
	data._name = nick_name;
	bool done = false;
	while (!done)
	{
		p_win->put_str_to_win(p_win->input, 1, 1, line);
		cwindow::myflush(p_win->input);

		data._msg  = p_win->get_str_from_win(p_win->input);
		p_win->clear_win_line(p_win->input, 1, 2);

		if (data._msg == "quit" || data._msg == "q")
		{
			data._cmd = "QUIT";

			data.to_string(out);
			cli_p->send_data(out);
			//exit(1);
			sig_cli_exit(0);

		}
		// 序列化
		data.to_string(out);
		cli_p->send_data(out);

		//usleep(1000);
	}
	
}


void  sig_cli_exit(int sig)
{
	udp_data data;
	data._cmd = "QUIT";
	std::string str;
	data.to_string(str);
	cli_p->send_data(str);
	g_win->~cwindow();
	exit(1);
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		Usage(argv[0]);
		exit(3);
	}
	short int port = atoi(argv[2]);
	char *ip = argv[1];

//	std::string rec;
//	std::string in;
//	char buf[_SIZE_];
//	udp_client cli(ip, port);
//	while (1)
//	{
//		std::cout<<"please input: ";
//		fflush(stdout);
//		memset(buf, '\0', sizeof(buf));
//		ssize_t size = read(0, buf, sizeof(buf) - 1);
//		if (size > 0)
//		{
//			rec=buf;
//			cli.send_data(rec);
//		}
//
//		if (buf == "quit")
//		{
//			std::cout<<"no data send"<<std::endl;
//			return 0;
//		}
//
//		sleep(2);
//		if (cli.recv_data(in) > 0)
//		{
//			std::cout<<"server echo:"<<in<<std::endl;
//		}
//	}


	std::cout<<"Please Enter Your Nick_name: ";
	fflush(stdout);
	std::cin>>nick_name;
	std::cout<<"Please Enter Your Shool:";
	fflush(stdout);
	std::cin>>school;

	signal(SIGINT, sig_cli_exit);
	udp_client cli(ip, port);
	cli_p = &cli;

	cwindow win;
	g_win = &win;
	pthread_t t_head, t_output, t_input, t_friend;
	pthread_create(&t_head, NULL, draw_header, (void*)&win);
	pthread_create(&t_friend, NULL, draw_friend, (void*)&win);
    pthread_create(&t_output, NULL, draw_output, (void*)&win);
	pthread_create(&t_input, NULL, draw_input, (void*)&win);

	pthread_join(t_head, NULL);
	pthread_join(t_friend, NULL);
	pthread_join(t_output, NULL);
	pthread_join(t_input, NULL);
	return 0;
}


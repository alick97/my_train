/*************************************************************************
	> File Name: select_2.c
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月08日 星期一 01时20分47秒
 ************************************************************************/
/* 利用select 编写网络服务器 */
#include<stdio.h>
#include <string.h>
#include <sys/select.h>

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

       #include <sys/types.h>          /* See NOTES */
       #include <sys/socket.h>
      #include <arpa/inet.h>



#define _PORT_ 9999
#define _MAX_SIZE_ 10
#define _BACK_LOG_ 5
#define _BUF_SIZE_ 1024

int fd_arr[_MAX_SIZE_];
int max_fd = 0;

static void init_fd_arr()
{
	int i =0;
	for (; i < _MAX_SIZE_; i++)
	{
		fd_arr[i] = -1;
	}
}

static int add_fd_arr(int fd)
{
	int i = 0;
	for (; i < _MAX_SIZE_; i++)
	{
		if (fd_arr[i] == -1)
		{
			fd_arr[i] = fd;
			return 0;
		}
	}
	return -1;
}

static int remove_fd_arr(int fd)
{
	int i = 0;
	for (; i < _MAX_SIZE_; i++)
	{
		if (fd_arr[i] == fd)
		{
			fd_arr[i] = -1; 
			return 0;
		}
	}
	return -1;
}


static void reload_fd_set(fd_set *fd_setp)
{
	int i = 0;
	for (; i < _MAX_SIZE_; i++)
	{
		if (fd_arr[i] != -1)
		{
			FD_SET(fd_arr[i], fd_setp);
			if (fd_arr[i] > max_fd)
			{
				max_fd = fd_arr[i];
			}
		}
	}
}

static void print_msg(int i , char buf[])
{
	printf("fd : %d, msg: %s\n", i , buf);
}

int select_server()
{
	struct sockaddr_in server;
	struct sockaddr_in client;
	fd_set fds;

	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0)
	{
		perror("socket");
		return 1;
	}
	printf("create socket success\n");
	int yes = 1;
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes ,sizeof(int));// 允许IP地址复用
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(_PORT_);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(fd, (struct sockaddr*)&server, sizeof(server)) < 0)
	{
		perror("bind");
		return 2;
	}
	printf("bind socket success\0");

	init_fd_arr();
	add_fd_arr(fd);

	FD_ZERO(&fds);
	if (listen(fd, _BACK_LOG_) < 0)
	{
		perror("listen error");
		return 3;
	}

	printf("listen socket success\n");


	while (1)
	{
		// 由于 select fds是 输入-输出型参数 完了值会被改变 所以每次从arr中重新加载
		reload_fd_set(&fds);
		struct timeval timeout = {30, 0};
		switch(select(max_fd + 1, &fds/*read*/,NULL, NULL, &timeout ))
		{
			case -1:
				printf("select error, quit\n");
				return 4;
			case 0:
				printf("select timeout, continue wait...\n");
				break;
			default:
				{
					int index = 0;
					for (; index < _MAX_SIZE_; index++)
					{
						if (index == 0 && fd_arr[index] != -1 && FD_ISSET(fd_arr[index], &fds))
						{
							socklen_t len = sizeof(client);
							bzero(&client, len);
							int new_fd = accept(fd_arr[index], (struct sockaddr*)&client,&len );
							// 有新的连接
							if (new_fd != -1)
							{
								printf("get a new request!\n");
								// 添加到arr中
								if (-1 == add_fd_arr(new_fd))
								{
									perror("fd arr is full, close new fd\n");
									close(new_fd);
								}
							}
							continue;
						}

						if (fd_arr[index] != -1&& FD_ISSET(fd_arr[index], &fds))
						{
							// 有客户端发送消息
							char buf[_BUF_SIZE_];
							memset(buf, '\0', sizeof(buf));

							ssize_t size = read(fd_arr[index], buf,sizeof(buf) );
							if (size == 0)
							{
								printf("remote client close\n" );
								close(fd_arr[index]);
								//printf("%d is close\n", fd_arr[index]);
								// 清除 fds中相应的文件描述符
								FD_CLR(fd_arr[index], &fds);
								remove_fd_arr(fd_arr[index]);
							}
							else
							{
								print_msg(fd_arr[index],buf );
							}
							
						}
					}
				}
		}
		
		
	}


}


int main()
{
	select_server();
	return 0;
}

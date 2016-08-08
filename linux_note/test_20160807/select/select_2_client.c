/*************************************************************************
	> File Name: select_2_client.c
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月08日 星期一 16时09分06秒
 ************************************************************************/
/* select_2 的客户端*/
#include<stdio.h>
#include <string.h>
       #include <sys/types.h>          /* See NOTES */
       #include <sys/socket.h>
       #include <netinet/in.h>
       #include <arpa/inet.h>
#include <stdlib.h>



void usage(const char* arg)
{
	printf("please enter : %s [IP] [PORT]\n",arg );
}

int select_client(char *ip, int port)
{
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0)
	{
		perror("create socket error");
		return 1;
	}

	struct sockaddr_in server;
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(ip);
	server.sin_port = htons(port);

	if (connect(fd, (struct sockaddr*)&server, sizeof(server)) < 0)
	{
		perror("connect error");
		return 2;
	}

	char buf[1024];
	while (1)
	{
		memset(buf, '\0', sizeof(buf));
		printf("please enter: ");
		fflush(stdout);
		fgets(buf, sizeof(buf) - 1, stdin);
		printf("buf is: %s\n", buf);
		int ret = send(fd, buf, strlen(buf) + 1, 0);
		if (ret < 0)
		{
			perror("send msg error\n");
		}
	}

	close(fd);
}

int main(int argc ,char* argv[])
{
	if (argc != 3)
	{
		usage(argv[0]);
		return 44;
	}

	int port = atoi(argv[2]);
	select_client(argv[1],port);

	return 0;
}

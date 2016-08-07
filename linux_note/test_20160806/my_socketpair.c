/*************************************************************************
	> File Name: my_socketpair.c
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月06日 星期六 10时23分29秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/socket.h>

int main()
{
	int sv[2];// 文件描述符
	if (socketpair(AF_LOCAL, SOCK_STREAM, 0, sv) < 0)
	{
		perror("socketpair");
		return 0;
	}

	pid_t id = fork();

	if (id == 0)
	{
		// child 
		close(sv[0]);
	const char *msg = "I am child";
	char buf[1024];
	while (1)
	{
		write(sv[1], msg, strlen(msg));
		memset(buf, 0, sizeof(buf));
		ssize_t _s = read(sv[1], buf, sizeof(buf) - 1);
		if (_s > 0)
		{
//			buf[_s] = '\0';
			printf("%d father->child: %s\n",_s, buf);
		}
		else if (_s == 0)
		{
			printf("child wait father...\n");
		}
		else
		{
			exit(1);
		}
		sleep(2);
	}
	}
	else
	{
		//father
		close(sv[1]);// 只要 和 child 不一样就行
		char buf[1024];
		while (1)
		{
		   memset(buf, 0, sizeof(buf));
          	read(sv[0], buf, sizeof(buf) - 1);
          	printf("child -> father: %s\n", buf);
          	strcpy(buf, "I am father");
         int sz = write(sv[0], buf, strlen(buf));
         //int sz = write(sv[0], buf, sizeof(buf) - 1); // error sizeof(buf)
		 printf("%d\n", sz);
		}
	}
}

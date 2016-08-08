/*************************************************************************
	> File Name: select_1.c
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月08日 星期一 00时35分49秒
 ************************************************************************/

/* select 检测标准输入输出*/
#include<stdio.h>
#include <string.h>
#include <sys/select.h>

int main()
{
	fd_set read_set;
	fd_set write_set;
	FD_ZERO(&read_set);
	FD_ZERO(&write_set);

	int read_fd = 0;
	int write_fd = 1;
	int max_fd = 2;

	char buf[1024];
	while (1)
	{
		struct timeval timeout= {3,0};
		FD_SET(read_fd, &read_set);
		FD_SET(write_fd, &write_set);
		int ret = select(max_fd + 1 , &read_set, &write_set, NULL, &timeout);// 除了第一个参数  后面4个 都是 输入-输出型参数
		switch(ret)
		{
			case -1:
				perror("select");
				return 1;
			case 0:
				printf("select timeout\n");
				break;
			default:
				{
					if (FD_ISSET(read_fd,& read_set ))
					{
						memset(buf, '\0', sizeof(buf));
						gets(buf);
						if (!strncmp(buf, "quit", 4))
						{
							return 0;
						}
						printf("read_fd: %s\n", buf);
					}

					if (FD_ISSET(write_fd, &write_set))
					{
						strcpy(buf, "output buffer is ok");
						puts(buf);
						sleep(3);
					}
				}
		}
	}

	return 0;
}


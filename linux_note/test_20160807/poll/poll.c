/*************************************************************************
	> File Name: poll.c
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月08日 星期一 20时02分18秒
 ************************************************************************/

#include<stdio.h>
#include <poll.h>
#include <string.h>


int mypoll()
{
	struct pollfd poll_set[2];
	//struct pollfd poll_set[1];
	//read
	poll_set[0].fd = 0;
	poll_set[0].events = POLLIN;
	poll_set[0].revents = 0;
	
	// write
	 poll_set[1].fd = 1;
	 poll_set[1].events = POLLOUT;
	 poll_set[1].revents = 0;
	
	int timeout = 3000;
	char buf[1024];

	while (1)
	{
		 switch(poll(poll_set, 2, timeout))
	//	switch(poll(poll_set, 1, timeout))
		{
			case -1:
				printf("poll error\n");
				return 1;
				break;
			case 0:
				printf("poll timeout\n");
				break;
			default:
				if (poll_set[0].revents & POLLIN)
				{
					memset(buf, '\0', sizeof(buf));
					printf("poll get \n");
					fgets(buf, sizeof(buf) - 1, stdin);
					printf("msg is: %s\n", buf);

				}

				if(poll_set[1].revents & POLLOUT)
				{
					printf("pollout is ok\n");
					sleep(1);
				}
				
				break;
		}
	}
	return 0;
}

int main()
{
	mypoll();
	return 0;
}

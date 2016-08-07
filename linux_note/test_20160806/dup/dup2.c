/*************************************************************************
	> File Name: dup2.c
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月07日 星期日 23时58分36秒
 ************************************************************************/

#include<stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



int main()
{
	int fd = open("./log", O_CREAT|O_RDWR);
	if (fd < 0)
	{
		perror("open");
		return fd;
	}

	close(1);

	int ret = dup2(fd, 1); // fd->1
	
	char buf[1024];
	while (1)
	{
		memset(buf, '\0', sizeof(buf));
		fgets(buf, sizeof(buf) - 1, stdin);
		if (strncmp(buf, "quit", 4) == 0)
		{
			break;
		}
		printf("%s", buf);
		fflush(stdout);
	}
	close(fd);
	return 0;
}

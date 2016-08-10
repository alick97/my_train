/*************************************************************************
	> File Name: fcntl.c
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月09日 星期二 23时22分47秒
 ************************************************************************/

#include<stdio.h>
       #include <unistd.h>
       #include <fcntl.h>
#include <string.h>


// 设置文件描述符号 不阻塞

int set_noblock(int fd)
{
	int fl = fcntl(fd, F_GETFL);// 获取 原来文件描述符的 状态
	if (fl < 0)
	{
		perror("fcntl F_GETFL ");
		return 1;
	}

	if (fcntl(fd, F_SETFL, fl | O_NONBLOCK) < 0) // 设置为 不阻塞状态
	{
		perror("fcntl F_SETFL");
		return 2;
	}
}

int myfcntl()
{
	set_noblock(0);
	char buf[10];
	while (1)
	{
		memset(buf, '\0', sizeof(buf));
		int ret = read(0, buf, sizeof(buf) - 1);
		sleep(1);
		printf("%s, ret: %d\n", buf, ret);
	}
}

int main()
{
	myfcntl();
	return 0;
}

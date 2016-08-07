/*************************************************************************
	> File Name: dup.c
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月07日 星期日 17时05分17秒
 ************************************************************************/

#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>




//int main()
//{
//	char buf[1024];
//	read(0, buf, sizeof(buf) - 1);
//	close(1);
//	int fd = open("./log", O_CREAT|O_RDWR, 0666);
//	printf("%d--------%s",fd, buf); //  原本是打印到标准输出 现在 是 文件fd
//	return 0;
//}


int main()
{
	int fd = open("./log", O_CREAT | O_RDWR,0666);
	if (fd < 0)
	{
		perror("open");
		return 1;
	}

	close(1);// 关闭标准输出

	int new_fd = dup(fd);

	if (new_fd == -1)
	{
		perror("dup");
		return 2;
	}

	close(fd);

	char buf[1024];

	while (1)
	{
		memset(buf, '\0', sizeof(buf));
		fgets(buf, sizeof(buf), stdin);
		if (strncmp("quit", buf, 4) == 0)
		{
			break;
		}
		
		printf("%s", buf);// 打到文件 中
		fflush(stdout);
	}
	close(new_fd);

	return 0;
}

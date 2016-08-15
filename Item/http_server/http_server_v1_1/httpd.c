/*************************************************************************
	> File Name: httpd.c
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月09日 星期二 16时37分37秒
 ************************************************************************/

#include<stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>


#define _SIZE_ 1024
//#define _DEBUG_
void usage(const char* proc)
{
	printf("Usage: %s [ip] [port]\n", proc);
}


static int startup(const char* _ip, int _port)
{
	int sock = socket(AF_INET,SOCK_STREAM, 0) ;
	if (sock < 0)
	{
		perror("socket");
		exit(2);
	}
      int op = 1;
	  // 消除2倍的MSL时间（报文最长生存时间）
	  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,&op, sizeof(int));

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(_port);
	local.sin_addr.s_addr = inet_addr(_ip);


	if (bind(sock,(struct sockaddr*)&local, sizeof(local)) < 0)
	{
		perror("bind");
		exit(3);
	}

	if (listen(sock, 5) < 0)
	{
		perror("listen ");
		exit(4);
	}

	return sock;
}

static void echo_errno(int sock)
{
	
}

static int get_line(int sock, char buf[], int len)
{
	if (buf == NULL || len < 0)
	{
		return -1;
	}

	char c = '\0';
	int n = 0;
	int i = 0;
	while ((i < len - 1) && c != '\n')
	{
		n = recv(sock, &c, 1, 0);
		if (n > 0)
		{
			// 转化 \r     \n      \r\n   为 \n
			if (c == '\r')
			{
				n = recv(sock, &c, 1, MSG_PEEK);// 向前读一个数据 但是不从sock中拿走
				if (n > 0 && c == '\n') // \r\n
				{
					recv(sock, &c, 1, 0);// 取出\n
				}
				c = '\n';
			}
			buf[i++] = c;
		}
		else
		{
			c  = '\n'; // 读取失败
		}
	}
	buf[i] = '\0';
	return i;
}
// 静态网页  文本等的处理
static void echo_www(int sock,const char* path, ssize_t size)
{
	int fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		echo_errno(sock);
		return;
	}

	printf("get a new client: %d -> %s \n", sock, path);

	char status_line[_SIZE_];
	sprintf(status_line, "HTTP/1.0 200 OK\r\n\r\n");// 发送 回应行 和 空行 之间GET没有参数 参数 在url中
	send(sock, status_line, strlen(status_line), 0);

	/////////////////////////////////////////////////////
	//   sendfile 将fd拷贝到 sock  直接在内核态完成  不许要经历用户态 切换 【高效】
	if (sendfile(sock, fd, NULL, size) < 0) // 发送文件内容 回应内容 
	{
		echo_errno(sock);
		return;
	}

	close(fd);
	close(sock);	
}
	
static clear_header(int sock) // 清除 请求行 和  空行   直接到达 内容部分
{
	int ret = 0;
	char buf[_SIZE_];
	do 
	{
		ret = get_line(sock, buf, sizeof(buf));
	}while ((ret > 0) && (strcmp(buf, "\n") != 0));
}

static void exec_cgi(int sock, const char *method, const char *path, const char *query_string )
{
	char buf[_SIZE_];
	int content_length = -1;// 内容长度  方便获取内容  
	int ret = -1;
	int cgi_input[2];
	int cgi_output[2];
	char method_env[_SIZE_];
	char query_string_env[_SIZE_];
	char content_length_env[_SIZE_];

	printf("[exec_cgi ]method : %s \n", method);

	if (strcasecmp(method, "GET") == 0)
	{
		clear_header(sock);
	}
	else // POST
	{
		do
		{
			ret = get_line(sock, buf, sizeof(buf));
			if (strncasecmp(buf, "Content-Length: ", 16) == 0)
			{
				content_length = atoi(&buf[16]);
				// break               不用 break  即把参数Content-Length获取  又把  空行删除
			}
		}while ((ret > 0) && strcmp(buf, "\n") != 0);

		if (content_length == -1)
		{
			echo_errno(sock);
			return;
		}
	}

	sprintf(buf, "HTTP/1.0 200 OK\r\n\r\n");
	send(sock, buf, strlen(buf), 0);


	// 创建  父子进程之间的 通信管道 cgi_input子进程的读  cgi_output子进程的写 
	if (pipe(cgi_input) < 0)
	{
		echo_errno(sock);
		return;
	}

	if (pipe(cgi_output) < 0)
	{
		echo_errno(sock);
		return;
	}

	pid_t id = fork();
	if (id < 0)
	{
		echo_errno(sock);
		return ;
	}

	if (id == 0)// child
	{
		close(cgi_input[1]);
		close(cgi_output[0]);

		// ////////////////
		// 重定向 管道到  标准输入 和 输出     这样以后 printf()直接打到管道

		dup2(cgi_input[0], 0);
		dup2(cgi_output[1], 1);

		sprintf(method_env, "REQUEST_METHOD=%s", method);
		putenv(method_env);// 注册环境变量 这样 execl 执行二进制程序时时 获取这些参数方便getenv
		
		// GET 要得 参数 在请求字段  中  环境变量注册 quer_string_env
		// post 要的参数在 内容中  所以要知道 内容什么时候截至（内容长度）所以 只要知道content_length_env 就可以了  

		if (strcasecmp(method, "GET") == 0)
		{
			sprintf(query_string_env, "QUERY_STRING=%s", query_string);
			putenv(query_string_env);
		}
		else // post
		{
			sprintf(content_length_env, "CONTENT_LENGTH=%d", content_length);
			putenv(content_length_env);
printf("%d-----------env\n", content_length);	
		}
		// 执行  二进制 程序
		execl(path,path,NULL);
		exit(1);
	}
	else // father
	{
		close(cgi_input[0]);
		close(cgi_output[1]);

		char c = '\0';
		int i = 0;
		printf("%s --fmethod\n", method);
		if (strcasecmp(method, "POST") == 0)
		{
			printf("--father here %d\n", content_length);
			for (; i < content_length; i++)
			{
				recv(sock, &c, 1, 0);
				printf("--%c ", c);
				fflush(stdout);
				write(cgi_input[1], &c, 1);// 给子进程 发过去 
			}
		}

		printf("\n");

		int ret = 0;
		while ((ret = read(cgi_output[0], &c, 1)) > 0)// 子进程退出 文件符号关闭 read读完文件结尾 返回0
		{
			send(sock, &c, 1, 0);// 父进程 负责向sock发送子进程的数据
		}

		waitpid(id, NULL, 0);
		close(sock);
	}
}


static void * accept_request(void *arg)
{
	int sock = (int)arg;
	char buf[_SIZE_];

	char method[_SIZE_/10];
	char url[_SIZE_];
	char path[_SIZE_];

	memset(buf, '\0', sizeof(buf));
	memset(buf, '\0', sizeof(method));
	memset(buf, '\0', sizeof(url));
	memset(buf, '\0', sizeof(path));

	int cgi = 0;
	int ret = -1;
	char *query_string = NULL; // 数据参数
	int len = sizeof(buf) / sizeof(buf[0]);
#ifdef _DEBUG_
	do 
	{
		// http 请求 报文 按行存储
		ret = get_line(sock, buf, len);
		printf("%s", buf);
		fflush(stdout);
	} while (ret > 0 && strcmp(buf, "\n") != 0);
#endif 

	ret = get_line(sock, buf, len); // 获取请求行
printf("line:   %s\n", buf);	
	if (ret < 0)
	{
		echo_errno(sock);
		return (void*)1;
	}

	// GET / HTTP/1.0
	int i = 0; // method index
	int j = 0; // buf index

	// 请求行 包括   【方法(GET/POST)】【url】【HTTP/1.0(1.1)】
	// 获取方法 GET/POST
	while ((i < sizeof(method) - 1) && (j < sizeof(buf)) && (!isspace(buf[j])))
	{
		method[i] = buf[j];
		++i;
		++j;
	}
	method[i] = '\0';
	// strcasecmp 忽略大小写的比较
	if (strcasecmp(method, "GET") != 0 && strcasecmp(method, "POST") != 0)
	{
		echo_errno(sock);
		return (void*)2;
	}
	
	// 跳过空格
	while (j < sizeof(buf) && isspace(buf[j]))
	{
		j++;
	}

	i = 0;


	// 获取url url是除了域名 端口号之后的 /。。。
	while ((i < sizeof(url) - 1) && (j < sizeof(buf)) && (!isspace(buf[j])))
	{
		url[i++] = buf[j++];
	}

	url[i] = '\0';
	//GET  所传递的参数 在URL中， 从server的QUERY_STRING 中获取
	//POST 所传递的参数 在 数据包中 从server环境变量中CONTENT_LENGTH 环境变量中获取参数 数据的长度
	
	if (strcasecmp(method, "POST") == 0)
	{
		cgi = 1;
	}
	
	 if (strcasecmp(method, "GET") == 0)
	 {
		 query_string = url;
		 // 路径和数据参数 以？分隔 如 http:// baidu.com /s ?  k = v
		 while (*query_string != '\0' && *query_string != '?')
		 {
			 ++query_string;
		 }

		 if(*query_string == '?') // GET 带参数 需要进一步处理参数
		 {
			 cgi = 1;
			 *query_string++ = '\0';
		 }
	 }

	 // 没指定具体网页 加默认网页 和 根文件夹（安全考虑）
	 sprintf(path, "httpdoc%s", url);
	 if (path[strlen(path) - 1] == '/')
	 {
		strcat(path, "index.html");
	 }


	 // method , query_string, cgi, path
	 struct stat st;
	 if (stat(path, &st) < 0) // 测文件在不在
	 {
		 echo_errno(sock);
		 return (void*)3;
	 }
	 else
	 {
		 if (S_ISDIR(st.st_mode))// 测是不是 文件夹
		 {
			 strcat(path, "/index.html");
		 }
		 else if( (st.st_mode & S_IXUSR) ||\
				(st.st_mode & S_IXGRP) ||\
				(st.st_mode & S_IXOTH))
				//   查看cgi执行权限
		 {
				cgi = 1;
		 }
		 else
		 {}

		 if (cgi)
		 {
			  exec_cgi(sock, method, path,  query_string);
		 }
		 else
		 {
			clear_header(sock); // 
			echo_www(sock, path, st.st_size);
		 }
	 }
}


int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		printf("Usage : %s [ip] [port]\n", argv[0]);
		exit(1);
	}
	
	int listen_sock = startup(argv[1], atoi(argv[2]));

	struct sockaddr_in peer;
	socklen_t len = sizeof(peer);

	int done = 0;

	while (!done)
	{
		int new_sock = accept(listen_sock , (struct sockaddr*)&peer, &len);
		if (new_sock < 0)
		{
			perror("accept");
			exit(2);
		}
		printf("client sock: %s:%d\n", inet_ntoa(peer.sin_addr), ntohs(peer.sin_port));

		pthread_t tid;
		pthread_create(&tid, NULL, accept_request, (void *)new_sock);
		pthread_detach(tid);
	}

	return 0;
}





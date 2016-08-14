/*************************************************************************
	> File Name: cgi_math.c
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月14日 星期日 01时35分49秒
 ************************************************************************/

#include<stdio.h>
#include <string.h>
#include <stdlib.h>


static void mymath(char *arg)
{
	// data1=100&data2=200
	char *data[3];
	data[2] = NULL;
	int i = 1;
	char *end = arg + strlen(arg) - 1;
	while (end > arg)
	{
		if (*end == '=')
		{
			data[i--] = end + 1;
		}

		if (*end == '&')
		{
			*end = '\0';
		}
		end--;
	}

//	printf("<html>\n");
//	printf("<h1>");
//
//
//	printf("</h1>");
//	printf("<body>");
	printf("nihao ");
//	printf("%s ", arg );
//
printf("%s + %s = %d", data[0], data[1], atoi(data[0]) + atoi(data[1]));
//	printf("</body>");
//	printf("</html>\n");

}


int main()
{
	char method[1024];
	char arg[1024];
	char content_len[1024];
	int len = -1;
	if (getenv("REQUEST_METHOD"))
	{
		strcpy(method, getenv("REQUEST_METHOD"));
	}

	if (strcasecmp(method,"GET") == 0 )
	{
		if (getenv("QUERY_STRING"))
		{
			strcpy(arg, getenv("QUERY_STRING"));

			printf("-----------%s--get\n", arg);
		}
	}
	else // post
	{
		if (getenv("CONTENT_LENGTH"))
		{
			strcpy(content_len, getenv("CONTENT_LENGTH"));
			len = atoi(content_len);
			printf("%d --len\n",len);
		}
		////////////////////////   读取name：value值
		int i = 0;
		for (; i < len; i++)
		{
			read(0, &arg[i], 1);
			printf("%c-", arg[i]);
		}

		arg[i] = '\0';
		printf("%s----------", arg);
	}
	mymath(arg);
	return 0;
}


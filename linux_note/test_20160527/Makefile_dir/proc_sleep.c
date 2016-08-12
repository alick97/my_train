/*************************************************************************
	> File Name: proc_sleep.c
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2016年05月27日 星期五 21时11分47秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>

void proc()
{
	const size = 102;
	char arr[size];
	char state[] = "\\|/-";
	memset(arr,'\0',sizeof(arr));
	int count = 0;
	while (count < size - 1)
	{
		arr[count] = '#';
		printf("[%-100s][%d%%][%c]\r",arr,count++,state[count%4]);
		//fflush(stdout);
		sleep(1);
	}
	printf("\n");
}


int main()
{
	proc();
	return 0;

}

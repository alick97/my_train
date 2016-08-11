#include<stdio.h>
#define MAX_NUM  100

void fun()
{
	int i = 0;
	while (i < 100 )
	{
		printf("%d\n",i);
		i++;
	}
}

int main()
{
	
	int count = 0;
	int i = 0;
	while (i <= MAX_NUM)
	{
		count += i;
		i++;
	}
	
	printf("%d\n", count);

	fun();

	return; 
}

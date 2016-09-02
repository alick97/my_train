/*************************************************************************
	> File Name: print_matrix.cpp
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年09月02日 星期五 22时57分49秒
 ************************************************************************/

#include <iostream>
using namespace std;
#include <stdio.h>

void _print_matrix(int **arr,int  n, int start);

int index = 1;
void print_matrix(int n)
{
    index = 1;
	if (n < 1)
	{
		return ;
	}

	int **arr = new int*[n];
    int i = 0;
	for (i = 0; i < n; i++)
	{
		arr[i] = new int[n];
	}
///////////////////////////////////
    int start = 0;
	for (; start * 2 < n; start++)
	_print_matrix(arr, n, start);
///////////////////////////////////

for (i = 0; i < n; i++)
{
	int j;
	for (j = 0; j < n; j++)
	{
		printf("%3d ",arr[i][j]);
	}
	printf("\n");
}


	//////////////////////////
	for (i = 0; i < n; i++)
	{
		delete[] arr[i];
	}

	delete[] arr;
}


void w(int *pn)
{
	//printf("n ");
	*pn = index++;
}

void _print_matrix(int **arr,int  n, int start)
{
	int rows = n - 1 - start;
	int cols = rows;
    int i = start;
	// top
	for (i = start; i <= cols; i++)
	{
		w(&arr[start][i]);
	}
	
	// right    morn than  one rows 
    if (rows > start)
	{
		for (i = start + 1; i <= rows; i++)
		{
			w(&arr[i][cols]);
		}
	}

	// bottom       more than one cols and more than one cols 4*4
	if (rows > start && cols > start)
	{
		for (i = cols - 1; i >= start; i--)
		{
			w(&arr[rows][i]);
		}
	}

	// left       more than 2 rows and 1 cols
	if (start +1 < rows && cols > start)
	{
		for (i = rows - 1; i >  start; i--)
		{
			w(&arr[i][start]);
		}
	}
}

void test()
{
	int i = -1;
	for(; i < 5; i++)
	{
		print_matrix(i);
		printf("\n-------------------------\n");
	}
}


int main()
{
    test();
	return 0;
}

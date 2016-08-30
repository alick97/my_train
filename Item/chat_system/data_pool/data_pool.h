/*************************************************************************
	> File Name: data_pool.h
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月24日 星期三 21时47分46秒
 ************************************************************************/
#pragma once
#include<iostream>
#include <vector>
#include <string.h>
#include <semaphore.h>

class data_pool
{
	public:
		data_pool(int size=128);
		void get_data(std::string &out);
		void put_data(const std::string &in);
		~data_pool();
	private:
		std::vector<std::string> _pool;
		int _cap;
		int _space_step;
		int _data_step;
		sem_t _space_sem;
		sem_t _data_sem;
};

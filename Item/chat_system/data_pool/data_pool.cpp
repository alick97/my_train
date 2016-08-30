/*************************************************************************
	> File Name: data_pool.cpp
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月24日 星期三 21时47分51秒
 ************************************************************************/

#include "data_pool.h"

data_pool::data_pool(int size)
	:_cap(size)
	 ,_pool(size)
{
	_space_step = 0;
	_data_step = 0;
	sem_init(&_space_sem, 0, _cap);
	sem_init(&_data_sem, 0, 0);
}
void data_pool::get_data(std::string &out)
{
	sem_wait(&_data_sem);
	// pthread_mutex_lock(); //?这里服务器进程就一个 就不用加锁了
	out = _pool[_data_step++];
	_data_step %= _cap;
	// pthread_mutex_unlock();
	sem_post(&_space_sem);
}

void data_pool::put_data(const std::string &in)
{
	sem_wait(&_space_sem);
	_pool[_space_step++] = in;
	_space_step %= _cap;
	sem_post(&_data_sem);
	
}
data_pool::~data_pool()
{
	sem_destroy(&_space_sem);
	sem_destroy(&_data_sem);
}

/*************************************************************************
	> File Name: cwindow.cpp
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月25日 星期四 00时42分18秒
 ************************************************************************/
#include "cwindow.h"

pthread_mutex_t mutex;

cwindow::cwindow()
{
	initscr();// screen
	header = NULL;
	output = NULL;
	userlist = NULL;
	input = NULL;
pthread_mutex_init(&mutex, NULL);
}

cwindow::~cwindow()
{
	pthread_mutex_destroy(&mutex);
	delwin(header);
	delwin(output);
	delwin(userlist);
	delwin(input);
	endwin();
}

void cwindow::create_header()
{
	int _h = LINES/5;
	int _w = COLS;
	int _y = 0;
	int _x = 0;
	header = newwin(_h, _w, _y, _x);
	myflush(header);
}
void cwindow::create_output()
{
	int _h = (LINES*3)/5;
	int _w = (COLS*3)/4;
	int _y = LINES/5;
	int _x = 0;
	output = newwin(_h, _w, _y, _x);
	myflush(output);
}
void cwindow::create_userlist()
{
	// LINES 最大的窗体的高    COLS最大的窗体的宽
	int _h = (LINES*3)/5;
	int _w = COLS/4;
	int _y = LINES/5;
	int _x = (COLS*3)/4;
	userlist = newwin(_h, _w, _y, _x);
	myflush(userlist);
}
void cwindow::create_input()
{
	int _h = LINES/5;
	int _w = COLS;
	int _y = (LINES*4)/5;
	int _x = 0;
	input = newwin(_h, _w, _y, _x);
	myflush(input);
}

 void cwindow::myflush(WINDOW* win)
{
	// mutex_lock
	// 标准输出 是临界资源  建议加锁
	pthread_mutex_lock(&mutex);
	box(win, 0, 0);////////////
	wrefresh(win);
	// mutex_unlock
	pthread_mutex_unlock(&mutex);
}

void cwindow::put_str_to_win(WINDOW *win, int _y, int _x, std::string &str)
{
	mvwaddstr(win, _y, _x, str.c_str());
}

std::string cwindow::get_str_from_win(WINDOW *win)
{
    char buf[_SIZE_];
	memset(buf, '\0', sizeof(buf));
	wgetnstr(win, buf, sizeof(buf) - 1);
	return buf;
}

void cwindow::clear_win_line(WINDOW *win, int begin, int num)
{
	while (num-- > 0)
	{
		wmove(win, begin++, 0);
		wclrtoeol(win);
	}
}
//
//int main()
//{
//	cwindow win;
//	win.create_header();
//	sleep(2);
//	win.myflush(win.header);
//	sleep(2);
//
//	win.create_output();
//	sleep(2);
//	win.myflush(win.output);
//	sleep(2);
//
//
//	win.create_userlist();
//	sleep(2);
//	win.myflush(win.userlist);
//	sleep(2);
//
//
//	win.create_input(); 
//	sleep(2);
//	win.myflush(win.input ); 
//	sleep(2);
//
//	return 0;
//}

/*************************************************************************
	> File Name: cwindow.h
	> Author: alick
	> Mail: alick97@outlook.com 
	> Created Time: 2016年08月25日 星期四 00时42分13秒
 ************************************************************************/
#pragma once
#include "comm.h"
#include<iostream>
#include <string.h>
#include <ncurses.h>

extern pthread_mutex_t mutex;
class cwindow
{
	public:
		cwindow();
		~cwindow();

		void create_header();
		void create_output();
		void create_userlist();
		void create_input();

		void clear_win_line(WINDOW *win, int begin, int num);
		static void myflush(WINDOW* win);
		void put_str_to_win(WINDOW *win, int _y, int _x, std::string &str);
		std::string get_str_from_win(WINDOW *_win);
	public:
		WINDOW *header;
		WINDOW *output;
		WINDOW *userlist;
		WINDOW *input;
};

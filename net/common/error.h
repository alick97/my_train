#ifndef __ERROR_H__
#define __ERROR_H__
#include "unp.h"
#include <stdarg.h>
#include <syslog.h>

void err_ret(const char *fmt, ...);
void err_sys(const char *fmt, ...);
void err_dump(const char *fmt, ...);
void err_msg(const char *fmt, ...);
void err_quit(const char *fmt, ...);

#endif
#ifndef __WRAPSOCKET__H__
#define __WRAPSOCKET__H__
#include "unp.h"
#include "error.h"

int Socket(int family, int type, int protocol);
int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int Listen(int sockfd, int backlog);
int Accept(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len);
ssize_t Write(int fildes, const void *buf, size_t nbyte);
int Close(int fd);
#endif
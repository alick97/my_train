#ifndef __UNP_H__
#define __UNP_H__

#include "config.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/un.h>

#ifdef HAVE_SYS_SELECT_H
#include <sys/select.h>
#endif

#ifdef HAVE_POLL_H
#include <poll.h>
#endif

#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif

#ifdef HAVE_SYS_IOCTL_H
#include <sys/ioctl.h>
#endif

#ifdef HAVE_SYS_FILIO_H
#include <sys/filio.h>
#endif

#ifdef HAVE_SYS_SOCKIO_H
#include <sys/sockio.h>
#endif

#ifdef HAVE_PTHREAD_H
#include <pthread.h>
#endif

#ifdef __osf__
#undef recv
#undef send
#define recv(a, b, c, d) recvfrom(a, b, c, d, 0, 0)
#define send(a, b, c, d) sendto(a, b, c, d, 0, 0)
#endif

#ifndef INADDR_NONE
#define INADDR_NONE 0xffffffff
#endif

#ifndef SHUT_RD
#define SHUT_RD 0
#define SHUT_WR 1
#define SHUT_RDWR 2
#endif

#ifndef INET_ADDRSTRLEN
#define INET_ADDRSTRLEN 16 /* "ddd.ddd.ddd.ddd\0" */
#endif

#ifndef INET6_ADDRSTRLEN
#define INET6_ADDRSTRLEN 46 /* max size of IPv6 address string */
#endif

#ifndef HAVE_BZERO
#define bzero(ptr, n) memset(ptr, 0, n)
#endif

#ifndef HAVE_GETHOSTBYNAME2
#define gethostbyname2(host, family) gethostbyname((host))
#endif

// /* The structure  returned by recvfrom_flags() */
// struct in_pktinfo {
    // struct in_addr ipi_addr; /* dst IPv4 address */
    // int ipi_ifindex; /* received interface index */
// };

#ifndef CMSG_LEN
#define CMSG_LEN(size) (sizeof(struct cmsghdr) + (size))
#endif

#ifndef CMSG_SPACE
#define CMSG_SPACE(size) (sizeof(struct cmsghdr) + (size))
#endif

#ifndef SUN_LEN
#define SUN_LEN(su) \
    (sizeof(*(su)) - sizeof((su)->sun_path) + strlen((su)->sun_path))
#endif

#ifndef AF_LOCAL
#define AF_LOCAL AF_UNIX
#endif

#ifndef PF_LOCAL
#define PF_LOCAL PF_UNIX
#endif

#ifndef INFTIM
#define INFTIM (-1)
#ifdef HAVE_POLL_H
#define INFTIM_UNPH
#endif
#endif

#define LISTENQ 1024
#define MAXLINE 4096
#define MAXSOCKADDR 128
#define BUFFSIZE 8192

#define SERV_PORT 9877
#define SERV_PORT_STR "9877"
#define UNIXSTR_PATH "/tmp/unix.str"
#define UNIXDG_PATH "/tmp/unix.dg"

#define SA struct sockaddr
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP| S_IROTH)
#define DIR_MODE (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)

typedef void Sigfunc(int);

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

#ifndef HAVE_ADDRINFO_STRUCT
#include "addrinfo.h"
#endif

// #ifndef HAVE_IF_NAMEINDEX_STRUCT
// struct if_nameindex {
    // unsigned int if_index; /* 1,2,... */
    // char *if_name;
// };
// #endif

// #ifndef HAVE_TIMESPEC_STRUCT
// struct timespec {
    // time_t tv_sec; /* seconds */
    // long tv_nsec; /* and nanoseconds */
// };
// #endif

/* prototypes for our own library functions */
int sock_bind_wild(int sockfd, int family);
int sock_cmp_addr(const struct sockaddr *sa1, const struct sockaddr *sa2,
	socklen_t salen);
int sock_cmp_port(const struct sockaddr *sa1, const struct sockaddr *sa2,
	              socklen_t salen);
/* Read n bytes from a descriptor. */
ssize_t readn(int fd, void *vptr, size_t n);
/* Write n butes to a descriptor. */
ssize_t writen(int fd, const void * vptr, size_t n);

/* wrap fun */
int Sock_bind_wild(int sockfd, int family);

int Socket(int family, int type, int protocol);
int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int Listen(int sockfd, int backlog);
int Accept(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len);
ssize_t Write(int fildes, const void *buf, size_t nbyte);
int Close(int fd);

void err_ret(const char *fmt, ...);
void err_sys(const char *fmt, ...);
void err_dump(const char *fmt, ...);
void err_msg(const char *fmt, ...);
void err_quit(const char *fmt, ...);

#endif
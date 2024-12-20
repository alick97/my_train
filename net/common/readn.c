#include "unp.h"

/* Read n bytes from a descriptor. */
ssize_t readn(int fd, void *vptr, size_t n) {
    ssize_t nleft;
    ssize_t nread;
    char *ptr;

    ptr = vptr;
    nleft = n;
    while (nleft > 0) {
        if ((nread = read(fd, ptr, nleft)) < 0) {
            if (errno == EINTR) {
                nread = 0; /* And call read() again. */
            } else {
                return -1;
            }
        } else if (nread == 0) {
            break;  /* EOF */
        }

        nleft -= nread;
        ptr += nread;
    }
    
    return n - nleft;  /* Return >= 0 */
}

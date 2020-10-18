#include "unp.h"

ssize_t readline1(int fd, void *vptr, size_t maxlen) {
    ssize_t n, rc;
    char c, *ptr;

    ptr = vptr;

    for (n = 1; n < maxlen; n++) {
        again:
            if ((rc = read(fd, &c, 1)) == 1) {
                *ptr++ = c;
                if (c == '\n') {
                    break;
                }
            } else if (rc == 0) {
                if (n == 1) {
                    return 0;  /* EOF, no data read. */
                } else {
                    break;  /* EOF, some data was read. */
                }
            } else {
                if (errno == EINTR) {
                    goto again;
                }

                return -1;  /* error, errno set by read(). */
            }
    }
    *ptr = 0;
    return n;
}
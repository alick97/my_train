#include	"unp.h"

int sock_cmp_port(const struct sockaddr *sa1, const struct sockaddr *sa2,
	              socklen_t salen) {
	if (sa1->sa_family != sa2->sa_family)
		return -1;

	switch (sa1->sa_family) {
        case AF_INET: {
            return( ((struct sockaddr_in *) sa1)->sin_port ==
                    ((struct sockaddr_in *) sa2)->sin_port);
	}

    /* TODO: Support ipv6. */
    return (-1);
	}
}

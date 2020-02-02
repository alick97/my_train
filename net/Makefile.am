bin_PROGRAMS = daytime_client daytime_server
AM_CPPFLAGS = -I$(srcdir) -I$(srcdir)/common
COMMON_SOURCES = common/error.c common/addrinfo.h common/unp.h \
    common/wrapsocket.c common/wrapsocket.h
daytime_client_SOURCES = chapter_1/daytime_client.c $(COMMON_SOURCES)
daytime_server_SOURCES = chapter_1/daytime_server.c $(COMMON_SOURCES)

ROOT_PATH=$(shell pwd)
BIN=httpd
CC=gcc
SRC=httpd.c
OBJ=$(SRC:.c=.o)#.c->.o
LIB=-lpthread
FLAGS=#-D_DEBUG_
CGI=$(ROOT_PATH)/httpdoc/cgi $(ROOT_PATH)/mysql_connect

.PHONY:all
all:$(BIN) cgi
$(BIN):$(OBJ)
	$(CC) -o $@ $^ $(LIB)
%.o:%.c
	$(CC) -c $< $(FLAGS)
##.PHONY:clean
#clean:
#	rm -f $(OBJ) $(BIN)
.PHONY:cgi
cgi:
	for name in `echo $(CGI)`;\
	do\
		cd $$name;\
		make;\
		cd -;\
	done

.PHONY:clean
clean:
	rm -rf *.o $(BIN) output
	for name in `echo $(CGI)`;\
		do\
		 cd $$name;\
		 make clean;\
		 cd -;\
	done

.PHONY:output
output:
	mkdir -p output/lib
	mkdir -p output/httpdoc/cgi
	mkdir -p output/httpdoc/image
	cp -r lib/*  output/lib 
	cp -f httpd output
	cp httpdoc/cgi/cgi_math output/httpdoc/cgi
	cp httpdoc/image/* output/httpdoc/image
	cp httpdoc/index.html output/httpdoc
	cp mysql_connect/cgi_insert output/httpdoc/cgi
	cp mysql_connect/cgi_select output/httpdoc/cgi
	cp mysql_connect/register_env.sh output/httpdoc/cgi

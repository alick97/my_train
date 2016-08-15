BIN_PATH=$(shell pwd)
BIN=httpd
CC=gcc
SRC=httpd.c
OBJ=$(SRC:.c=.o)#.c->.o
LDFLAGS=-lpthread
$(BIN):$(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) -g
%.o:%.c
	$(CC) -c $< -g
.PHONY:clean
clean:
	rm -f $(OBJ) $(BIN)
.PHONY:debug
debug:
	@echo $(SRC)
	@echo $(OBJ)


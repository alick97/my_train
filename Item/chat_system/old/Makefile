ROOT_PATH=$(shell pwd)
CC=g++
SERVER=$(ROOT_PATH)/udp_server
CLIENT=$(ROOT_PATH)/udp_client
COMM=$(ROOT_PATH)/comm
DATA_POLL=$(ROOT_PATH)/data_poll

SRC=$(shell ls $(ROOT_PATH)/*.cpp)
OBJ=$(SRC:.cpp=.o)

$(SERVER):$(OBJ)
	$(CC) -o $@ $^
%.o:%.cpp
	$(CC) -c $<

.PHONY:clean
clean:
	rm -rf *.o

.PHONY:debug
debug:
	@echo $(ROOT_PATH)
	@echo $(SRC)
	@echo $(OBJ)

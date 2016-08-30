ROOT_PATH=$(shell pwd)
DATA_POOL=$(ROOT_PATH)/../data_pool
COMMON=$(ROOT_PATH)/../common

CC=g++
SERVER=udp_server

SRC=$(shell ls *.cpp)
SRC+=$(shell cd $(DATA_POOL); ls *.cpp)
SRC+=$(shell cd $(COMMON); ls *.cpp)
OBJ=$(SRC:.cpp=.o)

LDFLAGS=-lpthread -ljsoncpp -static
INCLUDE=-I$(DATA_POOL) -I$(COMMON) -I$(ROOT_PATH)/../lib/include
LIB_PATH=-L$(ROOT_PATH)/../lib/lib

$(SERVER):$(OBJ)
	$(CC) -o $@ $^ $(LIB_PATH) $(LDFLAGS)
%.o:%.cpp
	$(CC) -c $< $(INCLUDE)
%.o:$(DATA_POOL)/%.cpp
	$(CC) -c $< $(INCLUDE)
%.o:$(COMMON)/%.cpp
	$(CC) -c $< $(INCLUDE)

.PHONY:clean
clean:
	rm -f $(SERVER) *.o

.PHONY:debug
debug:
	@echo $(ROOT_PATH)
	@echo $(SRC)
	@echo $(OBJ)


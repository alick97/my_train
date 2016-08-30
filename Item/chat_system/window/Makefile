ROOT_PATH=$(shell pwd)
INCLUDE=$(ROOT_PATH)/../common
cwindow:cwindow.o comm.o
	g++ -o $@ $^ -lcurses
cwindow.o:cwindow.cpp
	g++ -c  $^ -I $(INCLUDE)
comm.o:$(INCLUDE)/comm.cpp
	g++ -c  $^ -I$(INCLUDE)
.PHONY:clean
clean:
	rm -rf cwindow *.o
.PHONY:debug
	@echo $(ROOT_PATH)


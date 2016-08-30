ROOT_PATH=$(shell pwd)
INCLUDE=-I$(ROOT_PATH)/../lib/include
LIB=-L$(ROOT_PATH)/../lib/lib

udp_data:my_json.o udp_data.o
	g++ -o $@ $^ $(LIB) -ljsoncpp -static
%.o:%.cpp
	g++ -c $< $(INCLUDE)
.PHONY:clean
clean:
	rm -f *.o udp_data


test:test.o
	gcc -o test test.o
test.o:test.s
	gcc -c test.s -o test.o
test.s:test.i
	gcc -S test.i -o test.s
test.i:test.c
	gcc -E test.c -o test.i
#  #号为 注释
.PHONY:clean
clean: 
	#clean为伪目标
	rm -f test.o test.s test.i

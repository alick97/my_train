.PHONY: all
all: select_2 select_2_client
select_2:select_2.c
	gcc -o $@ $^
select_2_client:select_2_client.c
	gcc -o $@ $^
.PHONY:clean
clean:
	rm -rf select_2 select_2_client

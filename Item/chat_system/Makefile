ROOT_PATH=$(shell pwd)
CLIENT=$(ROOT_PATH)/client
SERVER=$(ROOT_PATH)/server
PLUGIN=$(ROOT_PATH)/plagin
ALL=$(CLIENT) $(SERVER)

.PHONY:output
output:
	@for i in `echo $(ALL)`;\
		do\
			cd $$i;\
			make;\
			cd -;\
	done
	@mkdir output
	@cp -f  $(SERVER)/udp_server output
	@cp -f $(CLIENT)/udp_client output
#	@cp -f $(PLUGIN)/server_ctl.sh output

.PHONY:clean
clean:
	@rm -rf output
	@for i in `echo $(ALL)`;\
		do\
			cd $$i;\
			make clean;\
			cd -;\
	    done

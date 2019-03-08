CC=gcc
objects = assignment_main.o time_check.o assignment_main_helpers.o
headers =  time_check.h 
assignment_main_helpers_headers = assignment_main_helpers.h 

all: assignment_daemon assignment_queue_server

assignment_daemon : $(objects)
	$(CC) -o assignment_daemon $(objects) -lrt

assignment_main.o : assignment_main.c $(assignment_main_helpers_headers)
	$(CC) -c assignment_main.c

time_check.o : time_check.c
	$(CC) -c time_check.c

assignment_main_helpers.o : assignment_main_helpers.c $(headers)
	$(CC) -c assignment_main_helpers.c


###################################################
assignment_queue_server: message_queue_server.o
	$(CC) -o assignment_queue_server message_queue_server.o -lrt

message_queue_server.o: message_queue_server.c
	$(CC) -c message_queue_server.c 



clean:
	rm assignment_daemon assignment_queue_server $(objects)
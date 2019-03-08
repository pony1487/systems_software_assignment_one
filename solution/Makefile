CC=gcc
objects = assignment_main.o time_check.o 
headers =  time_check.h  

all: assignment_daemon assignment_queue_server

assignment_daemon : $(objects)
	$(CC) -o assignment_daemon $(objects)

assignment_main.o : assignment_main.c $(headers)
	$(CC) -c assignment_main.c

time_check.o : time_check.c
	$(CC) -c time_check.c

assignment_queue_server: message_queue_server.o
	$(CC) -o assignment_queue_server message_queue_server.o

message_queue_server.o: message_queue_server.c
	$(CC) -c message_queue_server.c



clean:
	rm assignment_daemon assignment_queue_server $(objects)
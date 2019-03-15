CC=gcc
objects = assignment_main.o assignment_main_helpers.o

time_process_headers =  time_check.h 
time_process_objects =  time_check.o 

assignment_main_helpers_headers = assignment_main_helpers.h 

# Each process
all: assignment_daemon assignment_queue_server time_check_process log_change_process

assignment_daemon : $(objects)
	$(CC) -o assignment_daemon $(objects) -lrt

assignment_main.o : assignment_main.c $(assignment_main_helpers_headers)
	$(CC) -c assignment_main.c

assignment_main_helpers.o : assignment_main_helpers.c
	$(CC) -c assignment_main_helpers.c


# Below are the programs that are forked and execed from assignment_daemon
###################################################
assignment_queue_server: message_queue_server.o
	$(CC) -o assignment_queue_server message_queue_server.o -lrt

message_queue_server.o: message_queue_server.c
	$(CC) -c message_queue_server.c 

###################################################

time_check_process: time_check_process.o $(time_process_objects)
	$(CC) -o time_check_process time_check_process.o $(time_process_objects) -lrt

time_check_process.o : time_check_process.c $(time_process_headers)
	$(CC) -c time_check_process.c

time_check.o : time_check.c
	$(CC) -c time_check.c

###################################################

log_change_process: log_change_process.o
	$(CC) -o log_change_process log_change_process.o -lrt

log_change_process.o : log_change_process.c
	$(CC) -c log_change_process.c

clean:
	rm assignment_daemon assignment_queue_server time_check_process log_change_process $(objects) $(time_process_objects)
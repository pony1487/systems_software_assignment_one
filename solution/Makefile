CC=gcc
objects = assignment_main.o assignment_main_helpers.o

time_process_headers =  time_check.h 
time_process_objects =  time_check.o 

assignment_queue_server_objects = file_permissions.o #backup_transfer.o

assignment_main_helpers_headers = assignment_main_helpers.h 

# Each process
all: assignment_daemon assignment_queue_server time_check_process log_change_process backup_transfer_process

assignment_daemon : $(objects)
	$(CC) -o assignment_daemon $(objects) -lrt

assignment_main.o : assignment_main.c $(assignment_main_helpers_headers)
	$(CC) -c assignment_main.c

assignment_main_helpers.o : assignment_main_helpers.c
	$(CC) -c assignment_main_helpers.c


# Below are the programs that are forked and execed from assignment_daemon
###################################################
assignment_queue_server: message_queue_server.o file_permissions.o #backup_transfer.o
	$(CC) -o assignment_queue_server message_queue_server.o $(assignment_queue_server_objects)  -lrt

message_queue_server.o: message_queue_server.c 
	$(CC) -c message_queue_server.c

file_permissions.o : file_permissions.c file_permissions.h
	$(CC) -c file_permissions.c

#backup_transfer.o : backup_transfer.c backup_transfer.h
#	$(CC) -c backup_transfer.c

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

###################################################

backup_transfer_process: backup_transfer_process.o backup_transfer.o
	$(CC) -o backup_transfer_process backup_transfer_process.o backup_transfer.o -lrt

backup_transfer_process.o : backup_transfer_process.c backup_transfer.h
	$(CC) -c backup_transfer_process.c

backup_transfer.o : backup_transfer.c	
	$(CC) -c backup_transfer.c

clean:
	rm assignment_daemon assignment_queue_server time_check_process log_change_process backup_transfer_process $(objects) $(time_process_objects) $(assignment_queue_server_objects)

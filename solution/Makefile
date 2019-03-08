CC=gcc
objects = assignment_main.o time_check.o 
headers =  time_check.h 

assignment_daemon : $(objects)
	$(CC) -o assignment_daemon $(objects)

assignment_main.o : assignment_main.c $(headers)
	$(CC) -c assignment_main.c

time_check.o : time_check.c
	$(CC) -c time_check.c


clean:
	rm assignment_daemon $(objects)
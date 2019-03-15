/*
Multiple processes are forked and have the same parent. Each process does a particular task. The messeage queue is used to let each process know
of an event.
0:  assignment_queue_server
1:  time_check_process

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#include "assignment_main_helpers.h"



int main()
{
    int SIZE = 2;
    pid_t child_pids[SIZE];
    int num_of_children = SIZE;

    for(int i = 0; i < num_of_children; i++)
    {
        if((child_pids[i] = fork()) < 0)
        {
            perror("Error: failed to fork!\n");
            exit(EXIT_FAILURE);
        }
        else if(child_pids[i] == 0){

            if(i == 0)
            {
                //run message server
                char * argv_list[] = {"message_queue_server",NULL};
                execv("./assignment_queue_server",argv_list);
            }

            if(i == 1)
            {
                //run time check
                char * argv_list[] = {"time_check_process",NULL};
                execv("./time_check_process",argv_list);
            }                    
        }
    }

    int status;
    pid_t pid;
    while(num_of_children > 0)
    {   
        pid = wait(&status);
        printf("Child %d exited with status 0x%x\n",pid,status);
        num_of_children--;
    }

    return 0;
}

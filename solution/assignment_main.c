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
    //TO DO
    //https://stackoverflow.com/questions/876605/multiple-child-process
    //fork multiple children
    // pid_t pid;

    // pid = fork();

    // if(pid < 0)
    // {
    //     perror("Fork() error!\n");
    //     exit(EXIT_FAILURE);
    // }
    // else if(pid == 0)
    // {
    //     printf("child");
    //     char * argv_list[] = {"message_queue_server",NULL};
    //     execv("./assignment_queue_server",argv_list);
    // }
    // else if(pid > 0)
    // {
    //     printf("parent:\n");
    //     char * argv_list[] = {"time_check_process",NULL};
    //     execv("./time_check_process",argv_list);
    // }

    // printf("Back in assignment_main()\n");

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
                //exit(0);
            }

            if(i == 1)
            {
                //run time check
                char * argv_list[] = {"time_check_process",NULL};
                execv("./time_check_process",argv_list);
                //exit(0);

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>


#include "assignment_main_helpers.h"



int main()
{
    pid_t pid;

    pid = fork();

    if(pid < 0)
    {
        perror("Fork() error!\n");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0)
    {
        printf("child");
        char * argv_list[] = {"message_queue_server",NULL};
        //execv("./assignment_queue_server",argv_list);
    }
    else if(pid > 0)
    {
        printf("parent:\n");
    }
    

    return 0;
}

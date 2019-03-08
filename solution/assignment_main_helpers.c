#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <time.h>
#include "time_check.h"


void runTimeCheck()
{
    printf("runtTimeCheck() started....\n");
    while(1)
        {
        struct tm *current_time = get_current_time();
        int is_backup_time = check_backup_time(current_time);

        if(is_backup_time == 1)
        {
            printf("Backup!");
            break;
        }
    }
    
}

void testAssignmentMainHelpers()
{
    printf("testAssignmentMainHelpers\n");
}

void testServer()
{
    char queue_name[] = "/assignment_queue";
    printf("Testing message queue client\n");
    printf("Queue name: %s\n",queue_name);
    
    mqd_t mq;
    char buffer[1024];

    //open queue
    mq = mq_open(queue_name, O_WRONLY);

    printf("Send message to server (enter exit to quit\n");

    do{
        printf("$ ");
        fflush(stdout);

        memset(buffer,0,1024);
        fgets(buffer,1024,stdin);
        mq_send(mq,buffer,1024,0);

    }while(strncmp(buffer,"exit",strlen("exit")));
}
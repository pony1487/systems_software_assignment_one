/*
This process will be forked and exec from assignment_main
It will check if it is a particular time and then send that message to the message queue
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mqueue.h>
#include <syslog.h>

#include "time_check.h"


void runTimeCheck();
void testServer();

int main(int argc, char *argv[])
{

    runTimeCheck();
    return 0;
}

void runTimeCheck()
{
    openlog("time_check_process", LOG_PID|LOG_CONS,LOG_USER);
    syslog(LOG_INFO,"runtTimeCheck() started....");

    
    printf("runtTimeCheck() started....\n");
    while(1)
        {
        struct tm *current_time = get_current_time();
        int is_backup_time = check_backup_time(current_time);

        if(is_backup_time == 1)
        {
            printf("Backup!");
            testServer();
            syslog(LOG_INFO,"Backup time reached.");
            break;        
        }
    } 
    syslog(LOG_WARNING,"time_check_process has stopped.");
    closelog();
}

void testServer()
{
    char queue_name[] = "/assignment_queue";
    printf("Testing message queue client\n");
    printf("Queue name: %s\n",queue_name);
    
    mqd_t mq;
    char buffer[50] = "Its back up time!";
    char exit_buffer[10] = "exit";

    //open queue
    mq = mq_open(queue_name, O_WRONLY);

    mq_send(mq,buffer,sizeof(buffer),0);
    mq_send(mq,exit_buffer,sizeof(exit_buffer),0);

}
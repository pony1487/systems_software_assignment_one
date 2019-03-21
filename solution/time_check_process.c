/*
This process will be forked and exec from assignment_main
It will check if it is a particular time and then send that message to the message queue
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mqueue.h>
#include <syslog.h>

#include "time_check.h"


void runTimeCheck();
void sendMessageToServer(char *msg);

int main(int argc, char *argv[])
{
    printf("time_check_process started....\n");
    openlog("time_check_process", LOG_PID|LOG_CONS,LOG_USER);

    runTimeCheck();

    syslog(LOG_WARNING,"time_check_process has stopped.");
    closelog();
    return 0;
}

void runTimeCheck()
{
    syslog(LOG_INFO,"runtTimeCheck() started....");

    while(1)
    {
    struct tm *current_time = get_current_time();
    int is_backup_time = check_backup_time(current_time);

        if(is_backup_time == 1)
        {
            syslog(LOG_INFO,"Backup time reached.");

            sendMessageToServer("write_to_access_log");
            sendMessageToServer("backup");

            //sendMessageToServer("exit");
            //remove break to let the time check run indefinitley
            //break;        
        }
    } 
}


void sendMessageToServer(char *msg)
{
    char queue_name[] = "/assignment_queue";
    printf("sending %s to %s.\n",msg,queue_name);
    
    mqd_t mq;
    char buffer[50];

    strcpy(buffer, msg);
    //open queue
    mq = mq_open(queue_name, O_WRONLY);

    mq_send(mq,buffer,sizeof(buffer),0);
}
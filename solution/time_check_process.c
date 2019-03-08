/*
This process will be forked and exec from assignment_main
It will check if it is a particular time and then send that message to the message queue
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <syslog.h>

#include "time_check.h"


void runTimeCheck();

int main(int argc, char *argv[])
{

    runTimeCheck();
    return 0;
}

void runTimeCheck()
{
    openlog("Assignment", LOG_PID|LOG_CONS,LOG_USER);
    syslog(LOG_INFO,"runtTimeCheck() started....");

    printf("runtTimeCheck() started....\n");
    while(1)
        {
        struct tm *current_time = get_current_time();
        int is_backup_time = check_backup_time(current_time);

        if(is_backup_time == 1)
        {
            printf("Backup!");
            syslog(LOG_INFO,"Backup time reached.");           
        }
    } 
    syslog(LOG_WARNING,"time_check_process has stopped.");
    closelog();
}
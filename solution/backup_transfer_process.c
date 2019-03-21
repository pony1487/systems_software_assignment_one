#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <syslog.h>
#include "backup_transfer.h"


int main()
{
    openlog("backup_transfer_process", LOG_PID|LOG_CONS,LOG_USER);

    //backup
    if(backup() == -1)
    {
        printf("Backup failed");
        syslog(LOG_ERR,"Backup failed!"); 
    }
    else
    {
        syslog(LOG_INFO,"backup has completed.");
    }
    

        //transfer
    printf("transfer\n");
    if(transfer() == -1)
    {
        printf("Transfer to live failed");
        syslog(LOG_ERR,"Transfer to live failed!"); 
    }
    else
    {
        syslog(LOG_INFO,"transfer has completed.");        
    }
    

    closelog();
    return 0;
}
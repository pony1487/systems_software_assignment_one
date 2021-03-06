/*
This will accept messages and fork other processes depending on the message
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <mqueue.h>
#include <syslog.h>

#include "file_permissions.h"
//#include "backup_transfer.h"

#define BUFFER_SIZE 1024

int main(int argc, char *argb[])
{
    openlog("message_queue_server", LOG_PID|LOG_CONS,LOG_USER);

    char queue_name[] = "/assignment_queue";
    printf("Message_queue_server started...\n");

    char log_info[50] = "Queue name: ";
    strcat(log_info,queue_name);
    printf("%s\n",log_info);

    syslog(LOG_INFO,"Message_queue_server started..."); 
    syslog(LOG_INFO,log_info); 
    

    mqd_t message_queue;
    struct mq_attr queue_attributes;
    char buffer[BUFFER_SIZE + 1];
    int running = 1;

    //Set up queue attributes
    queue_attributes.mq_flags = 0;
    queue_attributes.mq_maxmsg = 10;
    queue_attributes.mq_msgsize = BUFFER_SIZE;
    queue_attributes.mq_curmsgs = 0;

    //Create queue
    message_queue = mq_open(queue_name,O_CREAT | O_RDONLY,0644,&queue_attributes);

    do{
        ssize_t bytes_read;

        //recieve message
        bytes_read = mq_receive(message_queue,buffer,BUFFER_SIZE,NULL);

        buffer[bytes_read] = '\0';


        printf("Received: %s\n",buffer);      
        //write what was recieved to the syslog
        syslog(LOG_INFO,buffer);  

        if(strcmp(buffer,"write_to_access_log") == 0)
        {
            printf("write_to_access_log\n");
            syslog(LOG_INFO,"write_to_access_log message recieved"); 
            pid_t pid;

            int status;
            pid_t wait_pid;

            pid = fork();

            if(pid < 0)
            {
                perror("Error: failed to fork");
                exit(EXIT_FAILURE);
            }
            else if(pid == 0)
            {
                char * argv_list[] = {"log_change_process",NULL};
                execv("./log_change_process",argv_list);
            }


            wait_pid = wait(&status);
            printf("message_queuese_server: child %d exited with status 0x%x\n",pid,status);

        }
        else if(strcmp(buffer,"backup") == 0)
        {
            pid_t pid;

            int status;
            pid_t wait_pid;

            printf("Backup message received\n");
            //lockdown
            printf("lockdown\n");
            lock_dir();
            syslog(LOG_INFO,"Backup started. folder locked..."); 

            printf("\ndir locked\n");
            
            // Backup
            pid = fork();

            if(pid < 0)
            {
                perror("Error: failed to fork");
                exit(EXIT_FAILURE);
            }
            else if(pid == 0)
            {
                char * argv_list[] = {"backup_transfer_process",NULL};
                execv("./backup_transfer_process",argv_list);
            }

            // Wait for backup to complete
            wait_pid = wait(&status);

            unlock_dir();
            printf("\ndir unlocked\n");
            syslog(LOG_INFO,"Backup and Transfer complete. folder unlocked..."); 

        }
        else if(strcmp(buffer,"exit") == 0)
        {
            running = 0;
        }

    }while(running);

    mq_close(message_queue);
    mq_unlink(queue_name);

    syslog(LOG_WARNING,"message_queue_server has stopped.");
    closelog();
    return 0;
}

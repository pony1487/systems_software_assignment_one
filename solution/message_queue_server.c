#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mqueue.h>
#include <syslog.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argb[])
{
    char queue_name[] = "/assignment_queue";
    printf("Message_queue_server\n");
    printf("Queue name: %s\n",queue_name);
    


    mqd_t message_queue;
    struct mq_attr queue_attributes;
    char buffer[BUFFER_SIZE + 1];
    int terminate = 0;

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
        if(! strncmp(buffer,"exit",strlen("exit")))
        {
            terminate = 1;
        }
        else
        {
            printf("Received: %s\n",buffer);      
            openlog("message_queue_server", LOG_PID|LOG_CONS,LOG_USER);
            syslog(LOG_INFO,buffer);          
        }
        
    }while(!terminate);

    mq_close(message_queue);
    mq_unlink(queue_name);

    syslog(LOG_WARNING,"message_queue_server has stopped.");
    closelog();
    return 0;
}
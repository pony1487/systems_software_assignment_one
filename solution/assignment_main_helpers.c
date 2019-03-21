#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>

//NOTHING USED IN THIS FILE
void writeAccessLog()
{
    printf("test write access log\n");
    char cmd[100] = "sudo ausearch -f $AUDITD_PATH > ";
    char filename[100] = "accesslog";
    char ext[5] = ".txt";
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

/*
Multiple processes are forked and have the same parent. Each process does a particular task. The messeage queue is used to let each process know
of an event.
0:  assignment_queue_server
1:  time_check_process

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

#include "assignment_main_helpers.h"

void signal_handler(int sig)
{
    char buffer[100];
    sprintf(buffer, "Caught signal %d", sig);
    syslog(LOG_WARNING, buffer);
}

int main()
{

    // Make it a daemon
    int pid = fork();

    if (pid > 0)
    {
        printf("Parent process..\n");
        //sleep(10);
        exit(EXIT_SUCCESS);
    }
    else if (pid == 0)
    {
        printf("Child process..\n");

        if (setsid() < 0)
        {
            exit(EXIT_FAILURE);
        }

        umask(0);

        //NOTE: The programs that are execv'd need to be moved to root for this work
        if (chdir("/") < 0)
        {
            exit(EXIT_FAILURE);
        }

        int x;
        for (x = sysconf(_SC_OPEN_MAX); x >= 0; x--)
        {
            close(x);
        }

        //Open logs and write message
        openlog("assignment_daemon", LOG_PID | LOG_CONS, LOG_USER);

        syslog(LOG_INFO, "assignment_daemon started...");

        //log any interupts
        signal(SIGINT, signal_handler);

        //for two children
        int SIZE = 2;
        pid_t child_pids[SIZE];
        int num_of_children = SIZE;

        for (int i = 0; i < num_of_children; i++)
        {
            if ((child_pids[i] = fork()) < 0)
            {
                perror("Error: failed to fork!\n");
                syslog(LOG_ERR, "failed to fork...");
                exit(EXIT_FAILURE);
            }
            else if (child_pids[i] == 0)
            {

                if (i == 0)
                {
                    syslog(LOG_INFO, "Forked message_server...");
                    //run message server
                    char *argv_list[] = {"message_queue_server", NULL};
                    execv("./assignment_queue_server", argv_list);
                }

                if (i == 1)
                {
                    syslog(LOG_INFO, "Forked time_check...");
                    //run time check
                    char *argv_list[] = {"time_check_process", NULL};
                    execv("./time_check_process", argv_list);
                }
            }
        }

        //parent(daemon) wait for both children to exit
        int status;
        pid_t pid;
        char exit_buffer[200];

        while (num_of_children > 0)
        {
            pid = wait(&status);
            sprintf(exit_buffer, "Child %d exited with status 0x%x", pid, status);

            syslog(LOG_INFO, exit_buffer);

            num_of_children--;
        }

        syslog(LOG_INFO, "assignment_daemon ended...");
    }
    return 0;
}

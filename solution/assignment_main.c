#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include "time_check.h"
//#include "assignment_main_helpers.h"


int main()
{
    pid_t pid;

    pid = fork();

    if(pid == 0)
    {
        printf("child");
    }
    else
    {
        printf("parent:");
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
    

    return 0;
}


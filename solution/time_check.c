#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "time_check.h"

#define HOUR 13
#define MIN 50
#define SEC 0

int check_backup_time(struct tm *current_time)
{
    //If the time is 21:0:0 return 1 as a flag for a backup is due
    if(current_time->tm_hour == HOUR && current_time->tm_min == MIN && current_time->tm_sec == SEC)
    {
        return 1;
    }
    return 0;
}


struct tm* get_current_time()
{
    time_t current_t, target_t;
    struct tm *target_time_struct;
    struct tm *current_time_struct;
    time(&current_t);
    current_time_struct = localtime(&current_t);
    //printf("current time: %s\n",asctime(current_time_struct));
    return current_time_struct;
}



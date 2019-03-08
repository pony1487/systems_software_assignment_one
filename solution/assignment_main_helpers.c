#include <time.h>
#include "time_check.h"


void runTimeCheck()
{
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
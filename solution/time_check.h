#ifndef TIME_CHECK_H_   /* Include guard */
#define TIME_CHECK_H_
#include <time.h>

int check_backup_time(struct tm *);
struct tm* get_current_time();

#endif
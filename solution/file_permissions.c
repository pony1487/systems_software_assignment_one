#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define DIR_PATH "/home/ronan/Documents/College/SystemsSoftware/Assignment/src"

void lock_dir()
{
    char mode[] ="0444";

    int i = strtol(mode,0,8);
    if(chmod(DIR_PATH,i) < 0)
    {
        perror("Cant lock mode!\n");
    } 

}

void unlock_dir()
{
    char mode[] ="0755";

    int i = strtol(mode,0,8);
    if(chmod(DIR_PATH,i) < 0)
    {
        perror("Cant unlock mode!\n");
    } 

}
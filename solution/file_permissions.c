#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define DIR_PATH "/home/ronan/Documents/College/SystemsSoftware/Assignment/src"

void lock_dir()
{
    char cmd[200] = "chmod -R 555 ";
    strcat(cmd,DIR_PATH);

    if(system(cmd) == -1)
    {
        perror("Could not lock dir\n");
    }
}

void unlock_dir()
{

    char cmd[200] = "chmod -R 755 ";
    strcat(cmd,DIR_PATH);

    if(system(cmd) == -1)
    {
        perror("Could not unlock dir\n");
    }

}
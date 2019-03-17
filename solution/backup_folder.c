#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SRC_DIR "/home/ronan/Documents/College/SystemsSoftware/Assignment/src/live/. "
#define DEST_DIR "/home/ronan/Documents/College/SystemsSoftware/Assignment/src/backup"

int backup()
{
    char cmd[200] = "cp -a ";
    strcat(cmd,SRC_DIR);
    strcat(cmd,DEST_DIR);

    if(system(cmd) == -1)
    {
        perror("Could not copy\n");
        return -1;
    }

    return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BACKUP_SRC_DIR "/home/ronan/Documents/College/SystemsSoftware/Assignment/src/live/. "
#define BACKUP_DEST_DIR "/home/ronan/Documents/College/SystemsSoftware/Assignment/src/backup"
 
#define TRANSFER_SRC_DIR "/home/ronan/Documents/College/SystemsSoftware/Assignment/src/intranet/. "
#define TRANSFER_DEST_DIR "/home/ronan/Documents/College/SystemsSoftware/Assignment/src/live"

int backup()
{
    char cmd[200] = "cp -a ";
    strcat(cmd,BACKUP_SRC_DIR);
    strcat(cmd,BACKUP_DEST_DIR);

    if(system(cmd) == -1)
    {
        perror("Could not copy\n");
        return -1;
    }

    return 0;
}

int transfer()
{
    char cmd[200] = "cp -a ";
    strcat(cmd,TRANSFER_SRC_DIR);
    strcat(cmd,TRANSFER_DEST_DIR);

    if(system(cmd) == -1)
    {
        perror("Could not copy\n");
        return -1;
    }

    return 0;
}
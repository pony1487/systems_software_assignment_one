/*
Will be ran to write to a file the changes made on the intranet folder when it is backup time
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mqueue.h>
#include <syslog.h>
#include <time.h>

void remove_spaces(char* source);

/*
NOT WORKING!!!!
*/
int main(int argc, char *argv[])
{
    openlog("log_change_process", LOG_PID|LOG_CONS,LOG_USER);
    syslog(LOG_INFO,"log_change_process started....");

	time_t rawtime;
	struct tm *timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	char *time_as_str_literal = asctime(timeinfo);
	
    // Segmentation fault??
    //const char *path_to_watch_file;
	//path_to_watch_file = getenv("AUDITD_PATH");

    char *path_to_watch_file = "/home/ronan/Documents/College/SystemsSoftware/Assignment/src/intranet";
    printf("%s\n",path_to_watch_file);

    remove_spaces(time_as_str_literal);

    printf("%s\n",time_as_str_literal);

    //this is an environment variable set to location of the intranet folder
    char cmd[200] = "ausearch -f ";
	char redirect[5] = " > ";
	strcat(cmd,path_to_watch_file);

    printf("%s\n",cmd);
	
	//add the redirect char
	strcat(cmd,redirect);
	
    printf("%s\n",cmd);
	
	//add the time/date with no spaces as the file name
	strcat(cmd,time_as_str_literal);
	printf("%s\n",cmd);
	
	// //make sure to run the main deamon as root so the ausearch cmd can be run
	system(cmd);

    syslog(LOG_WARNING,"log_change_process has stopped.");
    closelog();
    return 0;
}

void remove_spaces(char* source)
{
  char* i = source;
  char* j = source;
  while(*j != 0)
  {
    *i = *j++;
    if(*i != ' ')
      i++;
  }
  *i = 0;
}
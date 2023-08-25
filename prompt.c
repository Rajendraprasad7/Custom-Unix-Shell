#include "headers.h"

void prompt(char* home) {
    // Do not hardcode the prmopt
    // printf("<Everything is a file> ");    
    char hostname[1024];
    char cwd[1024];
    char home_dir[1024];
    char *username = getlogin();
    gethostname(hostname, sizeof(hostname));
    getcwd(cwd, sizeof(cwd));
    // printf("%s\n", cwd);
    strcpy(home_dir, home);
    char *relative_path = strstr(cwd, home_dir);

    if (relative_path != NULL) {
        printf("<\033[1;34m%s\033[0m@%s:~%s %s> ", username, hostname, relative_path + strlen(home_dir), time_taken);
    } else {
        printf("<\033[1;34m%s\033[0m@%s:~%s %s> ", username, hostname, cwd, time_taken);
    }
    // printf("<%s@%s:%s> ", username, hostname, cwd);
    fflush(stdout);
}

void update_prompt(struct timeval start_time, char* cmd_name)
{
    struct timeval end_time;
    gettimeofday(&end_time, NULL);
    
    int execution_time = (int)(end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

    if(execution_time >= 2)
    {
        sprintf(time_taken, "%s%s%ds", cmd_name," : ", execution_time);
    }
    else 
    {   
        char a[1];
        a[0] = '\0';
        strcpy(time_taken, a);
    }
}
#include "headers.h"

void execute_cmd(char** tokens, int flag)
{
    pid_t pid = fork();
    // struct timeval start_time, end_time;

    // gettimeofday(&start_time, NULL);
    if (pid < 0)
    {
        perror("Forking");
        return;
    }
    else if (pid != 0)
    {
        int status;

        if (flag == 0)
        {
            waitpid(pid, &status, 0);
        }
        else 
        {
            printf("%d\n", pid);
        }
        
        // if (WIFEXITED(status)) {
        //     gettimeofday(&end_time, NULL);
            
        //     int execution_time = (int)(end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

        //     if(execution_time >= 2)
        //     {
        //         sprintf(time_taken, "%s%s%ds", tokens[0]," : ", execution_time);
        //     }
        //     else 
        //     {   
        //         char a[1];
        //         a[0] = '\0';
        //         strcpy(time_taken, a);
        //     }
        // }
    }
    else if (pid == 0)
    {
        if (execvp(tokens[0], tokens) == -1)
        {
            printf("ERROR: Invalid command\n");
        }
        // kill(getpid(), SIGSEGV);
        exit(0);
    }
    return;
}
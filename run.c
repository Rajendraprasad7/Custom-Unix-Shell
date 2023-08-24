#include "headers.h"

void execute_cmd(char** tokens)
{
    pid_t pid = fork();
    struct timeval start_time, end_time;

    gettimeofday(&start_time, NULL);

    if (pid < 0)
    {
        perror("Forking");
        return;
    }
    else if (pid != 0)
    {
        int status;
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status)) {
            gettimeofday(&end_time, NULL);
            
            int execution_time = (int)(end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
            // update prompt based on exec time 
        }
    }
    else 
    {
        if (execvp(tokens[0], tokens) == -1)
        {
            printf("ERROR: Invalid command\n");
        }
        kill(getpid(), SIGSEGV);
    }
    return;
}
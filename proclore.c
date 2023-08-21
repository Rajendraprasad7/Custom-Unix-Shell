#include "headers.h"

long get_virtual_memory(pid_t pid) {
    char statFilePath[1024];
    snprintf(statFilePath, sizeof(statFilePath), "/proc/%d/stat", pid);
    FILE *statFile = fopen(statFilePath, "r");
    if (statFile) {
        long vsize;
        // Read the 23rd field from /proc/<pid>/stat, which represents virtual memory size (vsize)
        fscanf(statFile, "%*d %*s %*c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %*u %*u %*d %*d %*d %*d %*d %*u %ld", &vsize);
        fclose(statFile);
        return vsize;
    } else {
        return 0L;
    }
}

int is_background_process(pid_t pid) {
    pid_t terminal_pgid = tcgetpgrp(STDIN_FILENO);
    return (getpgid(pid) != terminal_pgid);
}


void get_process_info(int id)
{
    char status;
    char executablePath[1024];
    char statFilePath[1024];
    snprintf(statFilePath, sizeof(statFilePath), "/proc/%d/stat", id);
    FILE *statFile = fopen(statFilePath, "r");
    if (statFile) {
        fscanf(statFile, "%*d %*s %c", &status);
        fclose(statFile);
    } else {
        perror("Error reading process status");
        return;
    }


    pid_t processGroup = getpgid(id);

    long virtualMemory = get_virtual_memory(id);

    char exeLinkPath[1024];
    snprintf(exeLinkPath, sizeof(exeLinkPath), "/proc/%d/exe", id);
    ssize_t bytesRead = readlink(exeLinkPath, executablePath, sizeof(executablePath) - 1);
    if (bytesRead != -1) {
        executablePath[bytesRead] = '\0';
    } else {
        perror("Error reading executable path");
        return;
    }

    char status_string[3];

    if (!is_background_process(id)) {
        snprintf(status_string, sizeof(status_string), "%c+", status);
    } else {
        snprintf(status_string, sizeof(status_string), "%c", status);
    }

    printf("pid : %d\n", id);
    printf("process Status : %s\n", status_string);
    printf("Process Group : %d\n", processGroup);
    printf("Virtual memory : %ld\n", virtualMemory);
    printf("executable Path : %s\n", executablePath);
}
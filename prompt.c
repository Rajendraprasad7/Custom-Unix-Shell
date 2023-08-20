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
        printf("<\033[1;34m%s\033[0m@%s:~%s> ", username, hostname, relative_path + strlen(home_dir));
    } else {
        printf("<\033[1;34m%s\033[0m@%s:~%s> ", username, hostname, cwd);
    }
    // printf("<%s@%s:%s> ", username, hostname, cwd);
    fflush(stdout);
}
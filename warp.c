#include "headers.h"

void warp(char** tokens, int numTokens, char* home)
{
    if (numTokens == 1)
    {
        chdir(home);
        printf("%s\n", home);
        return;
    }
    char cwd[1024];
    for (int i = 1; i < numTokens; i++) {
        if (strcmp(tokens[i], "~") == 0)
        {
            chdir(home);
            printf("%s\n", home);
        }
        else if (chdir(tokens[i]) == 0)
        {
            getcwd(cwd, sizeof(cwd));
            printf("%s\n", cwd);
        }
        else 
        {
            printf("Error: No such directory\n");
        }
    }
}
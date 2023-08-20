#include "headers.h"

void warp(char** tokens, int numTokens, char* home, char** prevwd)
{
    if (numTokens == 1)
    {
        chdir(home);
        printf("%s\n", home);
        return;
    }
    char cwd[1024];
    char tmp[1024];

    for (int i = 1; i < numTokens; i++) {
        getcwd(tmp, sizeof(tmp));
        if (strcmp(tokens[i], "~") == 0)
        {
            chdir(home);
            printf("%s\n", home);
            strcpy(*prevwd, tmp);
        }
        else if (strcmp(tokens[i], "-") == 0)
        {
            chdir(*prevwd);
            printf("%s\n", *prevwd);
            strcpy(*prevwd, tmp);
        }
        else if (chdir(tokens[i]) == 0)
        {
            getcwd(cwd, sizeof(cwd));
            printf("%s\n", cwd);
            strcpy(*prevwd, tmp);
        }
        else 
        {
            printf("Error: No such directory\n");
        }
    }
}
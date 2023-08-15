#include "headers.h"

void identify(char* cmd, char* home)
{
    char *tokens[10];
    int numTokens;

    tokenizeit(cmd, tokens, &numTokens);

    if (strcmp(tokens[0], "warp") == 0)
    {
        warp(tokens, numTokens, home);
    }
    else 
    {
        system(cmd);
    }
    return;
}
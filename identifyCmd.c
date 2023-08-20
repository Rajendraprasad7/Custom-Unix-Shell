#include "headers.h"

void identify(char* cmd, char* home, char* prevwd)
{
    char *tokens[10];
    int numTokens;

    tokenizeit(cmd, tokens, &numTokens);

    if (strcmp(tokens[0], "warp") == 0)
    {
        warp(tokens, numTokens, home, &prevwd);
    }
    else if (strcmp(tokens[0], "peek") == 0)
    {
        char path[1024];
        strcpy(path,".");
        int show_hidden = 0;
        int show_details = 0;

        for (int i = 1; i<10; i++) {
            if (strcmp(tokens[i], "-a") == 0) {
                show_hidden = 1;
            } 
            else if (strcmp(tokens[i], "-l") == 0) {
                show_details = 1;
            } 
            else if (strcmp(tokens[i], "-la") == 0) {
                show_details = 1;
                show_hidden = 1;
            }
            else if (strcmp(tokens[i], "-al") == 0) {
                show_details = 1;
                show_hidden = 1;
            }
            else {
                strcpy(path, tokens[i]);
                break;
            }
        }
        peekdir(path, home, prevwd, show_hidden, show_details);

    }
    else 
    {
        system(cmd);
    }
    return;
}
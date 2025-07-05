#include "headers.h"

void getCommands(char* input, char*** commands)
{
    unsigned long len = strlen(input);

    input[len - 1] = '\0';

    char* tmpcmds[50];
    char* token = strtok(input, ";");

    tmpcmds[0] = NULL;
    for (int i = 0; token != NULL; i++) 
    {
        tmpcmds[i] = token;
        tmpcmds[i+1] = NULL;
        token = strtok(NULL, ";");
    }
    cmd_count = 0;
    commands[0] = NULL;
    for (int i = 0; tmpcmds[i] != NULL; i++) {
        cmd_count++;
        commands[i] = malloc(50 * sizeof(char*));
        token = strtok(tmpcmds[i], "&");
        bg_count = 0;
        commands[i][0] = NULL;
        for (int j = 0; (j < 50 && token != NULL); j++) {
            commands[i][j] = malloc(strlen(token) + 1);  
            strcpy(commands[i][j], token);
            commands[i][j + 1] = NULL;
            token = strtok(NULL, "&");
            bg_count++;
        }
        commands[i+1] = NULL;
    }
    return;
}
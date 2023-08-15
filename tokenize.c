#include "headers.h"

void trimLeadingWhitespace(char **str) {
    while (isspace(**str)) {
        (*str)++;
    }
}

void tokenizeit(const char *command, char **tokens, int *numTokens)
{
    char *cmdCopy = strdup(command); 

    *numTokens = 0; 

    char *token = strtok(cmdCopy, " \t"); 

    while (token != NULL) {
        trimLeadingWhitespace(&token); 
        tokens[*numTokens] = strdup(token);
        (*numTokens)++;
        token = strtok(NULL, " \t");
    }
    free(cmdCopy);
}
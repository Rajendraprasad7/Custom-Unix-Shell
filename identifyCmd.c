#include "headers.h"

int identify(char* cmd, char* home, char* prevwd)
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

        for (int i = 1; i<numTokens; i++) {
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
    else if (strcmp(tokens[0], "proclore") == 0)
    {
        if (numTokens == 1)
        {
            get_process_info(getpid());
        }
        else
        {
            get_process_info(atoi(tokens[1]));
        }
    }
    
    else if (strcmp(tokens[0], "seek") == 0)
    {
        int isf = 0, isd = 0, e = 0;
        char target[100]; 
        char where[1024];
        int i;
        for(i=1; i<numTokens; i++)
        {
            if (strcmp(tokens[i], "-f") == 0) {
                isf = 1;
            } 
            else if (strcmp(tokens[i], "-d") == 0) {
                isd = 1;
            } 
            else if(strcmp(tokens[i], "-e") == 0)
            {
                e = 1;
            }
            else if((strcmp(tokens[i], "-ef") == 0) || (strcmp(tokens[i], "-fe") == 0))
            {
                e = 1;
                isf = 1;
            }
            else if((strcmp(tokens[i], "-ed") == 0) || (strcmp(tokens[i], "-de") == 0))
            {
                e = 1;
                isd = 1;
            }
            else if((strcmp(tokens[i], "-df") == 0) || (strcmp(tokens[i], "-fd") == 0))
            {
                isf = 1;
                isd = 1;
            }
            else 
            {
                strcpy(target, tokens[i]);

                if (i+1 < numTokens)
                {
                    strcpy(where, tokens[i+1]);
                }
                else 
                {
                    strcpy(where, ".");
                }
                i = -1;
                break;
            }
        }

        if ((isf && isd) || (i != -1) || (isf == 0 && isd == 0))
        {
            printf("ERROR: Invalid flags!\n");
        }
        else
        {
            find(where, where, target, home, isd, isf, e);
        }
    }

    else if((strcmp(tokens[0],"exit") == 0) && numTokens == 1)
    {
        exit_flag = 1;
    }
    else if(strcmp(tokens[0],"pastevents") == 0)
    {
        if(numTokens == 1)
        {
            show_history();
        }

        else if(numTokens == 2)
        {
            if(strcmp(tokens[1], "purge") == 0)
            {
                clear_history();
            }
            else 
            {
                printf("ERROR: Invalid command\n");
                return 0;
            }
        }

        else if(numTokens == 3)
        {
            if (strcmp(tokens[1], "execute") == 0 && atoi(tokens[2]) > 0 && atoi(tokens[2]) <= numEvents)
            {
                return execute_history(atoi(tokens[2]), home, prevwd);
            }
            else 
            {
                printf("ERROR: Invalid command\n");
                return 0;
            }
        }
        else 
        {
            printf("ERROR: Invalid command\n");
            return 0;
        }
    }
    else 
    {
        tokens[numTokens] = NULL;
        execute_cmd(tokens);
    }
    return 0;
}
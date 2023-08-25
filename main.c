#include "headers.h"

int counter = 0;
char found[1024];
int exit_flag = 0;
char* events[16];
char time_taken[100];
int bg_count = 0;
int cmd_count = 0;
int numEvents = 0;

int main()
{
    char home[1024];
    getcwd(home, sizeof(home));
    char prevwd[1024];
    strcpy(prevwd,home);

    load_history(home);

    // Keep accepting commands
    while (1)
    {
        // Print appropriate prompt with username, systemname and directory before accepting input
        prompt(home);

        char input[4096];
        char** cmds[50]; 


        fgets(input, 4096, stdin);

        char *tmp_cpy = strdup(input);
        int bgs = 0;
        for(int i=0; i<strlen(input); i++)
        {
            if(input[i] == '&') bgs++;
        }
        // printf("%d\n", bgs);

        add_to_history(input, home);

        getCommands(input, cmds);

        struct timeval start_time;

        if (input[0] == '\0') strcpy(time_taken, "\0");

        for (int i = 0; cmds[i] != NULL; i++)
        {
            for (int j = 0; cmds[i][j] != NULL; j++) {
                gettimeofday(&start_time, NULL);
                if (identify(cmds[i][j], home, prevwd, bgs--)) return 0;
                if(exit_flag == 1) return 0;
                // printf("%d %d %s\n", i,j,cmds[i][j]);
                char *tokens[100];
                int numTokens;
                tokenizeit(cmds[i][j], tokens, &numTokens);
                update_prompt(start_time, tokens[0]);
            }
        }
    }
}

#include "headers.h"

int counter = 0;
char found[1024];
int exit_flag = 0;
char* events[16];
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

        add_to_history(input, home);

        getCommands(input, cmds);
        
        for (int i = 0; cmds[i] != NULL; i++)
        {
            for (int j = 0; cmds[i][j] != NULL; j++) {
                if (identify(cmds[i][j], home, prevwd)) return 0;
                if(exit_flag == 1) return 0;
            }
        }

    }
}

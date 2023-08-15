#include "headers.h"

int main()
{
    char home[1024];
    getcwd(home, sizeof(home));
    // Keep accepting commands
    while (1)
    {
        // Print appropriate prompt with username, systemname and directory before accepting input
        prompt(home);

        char input[4096];
        char** cmds[50]; 

        fgets(input, 4096, stdin);

        // printf("%s %lu\n", input, strlen(input));

        getCommands(input, cmds);


        for (int i = 0; cmds[i] != NULL; i++)
        {
            for (int j = 0; cmds[i][j] != NULL; j++) {
                // printf("%s\n", cmds[i][j]);
                identify(cmds[i][j], home);
            }
        }
    }
}

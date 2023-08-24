#include "headers.h"

void add_to_history(char* input, char* home)
{

    char* input_cpy = malloc(sizeof(char)*200);
    strcpy(input_cpy, input);
    input_cpy[strlen(input_cpy)-1] = '\0';

    if (strcmp(input_cpy, "") && !(numEvents > 0 && strcmp(input_cpy, events[numEvents-1]) == 0) && !strstr(input_cpy, "pastevents"))
    {   
        events[numEvents] = malloc(sizeof(char)*200);
        strcpy(events[numEvents++], input_cpy);
    }

    char path[1024];
    strcpy(path, home);
    strcat(path, "/pastevents.txt");
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        perror("Error opening pastevents file\n");
        return;
    }

    if (numEvents == 16)
    {
        for (int i = 1; i < 16; i++) {
            strcpy(events[i-1], events[i]);
        }
        numEvents--;
    }

    for (int i = 0; i < numEvents; i++) {
        fprintf(file, "%s\n", events[i]);
    }

    fclose(file);
}

void load_history(char* home) {
    char path[1024];
    strcpy(path, home);
    strcat(path, "/pastevents.txt");
    FILE *file = fopen(path, "r");

    if (file == NULL) {
        perror("Error opening pastevents file\n");
        return;
    }

    char buffer[200];
    int count = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strlen(buffer) - 1] = '\0'; 
        events[count] = strdup(buffer);
        count++;
    }
    numEvents = count;

    fclose(file);
}

void show_history()
{
    for(int i=0; i<numEvents; i++)
    {
        printf("%s\n", events[i]);
    }
}

void clear_history()
{
    for(int i=0;i<numEvents;i++)
    {
        events[i] = '\0';
    }
    numEvents = 0;
}

int execute_history(int ind, char* home, char* prevwd)
{
    ind = numEvents-ind;
    
    char ipt[4096];
    char** cmd[50]; 

    strcpy(ipt, events[ind]);
    strcat(ipt, "\n");
    getCommands(ipt, cmd);
    
    for (int i = 0; cmd[i] != NULL; i++)
    {
        for (int j = 0; cmd[i][j] != NULL; j++) {
            identify(cmd[i][j], home, prevwd);
            if(exit_flag == 1) return 1;
        }
    }

    return 0;
}
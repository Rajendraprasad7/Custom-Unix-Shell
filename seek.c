#include "headers.h"

void find(char* orig, char * where, char * name, char* home, int isdir, int isfile, int e)
{
    DIR * dir;
    struct dirent * entry;     
    char * e_name; 
    char fullpath[1024];
    char curr_dir[] = ".";
    char pre_dir[] = "..";
    int e_type;    
    int is_dots; 
    // static int counter = 0;
    struct stat entryStat;

    char newpath[1024];
    char tmp[1024];

    // static char found[1024];

    if(where[0] == '~')
    {
        strcpy(newpath,home);
        strcat(newpath, where+1);
    }
    else if(where[0] == '-')
    {
        strcpy(newpath, where);
    }
    else 
    {
        strcpy(newpath,where);
    }

    if (dir = opendir(newpath)) 
    {
        while ((entry = readdir(dir)) != NULL) 
        {
            e_type = entry -> d_type;
            e_name = entry -> d_name;
            is_dots = strcmp(e_name, curr_dir) == 0 || strcmp(e_name, pre_dir) == 0;
            if (!is_dots) {
                strcpy(tmp, newpath);
                strcat(tmp, "/");
                strcat(tmp, e_name);
                if (lstat(tmp, &entryStat) < 0) {
                    continue;
                }

                if ((isdir && S_ISDIR(entryStat.st_mode)) || (isfile && S_ISDIR(entryStat.st_mode) <= 0) ) {
                    if (strstr(e_name, name) != NULL && isfile && ((*(strstr(e_name, name)+strlen(name)) == '.') ||(strcmp(e_name, name) == 0) )) {
                        counter++;
                        char *relative_path = strstr(tmp, orig);
                        printf("\033[32m.%s\033[0m\n", relative_path + strlen(orig));
                        strcpy(found, tmp);
                    }
                    else if (strstr(e_name, name) != NULL && isdir && (strcmp(e_name, name) == 0))  {
                        counter++;
                        char *relative_path = strstr(tmp, orig);
                        printf("\033[34m.%s\033[0m\n", relative_path + strlen(orig));
                        strcpy(found, tmp);
                    }
                }
            } 

        }

        closedir(dir);
        dir = opendir(newpath);

        while ((entry = readdir(dir)) != NULL) 
        {
            e_type = entry -> d_type;
            e_name = entry -> d_name;
            is_dots = strcmp(e_name, curr_dir) == 0 || strcmp(e_name, pre_dir) == 0;
            if (!is_dots) {
                strcpy(tmp, newpath);
                strcat(tmp, "/");
                strcat(tmp, e_name);
                if (lstat(tmp, &entryStat) < 0) {
                    continue;
                }
                if (S_ISDIR(entryStat.st_mode)) {
                    find(orig, tmp, name, home, isdir, isfile, e);
                }

            } 

        }
        
    } 
    if (strcmp(orig, where) == 0 && e && counter == 1)
    {
        
        if (isdir)
        {
            chdir(found);
        }
        else 
        {
            FILE *file = fopen(found, "r");  
            if (file == NULL) {
                return;
            }

            char buffer[1024];
            while (fgets(buffer, sizeof(buffer), file)) {
                printf("%s", buffer);  
            }

            fclose(file);
        }
    }
    else if (strcmp(orig, where) == 0 && counter == 0)
    {
        printf("No match found!\n");
    }

    if (strcmp(orig, where) == 0) counter = 0;
    
}
#include "headers.h"

void print_colored(const char *name, mode_t mode) {
    if (S_ISDIR(mode)) {
        printf("\033[1;34m%s\033[0m\n", name); 
    } else if (mode & S_IXUSR) {
        printf("\033[1;32m%s\033[0m\n", name);
    } else {
        printf("%s\n", name); 
    }
}

void print_permissions(mode_t mode) {
    printf((S_ISDIR(mode)) ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}

void peekdir(char* path, char* home, char* prev, int show_hidden, int show_details)
{
    char newpath[1024];
    if(path[0] == '~')
    {
        strcpy(newpath,home);
        strcat(newpath, path+1);
    }
    else if(path[0] == '-')
    {
        strcpy(newpath, prev);
    }
    else 
    {
        strcpy(newpath, path);
    }

    struct dirent **entry_list;
    int num_entries = scandir(newpath, &entry_list, NULL, alphasort);
    if (num_entries == -1) {
        perror("scandir");
        return;
    }

    for (int i = 0; i < num_entries; i++) {
        struct dirent *entry = entry_list[i];

        if (!show_hidden && entry->d_name[0] == '.') {
            free(entry);
            continue;
        }

        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", newpath, entry->d_name);

        struct stat info;
        if (lstat(full_path, &info) == -1) {
            perror("lstat");
            free(entry);
            continue;
        }

        if (show_details) {
            struct passwd *pw = getpwuid(info.st_uid);
            struct group *gr = getgrgid(info.st_gid);
            char time_buffer[80];
            strftime(time_buffer, sizeof(time_buffer), "%b %d %H:%M", localtime(&info.st_mtime));
            print_permissions(info.st_mode);
            printf(" %hu", info.st_nlink);
            printf(" %s", pw->pw_name);
            printf(" %s", gr->gr_name);
            printf(" %lld", (long long)info.st_size);
            printf(" %s ", time_buffer);
        }

        print_colored(entry->d_name, info.st_mode);
    }
    return;
}
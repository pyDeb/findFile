#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <limits.h>

char *file_name;

void findFile(char *current_dir)
{
    DIR *dp;
    struct dirent *dirp;
    dp = opendir(current_dir);
    

    while((dirp=readdir(dp)) != NULL)
    {
        printf("%s\n", current_dir);
        if(!strcmp(dirp->d_name, file_name))
        {
            printf("File you were looking for found at directory %s\n", current_dir);
            exit(0);
        }
            
        else
        {
            if (dirp->d_type == DT_DIR && strcmp(dirp->d_name, "..") && strcmp(dirp->d_name, "."))
                {
                    strcat(current_dir, "/");
                    strcat(current_dir ,dirp->d_name);
                    findFile(current_dir); 
                }
        }
    }
    closedir(dp);
    return;
}

int main(int argc, char *argv[])
{
    
    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s <file-name>\n", argv[0]);
        exit(0);
    }


    file_name = (char *)malloc(sizeof(char) * 128);

    char start_dir[PATH_MAX];
    memset(start_dir, '\0', strlen(start_dir));
    getcwd(start_dir, sizeof(start_dir));

    memset(file_name, '\0', strlen(file_name));
    snprintf(file_name, 300, "%s", argv[1]);
    findFile(start_dir);

    printf("The file you are looking for does not exist at the current directory or its sub-directories\n");

    exit(0);
}

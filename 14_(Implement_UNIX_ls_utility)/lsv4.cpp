/*
*  lsv1.cpp: implement simple ls unix utility  with optional -l
*  usage:./lsv4 
        ./lsv4    dirpath
        ./lsv4 -l dirpath
        ./a.out dir1 dir2 dir3
*/



#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

void print_file_info(const char *file_name) {
    struct stat file_stat;

    if (stat(file_name, &file_stat) == -1) {
        perror("stat");
        return;
    }

    printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat.st_mode & S_IXOTH) ? "x " : "- ");

    printf("%2ld ", (long)file_stat.st_nlink);

    struct passwd *pwd = getpwuid(file_stat.st_uid);
    printf("%-8s ", (pwd) ? pwd->pw_name : "unknown");

    struct group *grp = getgrgid(file_stat.st_gid);
    printf("%-8s ", (grp) ? grp->gr_name : "unknown");

    printf("%8lld ", (long long)file_stat.st_size);

    char time_str[20];
    strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stat.st_mtime));
    printf("%s ", time_str);

    // Get just the file name from the full path
    const char *file_name_only = strrchr(file_name, '/');
    if (file_name_only != NULL) {
        file_name_only++; // Move past the '/'
    } else {
        file_name_only = file_name; // No '/' found, use the entire path
    }

    printf("%s\n", file_name_only);
}


void list_directory(const char *dir_name, int detailed_listing) {
    DIR *dir = opendir(dir_name);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.' && !detailed_listing)
            continue;
        
        char file_path[PATH_MAX];
        snprintf(file_path, PATH_MAX, "%s/%s", dir_name, entry->d_name);
        // snprintf(file_path, PATH_MAX, "%s", entry->d_name);

        if (detailed_listing) {
            print_file_info(file_path);
        } else {
            printf("%s  ", entry->d_name);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    int detailed_listing = 0;
    int start_index = 1;

    // Check for -l option
    if (argc > 1 && strcmp(argv[1], "-l") == 0) {
        detailed_listing = 1;
        start_index = 2;
    }

    // If no directory specified, list current directory
    if (argc == start_index) {
        list_directory(".", detailed_listing);
    } else {
        for (int i = start_index; i < argc; i++) {
            printf("Directory listing of %s:\n", argv[i]);
            list_directory(argv[i], detailed_listing);
            printf("\n");
        }
    }

    return 0;
}

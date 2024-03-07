#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <cstdlib> // for the exit function
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <ctime>
#include <cstring>

// Function to display the file permissions in ls -l format
std::string permissions(mode_t mode) {
    std::string perms;

    // File type
    if (S_ISREG(mode)) perms += '-';
    else if (S_ISDIR(mode)) perms += 'd';
    else if (S_ISCHR(mode)) perms += 'c';
    else if (S_ISBLK(mode)) perms += 'b';
    else if (S_ISFIFO(mode)) perms += 'p';
    else if (S_ISLNK(mode)) perms += 'l';
    else if (S_ISSOCK(mode)) perms += 's';
    else perms += '?';

    // Permissions
    perms += (mode & S_IRUSR) ? 'r' : '-';
    perms += (mode & S_IWUSR) ? 'w' : '-';
    perms += (mode & S_IXUSR) ? 'x' : '-';
    perms += (mode & S_IRGRP) ? 'r' : '-';
    perms += (mode & S_IWGRP) ? 'w' : '-';
    perms += (mode & S_IXGRP) ? 'x' : '-';
    perms += (mode & S_IROTH) ? 'r' : '-';
    perms += (mode & S_IWOTH) ? 'w' : '-';
    perms += (mode & S_IXOTH) ? 'x' : '-';

    return perms;
}

// Function to display the directory listing in ls -l format
void listFiles(const char* path) {
    DIR *dir;
    struct dirent *entry;
    struct stat filestat;

    dir = opendir(path);//opendir
    if (dir == nullptr) {
        std::cerr << "Error opening directory: " << path << std::endl;
        return;
    }

    while ((entry = readdir(dir)) != nullptr) {//readdir
        std::string full_path = std::string(path) + "/" + entry->d_name;
        if (stat(full_path.c_str(), &filestat) == -1) {
            std::cerr << "Error statting file: " << entry->d_name << std::endl;
            continue;
        }

        struct passwd *owner = getpwuid(filestat.st_uid);
        if (owner == nullptr) {
            std::cerr << "Error getting owner for file: " << entry->d_name << std::endl;
            continue;
        }

        struct group *grp = getgrgid(filestat.st_gid);
        if (grp == nullptr) {
            std::cerr << "Error getting group for file: " << entry->d_name << std::endl;
            continue;
        }

        std::cout << permissions(filestat.st_mode) << " ";
        std::cout << filestat.st_nlink << " ";
        std::cout << owner->pw_name << " ";
        std::cout << grp->gr_name << " ";
        std::cout << filestat.st_size << " ";
        std::string time = ctime(&filestat.st_mtime);
        time.pop_back(); // Remove trailing newline
        std::cout << time << " ";
        std::cout << entry->d_name << std::endl;
    }
    closedir(dir);
}
int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " -l <directory1> [<directory2> ...]" << std::endl;
        return 1;
    }
    
    if (strcmp(argv[1], "-l") != 0) {
        std::cerr << "Invalid option. Usage: " << argv[0] << " -l <directory1> [<directory2> ...]" << std::endl;
        return 1;
    }

    for (int i = 2; i < argc; ++i) {
        const char* path = argv[i];
        std::cout << "Listing directory: " << path << std::endl;
        listFiles(path);
    }
    
    return 0;
}

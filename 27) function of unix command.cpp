#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
void listFiles(const char *dir_path) {
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') {
            printf("%s\n", entry->d_name);
        }
    }
    closedir(dir);
}
int main(int argc, char *argv[]) {
    const char *dir_path = (argc > 1) ? argv[1] : ".";
    printf("Files in directory '%s':\n", dir_path);
    listFiles(dir_path);
    return 0;
}

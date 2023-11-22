#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 1024
void grep(FILE *file, const char *pattern) {
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, pattern) != NULL) {
            printf("%s", line);
        }
    }
}
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pattern>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    const char *pattern = argv[1];
    printf("Enter text (Ctrl-D to end input):\n");
    grep(stdin, pattern);
    return 0;
}

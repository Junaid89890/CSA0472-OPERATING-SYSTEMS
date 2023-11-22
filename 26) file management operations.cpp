#include <stdio.h>
#include <stdlib.h>
void writeFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "Hello, this is a demonstration of file management operations.\n");
    fprintf(file, "You can add more lines to this file.\n");
    fclose(file);
    printf("File \"%s\" written successfully.\n", filename);
}
void readFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }
    printf("Contents of the file \"%s\":\n", filename);
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    fclose(file);
}
int main() {
    const char *filename = "example.txt";
    writeFile(filename);
    readFile(filename);
    return 0;
}

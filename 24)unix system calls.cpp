#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
int main() {
    int fd;
    fd = creat("example_file.txt", S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    } else {
        printf("File created successfully.\n");
    }
    close(fd);
    fd = open("example_file.txt", O_WRONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    } else {
        printf("File opened in write-only mode.\n"); 
    }
    const char *data = "Hello, this is a sample text.\n";
    ssize_t bytes_written = write(fd, data, strlen(data));
    if (bytes_written == -1) {
        perror("Error writing to file");
        exit(EXIT_FAILURE);
    } else {
        printf("Data written to file: %ld bytes\n", bytes_written);
    }
    close(fd);
    fd = open("example_file.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    } else {
        printf("File opened in read-only mode.\n");
    }
    char buffer[1024];
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
    if (bytes_read == -1) {
        perror("Error reading from file");
        exit(EXIT_FAILURE);
    } else {
        buffer[bytes_read] = '\0';  
        printf("Data read from file:\n%s", buffer);
    }
    close(fd);
    return 0;
}

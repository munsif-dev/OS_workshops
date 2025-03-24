#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

// Error handling macro
#define HANDLE_ERROR(msg) \
    do { perror(msg); return -1; } while(0)

int main() {
    // 1. Create a text file named doc1.txt and write name and age from user input
    char name[100];
    int age;

    // Open file with O_CREAT and O_TRUNC flags to overwrite if file exists
    int fd = open("doc1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        HANDLE_ERROR("Error opening doc1.txt for writing");
    }

    // Take user input for name and age
    printf("Enter your name: ");
    scanf("%s", name);
    printf("Enter your age: ");
    scanf("%d", &age);

    // Write the name and age to the file
    char buffer[200];
    snprintf(buffer, sizeof(buffer), "Name: %s\nAge: %d\n", name, age);

    if (write(fd, buffer, strlen(buffer)) == -1) {
        HANDLE_ERROR("Error writing to doc1.txt");
    }

    // Close file
    close(fd);

    return 0;
}

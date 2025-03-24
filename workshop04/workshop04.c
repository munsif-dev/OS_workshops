#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 1024

// Error handling macro
#define HANDLE_ERROR(msg) \
    do { perror(msg); return -1; } while(0)

int main() {
    // 1. Create a text file named doc1.txt and write name and age from user input
    char name[100];
    int age;

    // Open file with O_CREAT and O_TRUNC flags to overwrite if file exists
    int fd1 = open("doc1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd1 == -1) {
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

    if (write(fd1, buffer, strlen(buffer)) == -1) {
        HANDLE_ERROR("Error writing to doc1.txt");
    }

    // Close file
    close(fd1);

    // 2. Copy doc1.txt to doc2.txt
    int fd2 = open("doc2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd2 == -1) {
        HANDLE_ERROR("Error opening doc2.txt for writing");
    }

    fd1 = open("doc1.txt", O_RDONLY);
    if (fd1 == -1) {
        HANDLE_ERROR("Error opening doc1.txt for reading");
    }

    // Copy contents from doc1.txt to doc2.txt
    char buffer_copy[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;

    while ((bytes_read = read(fd1, buffer_copy, sizeof(buffer_copy))) > 0) {
        bytes_written = write(fd2, buffer_copy, bytes_read);
        if (bytes_written == -1) {
            HANDLE_ERROR("Error writing to doc2.txt");
        }
    }

    if (bytes_read == -1) {
        HANDLE_ERROR("Error reading from doc1.txt");
    }

    close(fd1);
    close(fd2);

    // 3. Read specific bytes from doc1.txt and write to doc2.txt
    fd1 = open("doc1.txt", O_RDONLY);
    if (fd1 == -1) {
        HANDLE_ERROR("Error opening doc1.txt for reading");
    }

    fd2 = open("doc2.txt", O_WRONLY | O_APPEND);
    if (fd2 == -1) {
        HANDLE_ERROR("Error opening doc2.txt for appending");
    }

    // Read from 15th byte to 30th byte
    lseek(fd1, 14, SEEK_SET); // Move to 15th byte
    bytes_read = read(fd1, buffer_copy, 16); // Read 16 bytes
    if (bytes_read == -1) {
        HANDLE_ERROR("Error reading from doc1.txt");
    }
    write(fd2, buffer_copy, bytes_read);

    // Read from 40th byte to 50th byte
    lseek(fd1, 39, SEEK_SET); // Move to 40th byte
    bytes_read = read(fd1, buffer_copy, 11); // Read 11 bytes
    if (bytes_read == -1) {
        HANDLE_ERROR("Error reading from doc1.txt");
    }
    write(fd2, buffer_copy, bytes_read);

    close(fd1);
    close(fd2);

    // 4. Create and open doc3.txt, change its permissions, and write to it
    int fd3 = open("doc3.txt", O_CREAT | O_RDWR, 0777);
    if (fd3 == -1) {
        HANDLE_ERROR("Error creating doc3.txt");
    }
    close(fd3); // Close file after creation

    // Change permissions to read-only
    if (chmod("doc3.txt", S_IRUSR | S_IRGRP | S_IROTH) == -1) {
        HANDLE_ERROR("Error changing permissions for doc3.txt");
    }

    // Open doc3.txt as read-only
    fd3 = open("doc3.txt", O_RDONLY);
    if (fd3 == -1) {
        HANDLE_ERROR("Error opening doc3.txt as read-only");
    }

    // Attempt to write to doc3.txt (this should fail)
    const char *sentence = "This will not be written because the file is read-only.";
    if (write(fd3, sentence, strlen(sentence)) == -1) {
        perror("Write failed");  // Expected failure due to read-only permission
    }

    close(fd3);

    return 0;
}

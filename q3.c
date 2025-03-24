#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 1024

// Error handling macro
#define HANDLE_ERROR(msg) \
    do { perror(msg); return -1; } while(0)

int main() {
    // Open doc1.txt for reading
    int fd1 = open("doc1.txt", O_RDONLY);
    if (fd1 == -1) {
        HANDLE_ERROR("Error opening doc1.txt for reading");
    }

    // Open doc2.txt for writing
    int fd2 = open("doc2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd2 == -1) {
        HANDLE_ERROR("Error opening doc2.txt for writing");
    }

    // Temporary buffer to store the data being read
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;

    // Read from 15th byte to 30th byte from doc1.txt
    lseek(fd1, 14, SEEK_SET);  // Move to 15th byte (lseek is zero-based)
    bytes_read = read(fd1, buffer, 16);  // Read 16 bytes (from byte 15 to 30)
    if (bytes_read == -1) {
        HANDLE_ERROR("Error reading from doc1.txt");
    }
    bytes_written = write(fd2, buffer, bytes_read);  // Write to doc2.txt
    if (bytes_written == -1) {
        HANDLE_ERROR("Error writing to doc2.txt");
    }

    // Read from 40th byte to 50th byte from doc1.txt
    lseek(fd1, 39, SEEK_SET);  // Move to 40th byte
    bytes_read = read(fd1, buffer, 11);  // Read 11 bytes (from byte 40 to 50)
    if (bytes_read == -1) {
        HANDLE_ERROR("Error reading from doc1.txt");
    }
    bytes_written = write(fd2, buffer, bytes_read);  // Write to doc2.txt
    if (bytes_written == -1) {
        HANDLE_ERROR("Error writing to doc2.txt");
    }

    // Close both files
    close(fd1);
    close(fd2);

    return 0;
}

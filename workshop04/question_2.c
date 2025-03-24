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
    // Step 1: Open doc1.txt for reading
    int fd1 = open("doc1.txt", O_RDONLY);
    if (fd1 == -1) {
        HANDLE_ERROR("Error opening doc1.txt for reading");
    }

    // Step 2: Open doc2.txt for writing
    int fd2 = open("doc2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd2 == -1) {
        HANDLE_ERROR("Error opening doc2.txt for writing");
    }

    // Step 3: Read from doc1.txt and write to doc2.txt
    char buffer[BUFFER_SIZE]; // Temporary buffer to store the data being read
    ssize_t bytes_read, bytes_written;

    while ((bytes_read = read(fd1, buffer, sizeof(buffer))) > 0) {
        bytes_written = write(fd2, buffer, bytes_read);
        if (bytes_written == -1) {
            HANDLE_ERROR("Error writing to doc2.txt");
        }
    }

    // Handle reading error (if any)
    if (bytes_read == -1) {
        HANDLE_ERROR("Error reading from doc1.txt");
    }

    // Step 4: Close the files
    close(fd1);
    close(fd2);

    return 0;
}

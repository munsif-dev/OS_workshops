#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    // Step 1: Create and open doc1.txt in write mode
    FILE *file = fopen("doc1.txt", "w");
    if (file == NULL) {
        perror("Error creating doc1.txt");
        return 1;
    }

    // Write some content to the file
    if (fprintf(file, "This is a test file.\n") < 0) {
        perror("Error writing to doc1.txt");
        fclose(file);
        return 1;
    }

    // Close the file after writing
    fclose(file);

    // Step 2: Change the file permissions to read-only
    if (chmod("doc1.txt", S_IRUSR | S_IRGRP | S_IROTH) == -1) {
        perror("Error changing file permissions to read-only");
        return 1;
    }

    // Step 3: Try opening the file in write mode (should fail)
    file = fopen("doc1.txt", "w");
    if (file == NULL) {
        perror("Error: doc1.txt is read-only, can't write to it");
        return 1;
    }

    // Try writing to the file (this should not succeed)
    if (fprintf(file, "Trying to write to a read-only file.\n") < 0) {
        perror("Error writing to doc1.txt (this should fail)");
        fclose(file);  // Close the file before exiting
        return 1;
    }

    fclose(file);  // Close the file after operation (though this shouldn't be reached)
    return 0;
}

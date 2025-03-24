#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *sourceFile = fopen("doc1.txt", "r");  // Open doc1.txt for reading
    if (sourceFile == NULL) {
        perror("Error opening doc1.txt for reading");
        return 1;
    }

    FILE *destinationFile = fopen("doc2.txt", "w");  // Open doc2.txt for writing
    if (destinationFile == NULL) {
        perror("Error opening doc2.txt for writing");
        fclose(sourceFile);  // Close sourceFile before exiting
        return 1;
    }

    char ch;
    // Copy content from sourceFile to destinationFile
    while ((ch = fgetc(sourceFile)) != EOF) {
        if (fputc(ch, destinationFile) == EOF) {
            perror("Error writing to doc2.txt");
            fclose(sourceFile);
            fclose(destinationFile);
            return 1;
        }
    }

    printf("File copied successfully from doc1.txt to doc2.txt\n");

    // Close the files
    fclose(sourceFile);
    fclose(destinationFile);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("doc1.txt", "w");  // Open file for writing
    if (file == NULL) {
        perror("Error opening file for writing");
        return 1;  // Exit on error
    }

    char name[100];
    int age;

    // Get user input
    printf("Enter your name: ");
    scanf("%s", name);
    printf("Enter your age: ");
    scanf("%d", &age);

    // Write name and age to the file
    if (fprintf(file, "Name: %s\nAge: %d\n", name, age) < 0) {
        perror("Error writing to file");
        fclose(file);  // Close the file before exiting
        return 1;
    }

    printf("Data successfully written to doc1.txt\n");

    // Close the file
    fclose(file);
    return 0;
}

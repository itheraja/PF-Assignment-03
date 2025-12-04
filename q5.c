#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Initialize the editor
void initEditor(char ***lines, int *numLines, int *capacity) {
    *capacity = 10;  // Initial capacity
    *numLines = 0;
    
    // Allocate memory for array of pointers
    *lines = (char **)malloc(*capacity * sizeof(char *));
    
    if (*lines == NULL) {
        printf("Error: Memory allocation failed!\n");
        exit(1);
    }
    
    printf("Editor initialized with capacity %d\n", *capacity);
}

// Insert a line at given index
void insertLine(char ***lines, int *numLines, int *capacity, int index, char *text) {
    // Check if index is valid
    if (index < 0 || index > *numLines) {
        printf("Error: Invalid index!\n");
        return;
    }
    
    // Expand array if needed
    if (*numLines >= *capacity) {
        *capacity *= 2;  // Double the capacity
        *lines = (char **)realloc(*lines, *capacity * sizeof(char *));
        
        if (*lines == NULL) {
            printf("Error: Memory reallocation failed!\n");
            exit(1);
        }
        
        printf("Array expanded to capacity %d\n", *capacity);
    }
    
    // Shift pointers to make space (moving pointers, not strings!)
    for (int i = *numLines; i > index; i--) {
        (*lines)[i] = (*lines)[i - 1];
    }
    
    // Allocate exact memory for the new line
    (*lines)[index] = (char *)malloc((strlen(text) + 1) * sizeof(char));
    
    if ((*lines)[index] == NULL) {
        printf("Error: Memory allocation failed for line!\n");
        exit(1);
    }
    
    // Copy the text
    strcpy((*lines)[index], text);
    (*numLines)++;
    
    printf("Line inserted at index %d\n", index);
}

// Delete a line at given index
void deleteLine(char ***lines, int *numLines, int index) {
    if (index < 0 || index >= *numLines) {
        printf("Error: Invalid index!\n");
        return;
    }
    
    // Free the memory for this line
    free((*lines)[index]);
    
    // Shift pointers to fill the gap
    for (int i = index; i < *numLines - 1; i++) {
        (*lines)[i] = (*lines)[i + 1];
    }
    
    (*numLines)--;
    printf("Line %d deleted\n", index);
}

// Print all lines
void printAllLines(char **lines, int numLines) {
    printf("\n=== Text Editor Content (%d lines) ===\n", numLines);
    
    if (numLines == 0) {
        printf("(empty)\n");
        return;
    }
    
    for (int i = 0; i < numLines; i++) {
        printf("%d: %s\n", i, lines[i]);
    }
}

// Free all memory
void freeAll(char **lines, int numLines) {
    for (int i = 0; i < numLines; i++) {
        free(lines[i]);
    }
    free(lines);
    printf("All memory freed\n");
}

// Shrink array to fit exactly
void shrinkToFit(char ***lines, int numLines, int *capacity) {
    if (*capacity > numLines) {
        *capacity = numLines;
        *lines = (char **)realloc(*lines, *capacity * sizeof(char *));
        
        if (*lines == NULL && numLines > 0) {
            printf("Error: Shrink failed!\n");
            exit(1);
        }
        
        printf("Array shrunk to capacity %d\n", *capacity);
    }
}

// Save to file
void saveToFile(char **lines, int numLines, char *filename) {
    FILE *file = fopen(filename, "w");
    
    if (file == NULL) {
        printf("Error: Cannot open file for writing!\n");
        return;
    }
    
    for (int i = 0; i < numLines; i++) {
        fprintf(file, "%s\n", lines[i]);
    }
    
    fclose(file);
    printf("Saved to %s\n", filename);
}

// Load from file
void loadFromFile(char ***lines, int *numLines, int *capacity, char *filename) {
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
        printf("Error: Cannot open file for reading!\n");
        return;
    }
    
    char buffer[1000];
    
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Remove newline character
        buffer[strcspn(buffer, "\n")] = 0;
        
        insertLine(lines, numLines, capacity, *numLines, buffer);
    }
    
    fclose(file);
    printf("Loaded from %s\n", filename);
}

int main() {
    char **lines;
    int numLines, capacity;
    int choice, index;
    char text[1000], filename[100];
    
    printf("=== Minimal Line-Based Text Editor ===\n\n");
    
    initEditor(&lines, &numLines, &capacity);
    
    while (1) {
        printf("\n--- Menu ---\n");
        printf("1. Insert line\n");
        printf("2. Delete line\n");
        printf("3. Print all lines\n");
        printf("4. Save to file\n");
        printf("5. Load from file\n");
        printf("6. Shrink to fit\n");
        printf("7. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar();  // Consume newline
        
        switch (choice) {
            case 1:
                printf("Enter index: ");
                scanf("%d", &index);
                getchar();
                printf("Enter text: ");
                fgets(text, sizeof(text), stdin);
                text[strcspn(text, "\n")] = 0;  // Remove newline
                insertLine(&lines, &numLines, &capacity, index, text);
                break;
                
            case 2:
                printf("Enter index: ");
                scanf("%d", &index);
                deleteLine(&lines, &numLines, index);
                break;
                
            case 3:
                printAllLines(lines, numLines);
                break;
                
            case 4:
                printf("Enter filename: ");
                scanf("%s", filename);
                saveToFile(lines, numLines, filename);
                break;
                
            case 5:
                printf("Enter filename: ");
                scanf("%s", filename);
                loadFromFile(&lines, &numLines, &capacity, filename);
                break;
                
            case 6:
                shrinkToFit(&lines, numLines, &capacity);
                break;
                
            case 7:
                freeAll(lines, numLines);
                printf("Goodbye!\n");
                return 0;
                
            default:
                printf("Invalid choice!\n");
        }
        
        printf("Current: %d lines, capacity: %d\n", numLines, capacity);
    }
    
    return 0;
}

/*
Why Dynamic Allocation is Better:
1. Only allocates memory for actual lines (no waste)
2. Can grow/shrink at runtime (flexible)
3. Handles unknown number of lines efficiently
4. Moving pointers is faster than moving entire strings
*/

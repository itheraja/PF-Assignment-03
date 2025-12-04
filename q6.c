#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Student structure
struct Student {
    int studentID;
    char fullName[100];
    char batch[30];           // CS, SE, Cyber Security, AI
    char membershipType[10];  // IEEE, ACM
    char registrationDate[15]; // YYYY-MM-DD
    char dateOfBirth[15];      // YYYY-MM-DD
    char interest[20];         // IEEE, ACM, Both
};

// Global variables for in-memory storage
struct Student *students = NULL;
int studentCount = 0;
int capacity = 10;

// Initialize database
void initDatabase() {
    students = (struct Student *)malloc(capacity * sizeof(struct Student));
    if (students == NULL) {
        printf("Error: Memory allocation failed!\n");
        exit(1);
    }
}

// Load database from file
void loadDatabase(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("No existing database found. Starting fresh.\n");
        return;
    }
    
    // Read student count
    fread(&studentCount, sizeof(int), 1, file);
    
    // Allocate memory
    if (studentCount > capacity) {
        capacity = studentCount + 10;
        students = (struct Student *)realloc(students, capacity * sizeof(struct Student));
    }
    
    // Read all students
    fread(students, sizeof(struct Student), studentCount, file);
    
    fclose(file);
    printf("Loaded %d students from database.\n", studentCount);
}

// Save database to file
void saveDatabase(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error: Cannot save to file!\n");
        return;
    }
    
    // Write student count
    fwrite(&studentCount, sizeof(int), 1, file);
    
    // Write all students
    fwrite(students, sizeof(struct Student), studentCount, file);
    
    fclose(file);
    printf("Database saved successfully.\n");
}

// Check if student ID is unique
int isUniqueID(int id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].studentID == id) {
            return 0;  // Not unique
        }
    }
    return 1;  // Unique
}

// Add a new student
void addStudent(const char *filename) {
    struct Student newStudent;
    
    printf("\n=== Register New Student ===\n");
    printf("Student ID: ");
    scanf("%d", &newStudent.studentID);
    
    if (!isUniqueID(newStudent.studentID)) {
        printf("Error: Student ID already exists!\n");
        return;
    }
    
    printf("Full Name: ");
    scanf(" %[^\n]", newStudent.fullName);
    
    printf("Batch (CS/SE/Cyber Security/AI): ");
    scanf(" %[^\n]", newStudent.batch);
    
    printf("Membership Type (IEEE/ACM): ");
    scanf(" %[^\n]", newStudent.membershipType);
    
    printf("Registration Date (YYYY-MM-DD): ");
    scanf(" %[^\n]", newStudent.registrationDate);
    
    printf("Date of Birth (YYYY-MM-DD): ");
    scanf(" %[^\n]", newStudent.dateOfBirth);
    
    printf("Interest (IEEE/ACM/Both): ");
    scanf(" %[^\n]", newStudent.interest);
    
    // Expand array if needed
    if (studentCount >= capacity) {
        capacity *= 2;
        students = (struct Student *)realloc(students, capacity * sizeof(struct Student));
        if (students == NULL) {
            printf("Error: Memory reallocation failed!\n");
            exit(1);
        }
    }
    
    // Add student
    students[studentCount++] = newStudent;
    
    // Save to file
    saveDatabase(filename);
    
    printf("Student registered successfully!\n");
}

// Update student
void updateStudent(int studentID, const char *filename) {
    int found = -1;
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].studentID == studentID) {
            found = i;
            break;
        }
    }
    
    if (found == -1) {
        printf("Student not found!\n");
        return;
    }
    
    int choice;
    printf("\nUpdate:\n");
    printf("1. Batch\n");
    printf("2. Membership Type\n");
    printf("Choice: ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        printf("New Batch: ");
        scanf(" %[^\n]", students[found].batch);
    } else if (choice == 2) {
        printf("New Membership Type: ");
        scanf(" %[^\n]", students[found].membershipType);
    }
    
    saveDatabase(filename);
    printf("Student updated successfully!\n");
}

// Delete student
void deleteStudent(int studentID, const char *filename) {
    int found = -1;
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].studentID == studentID) {
            found = i;
            break;
        }
    }
    
    if (found == -1) {
        printf("Student not found!\n");
        return;
    }
    
    // Shift students
    for (int i = found; i < studentCount - 1; i++) {
        students[i] = students[i + 1];
    }
    
    studentCount--;
    saveDatabase(filename);
    printf("Student deleted successfully!\n");
}

// Display all students
void displayAllStudents() {
    printf("\n=== All Students (%d) ===\n", studentCount);
    
    if (studentCount == 0) {
        printf("No students registered.\n");
        return;
    }
    
    for (int i = 0; i < studentCount; i++) {
        printf("\n--- Student %d ---\n", i + 1);
        printf("ID: %d\n", students[i].studentID);
        printf("Name: %s\n", students[i].fullName);
        printf("Batch: %s\n", students[i].batch);
        printf("Membership: %s\n", students[i].membershipType);
        printf("Registration Date: %s\n", students[i].registrationDate);
        printf("DOB: %s\n", students[i].dateOfBirth);
        printf("Interest: %s\n", students[i].interest);
    }
}

// Generate batch-wise report
void generateBatchReport() {
    char batch[30], membership[20];
    
    printf("\nEnter Batch: ");
    scanf(" %[^\n]", batch);
    printf("Enter Membership Type (IEEE/ACM/Both): ");
    scanf(" %[^\n]", membership);
    
    printf("\n=== Report: %s - %s ===\n", batch, membership);
    
    int count = 0;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].batch, batch) == 0) {
            if (strcmp(membership, "Both") == 0 || 
                strcmp(students[i].membershipType, membership) == 0 ||
                strcmp(students[i].interest, "Both") == 0) {
                
                printf("\nID: %d | Name: %s | Membership: %s | Interest: %s\n",
                       students[i].studentID, students[i].fullName,
                       students[i].membershipType, students[i].interest);
                count++;
            }
        }
    }
    
    printf("\nTotal: %d students\n", count);
}

int main() {
    const char *filename = "members.dat";
    int choice, id;
    
    printf("=== IEEE/ACM Membership System ===\n\n");
    
    initDatabase();
    loadDatabase(filename);
    
    while (1) {
        printf("\n--- Menu ---\n");
        printf("1. Register new student\n");
        printf("2. Update student\n");
        printf("3. Delete student\n");
        printf("4. View all students\n");
        printf("5. Generate batch-wise report\n");
        printf("6. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addStudent(filename);
                break;
                
            case 2:
                printf("Enter Student ID: ");
                scanf("%d", &id);
                updateStudent(id, filename);
                break;
                
            case 3:
                printf("Enter Student ID: ");
                scanf("%d", &id);
                deleteStudent(id, filename);
                break;
                
            case 4:
                displayAllStudents();
                break;
                
            case 5:
                generateBatchReport();
                break;
                
            case 6:
                saveDatabase(filename);
                free(students);
                printf("Goodbye!\n");
                return 0;
                
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}

#include <stdio.h>
#include <string.h>

struct Employee {
    int id;
    char name[100];
    char designation[50];
    float salary;
};

void displayEmployees(struct Employee emp[], int n) {
    printf("\n%-10s %-30s %-25s %-15s\n", "ID", "Name", "Designation", "Salary");
    printf("--------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < n; i++) {
        printf("%-10d %-30s %-25s %-15.2f\n",
               emp[i].id, emp[i].name, emp[i].designation, emp[i].salary);
    }
}

void findHighestSalary(struct Employee emp[], int n) {
    int maxIndex = 0;
    
    for (int i = 1; i < n; i++) {
        if (emp[i].salary > emp[maxIndex].salary) {
            maxIndex = i;
        }
    }
    
    printf("\nEmployee with Highest Salary\n");
    printf("ID: %d\n", emp[maxIndex].id);
    printf("Name: %s\n", emp[maxIndex].name);
    printf("Designation: %s\n", emp[maxIndex].designation);
    printf("Salary: %.2f\n", emp[maxIndex].salary);
}

void searchEmployee(struct Employee emp[], int n) {
    int choice, id, found = 0;
    char name[100];
    
    printf("\nSearch by:\n");
    printf("1. ID\n");
    printf("2. Name\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        printf("Enter Employee ID: ");
        scanf("%d", &id);
        
        for (int i = 0; i < n; i++) {
            if (emp[i].id == id) {
                printf("\nEmployee Found:\n");
                printf("ID: %d\n", emp[i].id);
                printf("Name: %s\n", emp[i].name);
                printf("Designation: %s\n", emp[i].designation);
                printf("Salary: %.2f\n", emp[i].salary);
                found = 1;
                break;
            }
        }
        
    } else if (choice == 2) {
        printf("Enter Employee Name: ");
        scanf(" %[^\n]", name);
        
        for (int i = 0; i < n; i++) {
            if (strcmp(emp[i].name, name) == 0) {
                printf("\nEmployee Found:\n");
                printf("ID: %d\n", emp[i].id);
                printf("Name: %s\n", emp[i].name);
                printf("Designation: %s\n", emp[i].designation);
                printf("Salary: %.2f\n", emp[i].salary);
                found = 1;
                break;
            }
        }
    }
    
    if (!found) {
        printf("\nEmployee not found!\n");
    }
}

void updateSalariesWithBonus(struct Employee emp[], int n, float threshold) {
    printf("\n=== Updating Salaries Below %.2f ===\n", threshold);
    
    for (int i = 0; i < n; i++) {
        if (emp[i].salary < threshold) {
            float oldSalary = emp[i].salary;
            emp[i].salary = emp[i].salary * 1.10;
            printf("Employee %s: %.2f -> %.2f\n",
                   emp[i].name, oldSalary, emp[i].salary);
        }
    }
}

int main() {
    int n;
    
    printf("ABC Technologies Employee Management System\n\n");
    printf("Enter number of employees: ");
    scanf("%d", &n);
    
    struct Employee emp[n];
    
    printf("\nEnter Employee Details:\n");
    for (int i = 0; i < n; i++) {
        printf("\nEmployee %d:\n", i + 1);
        printf("ID: ");
        scanf("%d", &emp[i].id);
        printf("Name: ");
        scanf(" %[^\n]", emp[i].name);
        printf("Designation: ");
        scanf(" %[^\n]", emp[i].designation);
        printf("Salary: ");
        scanf("%f", &emp[i].salary);
    }
    
    printf("\n=== All Employee Records ===");
    displayEmployees(emp, n);
    
    findHighestSalary(emp, n);
    
    searchEmployee(emp, n);
    
    updateSalariesWithBonus(emp, n, 50000);
    
    printf("\nUpdated Employee Records");
    displayEmployees(emp, n);
    
    printf("\n\nExplanation of Bonus Function:\n");
    printf("- Array is passed by reference (pointer to first element)\n");
    printf("- Changes made inside function affect original array\n");
    printf("- More efficient than copying all values\n");
    
    return 0;
}

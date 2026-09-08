#include <stdio.h>
#include <stdlib.h>

struct Employee {
    int id;
    char name[50];
    float salary;
};

// Function declarations
void createEmployee();
void displayEmployees();
void updateEmployee();
void deleteEmployee();

int main() {
    int choice;

    while (1) {
        printf("\n===== COMPANY MANAGEMENT SYSTEM =====\n");
        printf("1. Create Employee\n");
        printf("2. Display Employees\n");
        printf("3. Update Employee\n");
        printf("4. Delete Employee\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createEmployee(); break;
            case 2: displayEmployees(); break;
            case 3: updateEmployee(); break;
            case 4: deleteEmployee(); break;
            case 5: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

// CREATE
void createEmployee() {
    FILE *fp = fopen("company.dat", "ab");
    struct Employee e;

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter ID: ");
    scanf("%d", &e.id);

    printf("Enter Name: ");
    scanf(" %[^\n]", e.name);   // supports spaces

    printf("Enter Salary: ");
    scanf("%f", &e.salary);     // ? correct format

    fwrite(&e, sizeof(e), 1, fp);
    fclose(fp);

    printf("Employee Added Successfully!\n");
}

// READ
void displayEmployees() {
    FILE *fp = fopen("company.dat", "rb");
    struct Employee e;

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n--- Employee Records ---\n");

    while (fread(&e, sizeof(e), 1, fp)) {
        printf("ID: %d | Name: %s | Salary: %.2f\n",
               e.id, e.name, e.salary);
    }

    fclose(fp);
}

// UPDATE
void updateEmployee() {
    FILE *fp = fopen("company.dat", "rb+");
    struct Employee e;
    int id, found = 0;

    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    printf("Enter ID to update: ");
    scanf("%d", &id);

    while (fread(&e, sizeof(e), 1, fp)) {
        if (e.id == id) {

            printf("Enter new Name: ");
            scanf(" %[^\n]", e.name);

            printf("Enter new Salary: ");
            scanf("%f", &e.salary);   // ? FIXED

            fseek(fp, -sizeof(e), SEEK_CUR);
            fwrite(&e, sizeof(e), 1, fp);

            found = 1;
            printf("Record Updated!\n");
            break;
        }
    }

    if (!found)
        printf("Record not found!\n");

    fclose(fp);
}

// DELETE
void deleteEmployee() {
    FILE *fp = fopen("company.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    struct Employee e;
    int id, found = 0;

    if (fp == NULL || temp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter ID to delete: ");
    scanf("%d", &id);

    while (fread(&e, sizeof(e), 1, fp)) {
        if (e.id != id) {
            fwrite(&e, sizeof(e), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("company.dat");
    rename("temp.dat", "company.dat");

    if (found)
        printf("Record Deleted!\n");
    else
        printf("Record not found!\n");
}

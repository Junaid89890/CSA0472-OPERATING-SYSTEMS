#include <stdio.h>
#include <stdlib.h>
#define FILENAME "employee_records.dat"
#define MAX_RECORDS 100
struct Employee {
    int id;
    char name[50];
    float salary;
};
void addRecord(FILE *file) {
    struct Employee emp;
    printf("Enter Employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter Employee Name: ");
    scanf("%s", emp.name);
    printf("Enter Employee Salary: ");
    scanf("%f", &emp.salary);
    fseek(file, (emp.id - 1) * sizeof(struct Employee), SEEK_SET);
    fwrite(&emp, sizeof(struct Employee), 1, file);
    printf("Record added successfully.\n");
}
void displayAllRecords(FILE *file) {
    struct Employee emp;
    rewind(file);
    while (fread(&emp, sizeof(struct Employee), 1, file) == 1) {
        printf("ID: %d, Name: %s, Salary: %.2f\n", emp.id, emp.name, emp.salary);
    }
}
void updateRecord(FILE *file, int id) {
    struct Employee emp;
    fseek(file, (id - 1) * sizeof(struct Employee), SEEK_SET);
    if (fread(&emp, sizeof(struct Employee), 1, file) == 1) {
        printf("Enter new salary for employee %d: ", id);
        scanf("%f", &emp.salary);
        fseek(file, (id - 1) * sizeof(struct Employee), SEEK_SET);
        fwrite(&emp, sizeof(struct Employee), 1, file);
        printf("Record updated successfully.\n");
    } else {
        printf("Record not found.\n");
    }
}
void deleteRecord(FILE *file, int id) {
    struct Employee emp;
    fseek(file, (id - 1) * sizeof(struct Employee), SEEK_SET);
    if (fread(&emp, sizeof(struct Employee), 1, file) == 1) {
        emp.id = 0; 
        fseek(file, (id - 1) * sizeof(struct Employee), SEEK_SET);
        fwrite(&emp, sizeof(struct Employee), 1, file);
        printf("Record deleted successfully.\n");
    } else {
        printf("Record not found.\n");
    }
}
int main() {
    FILE *file = fopen(FILENAME, "rb+");
    if (file == NULL) {
        file = fopen(FILENAME, "wb+");
    }
    if (file == NULL) {
        fprintf(stderr, "Error opening the file.\n");
        return 1;
    }
    int choice;
    int empId;
    do {
        printf("\n1. Add Record\n2. Display All Records\n3. Update Record\n4. Delete Record\n0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addRecord(file);
                break;
            case 2:
                displayAllRecords(file);
                break;
            case 3:
                printf("Enter Employee ID to update: ");
                scanf("%d", &empId);
                updateRecord(file, empId);
                break;
            case 4:
                printf("Enter Employee ID to delete: ");
                scanf("%d", &empId);
                deleteRecord(file, empId);
                break;
            case 0:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
    fclose(file);
    return 0;
}

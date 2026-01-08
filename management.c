/*
  STUDENT DATABASE MANAGEMENT SYSTEM
  Manage student records with departments and registration numbers
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Student record structure
struct student
{
    char name[30];              
    int roll;                   
    char department[20];        
    int enrollmentYear;         
    char registrationNumber[20]; 
    float cgpa;                 
    struct student *NEXT;       
};

// Linked list pointers
struct student *head = NULL;  
struct student *tail = NULL;  

// Convert department input to CS code (case-insensitive)
int validateAndSetDepartment(char *dept_input, char *dept_code)
{
    char lowercase_input[20];
    strcpy(lowercase_input, dept_input);
    
    // Convert to lowercase
    for (int i = 0; lowercase_input[i]; i++) {
        if (lowercase_input[i] >= 'A' && lowercase_input[i] <= 'Z') {
            lowercase_input[i] = lowercase_input[i] + 32;
        }
    }
    
    if (strcmp(lowercase_input, "core") == 0) {
        strcpy(dept_code, "CS");
        return 1;
    }
    else if (strcmp(lowercase_input, "ai") == 0) {
        strcpy(dept_code, "CSAI");
        return 1;
    }
    else if (strcmp(lowercase_input, "ds") == 0) {
        strcpy(dept_code, "CSDS");
        return 1;
    }
    else if (strcmp(lowercase_input, "iot") == 0) {
        strcpy(dept_code, "CSIOT");
        return 1;
    }
    
    return 0;
}

// Auto-generate registration number: DEPTCODE + YEAR + ROLL
void generateRegistrationNumber(struct student *s)
{
    snprintf(s->registrationNumber, sizeof(s->registrationNumber), "%s%d%d",
             s->department, s->enrollmentYear, s->roll);
}

// Add a new student to database
void addStudent()
{
    getchar();
    
    struct student *newStudent = malloc(sizeof(struct student));
    
    if (newStudent == NULL) {
        printf("\nMemory allocation failed!\n");
        return;
    }
    
    printf("\nEnter name of the student: ");
    scanf("%[^\n]s", newStudent->name);
    getchar();
    
    printf("\nEnter roll number: ");
    scanf("%d", &newStudent->roll);
    getchar();
    
    char deptInput[20];
    int isDeptValid = 0;
    while (!isDeptValid) {
        printf("\nEnter department (core/ai/ds/iot): ");
        scanf("%[^\n]s", deptInput);
        getchar();
        isDeptValid = validateAndSetDepartment(deptInput, newStudent->department);
        if (!isDeptValid) {
            printf("\n[INVALID] Please enter: core, ai, ds, or iot\n");
        }
    }
    
    printf("\nEnter year of enrollment (e.g., 2024): ");
    scanf("%d", &newStudent->enrollmentYear);
    getchar();
    
    printf("\nEnter CGPA (0-10): ");
    scanf("%f", &newStudent->cgpa);
    getchar();
    
    generateRegistrationNumber(newStudent);
    
    newStudent->NEXT = NULL;
    
    if (head == NULL) {
        head = newStudent;
        tail = newStudent;
    }
    else {
        tail->NEXT = newStudent;
        tail = newStudent;
    }
    
    printf("\nStudent added successfully!\n");
    printf("Registration Number: %s\n", newStudent->registrationNumber);
}

// Search for student by roll number
struct student* searchStudent(int roll)
{
    struct student *current = head;
    
    while(current != NULL)
    {
        if(current->roll == roll)
            return current;
        current = current->NEXT;
    }
    
    return NULL;
}

// Display single student record
void displayStudent(struct student *student)
{
    if(student == NULL)
    {
        printf("\nNo record found!\n");
        return;
    }
    
    printf("\n----------------------------------------");
    printf("\nName: %s", student->name);
    printf("\nRoll Number: %d", student->roll);
    printf("\nDepartment: %s", student->department);
    printf("\nYear: %d", student->enrollmentYear);
    printf("\nReg Number: %s", student->registrationNumber);
    printf("\nCGPA: %.2f", student->cgpa);
    printf("\n----------------------------------------\n");
}

// Display all student records
void displayAllStudents()
{
    struct student *current = head;
    
    if(head == NULL) {
        printf("\nNo records found! Database is empty.\n");
    }
    else
    {
        int recordNumber = 1;
        
        while(current != NULL)
        {
            printf("\n\n===== Record %d =====", recordNumber);
            printf("\nName: %s", current->name);
            printf("\nRoll Number: %d", current->roll);
            printf("\nDepartment: %s", current->department);
            printf("\nYear: %d", current->enrollmentYear);
            printf("\nReg Number: %s", current->registrationNumber);
            printf("\nCGPA: %.2f", current->cgpa);
            
            current = current->NEXT;
            recordNumber++;
            
            if(current != NULL){
                printf("\n----------------------------------------");
                printf("\nPress enter for next record...");
                getchar();
            }
        }
        
        printf("\n\n===== End of Records =====\n");
    }
}

// Search student by roll number
void searchStudentByRoll()
{
    if(head == NULL)
    {
        printf("\nNo records found! Database is empty.\n");
        getchar();
        return;
    }
    
    int rollToSearch;
    printf("\nEnter roll number: ");
    scanf("%d", &rollToSearch);
    getchar();
    
    struct student *foundStudent = searchStudent(rollToSearch);
    
    if(foundStudent != NULL)
    {
        printf("\nStudent found!\n");
        displayStudent(foundStudent);
    }
    else
    {
        printf("\nStudent with roll %d not found!\n", rollToSearch);
    }
    
    printf("\nPress enter to continue...");
    getchar();
}

// Update student information
void updateStudent()
{
    if(head == NULL)
    {
        printf("\nNo records found! Database is empty.\n");
        getchar();
        return;
    }
    
    int rollToUpdate;
    printf("\nEnter roll number: ");
    scanf("%d", &rollToUpdate);
    getchar();
    
    struct student *studentToUpdate = searchStudent(rollToUpdate);
    
    if(studentToUpdate == NULL)
    {
        printf("\nStudent with roll %d not found!\n", rollToUpdate);
        getchar();
        return;
    }
    
    printf("\nEnter new name: ");
    scanf("%[^\n]s", studentToUpdate->name);
    getchar();
    
    char deptInput[20];
    int isDeptValid = 0;
    while (!isDeptValid) {
        printf("\nEnter new department (core/ai/ds/iot): ");
        scanf("%[^\n]s", deptInput);
        getchar();
        isDeptValid = validateAndSetDepartment(deptInput, studentToUpdate->department);
        if (!isDeptValid) {
            printf("\n[INVALID] Please enter: core, ai, ds, or iot\n");
        }
    }
    
    printf("\nEnter new year: ");
    scanf("%d", &studentToUpdate->enrollmentYear);
    getchar();
    
    printf("\nEnter new CGPA: ");
    scanf("%f", &studentToUpdate->cgpa);
    getchar();
    
    generateRegistrationNumber(studentToUpdate);
    
    printf("\nStudent updated!\n");
    printf("%s\n", studentToUpdate->registrationNumber);
    
    printf("\nPress enter to continue...");
    getchar();
}

// Delete a student record
void deleteStudent()
{
    if(head == NULL)
    {
        printf("\nNo records found! Database is empty.\n");
        getchar();
        return;
    }
    
    int rollToDelete;
    printf("\nEnter roll number: ");
    scanf("%d", &rollToDelete);
    getchar();
    
    struct student *current = head;
    struct student *previous = NULL;
    
    if(current != NULL && current->roll == rollToDelete)
    {
        head = current->NEXT;
        if(head == NULL)
            tail = NULL;
        free(current);
        printf("\nStudent deleted!\n");
        getchar();
        return;
    }
    
    while(current != NULL && current->roll != rollToDelete)
    {
        previous = current;
        current = current->NEXT;
    }
    
    if(current == NULL)
    {
        printf("\nStudent with roll %d not found!\n", rollToDelete);
        getchar();
        return;
    }
    
    previous->NEXT = current->NEXT;
    
    if(current->NEXT == NULL)
        tail = previous;
    
    free(current);
    printf("\nStudent deleted!\n");
    getchar();
}

// Delete all student records
void deleteAllStudents()
{
    if(head == NULL) {
        printf("\nDatabase is already empty.\n");
    }
    else
    {
        unsigned long int deletedCount = 0;
        struct student *current = head;
        
        while(current != NULL)
        {
            struct student *nextStudent = current->NEXT;
            free(current);
            current = nextStudent;
            deletedCount++;
        }
        
        head = NULL;
        tail = NULL;
        
        printf("\nAll records cleared!\n");
        printf("Total deleted: %ld\n", deletedCount);
    }
}

// Main menu and program control
int main()
{
    int userChoice = 1;
    
    while(userChoice != 0)
    {
        printf("\n");
        printf("=========================================\n");
        printf("|   STUDENT DATABASE MANAGEMENT SYSTEM  |\n");
        printf("=========================================\n");
        printf("\nMENU OPTIONS:\n");
        printf("  1. Add Student\n");
        printf("  2. Display All Students\n");
        printf("  3. Search Student by Roll\n");
        printf("  4. Update Student\n");
        printf("  5. Delete Student\n");
        printf("  0. Exit Program\n");
        printf("\nEnter your choice: ");
        scanf("%d", &userChoice);
        
        switch(userChoice)
        {
            case 1:
                addStudent();
                break;
                
            case 2:
                displayAllStudents();
                break;
                
            case 3:
                searchStudentByRoll();
                break;
                
            case 4:
                updateStudent();
                break;
                
            case 5:
                deleteStudent();
                break;
                
            case 0:
                deleteAllStudents();
                printf("\nThank you! Program closed safely.\n");
                exit(0);
                break;
                
            default:
                printf("\nInvalid choice! Please enter 0-5.\n");
                getchar();
        }
    }
    
    return 0;
}








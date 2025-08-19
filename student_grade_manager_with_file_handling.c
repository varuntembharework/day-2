#include <stdio.h>
#include <string.h>

char getGrade(float avg) {
    if (avg >= 90) return 'A';
    else if (avg >= 75) return 'B';
    else if (avg >= 50) return 'C';
    else return 'F';
}

void saveRecord(char name[], int marks[], float avg, char grade) {
    FILE *fp = fopen("records.txt", "a"); // append mode
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(fp, "Name: %s\n", name);
    fprintf(fp, "Marks: %d, %d, %d\n", marks[0], marks[1], marks[2]);
    fprintf(fp, "Average: %.2f\n", avg);
    fprintf(fp, "Grade: %c\n", grade);
    fprintf(fp, "------------------------\n");
    fclose(fp);
}

void viewRecords() {
    FILE *fp = fopen("records.txt", "r");
    if (fp == NULL) {
        printf("No records found yet.\n");
        return;
    }
    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }
    fclose(fp);
}

int main() {
    int choice;
    char name[50];
    int marks[3];
    float avg;
    char grade;

    while (1) {
        printf("\n--- Student Grade Manager ---\n");
        printf("1. Add new student record\n");
        printf("2. View all records\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter student name: ");
            scanf(" %[^\n]", name);  // reads full name with spaces

            int sum = 0;
            for (int i = 0; i < 3; i++) {
                do {
                    printf("Enter marks for subject %d (0-100): ", i + 1);
                    scanf("%d", &marks[i]);
                    if (marks[i] < 0 || marks[i] > 100) {
                        printf("❌ Invalid input! Please enter between 0-100.\n");
                    }
                } while (marks[i] < 0 || marks[i] > 100);
                sum += marks[i];
            }

            avg = sum / 3.0;
            grade = getGrade(avg);

            printf("\n✅ Record Added:\n");
            printf("Name: %s\n", name);
            printf("Average: %.2f\n", avg);
            printf("Grade: %c\n", grade);

            saveRecord(name, marks, avg, grade);

        } else if (choice == 2) {
            printf("\n--- All Student Records ---\n");
            viewRecords();

        } else if (choice == 3) {
            printf("Exiting... Goodbye!\n");
            break;

        } else {
            printf("❌ Invalid choice. Try again.\n");
        }
    }

    return 0;
}
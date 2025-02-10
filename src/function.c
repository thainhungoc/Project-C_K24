#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/datatype.h"
#include "../include/function.h"

#define FILENAME "../data/stu.bin"
Student students[100];
int studentCount = 0;

void displayMenu() {
    printf("\n====================================\n");
    printf("    HE THONG QUAN LY SINH VIEN    \n");
    printf("====================================\n");
    printf("1. Hien thị danh sach sinh vien\n");
    printf("2. Them sinh vien mơi\n");
    printf("0. Thoat\n");
    printf("====================================\n");
    printf("Vui long chon chuc nang: ");
}

void displayStudents() {
    if (studentCount == 0) {
        printf("\nDanh sach sinh vien trong\n");
        return;
    }
    
    printf("\n=== DANH SACH SINH VIEN ===\n");
    printf("%-10s %-30s %-10s %-10s\n", "MSSV", "Ho va ten", "Tuoi", "GPA");
    for (int i = 0; i < studentCount; i++) {
        printf("%-10s %-30s %-10d %-10.2f\n", 
            students[i].id, 
            students[i].name, 
            students[i].age, 
            students[i].gpa);
    }
}

void addStudent() {
    if (studentCount >= 100) {
        printf("\nDanh sach sinh vien da day\n");
        return;
    }

    Student newStudent;
    printf("\n=== THEM SINH VIEN MOI ===\n");
    
    printf("Nhap MSSV: ");
    scanf("%s", newStudent.id);
    getchar();
    
    printf("Nhap ho va ten: ");
    fgets(newStudent.name, 50, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = 0; // Xóa ký tự xuống dòng
    
    printf("Nhap tuổi: ");
    scanf("%d", &newStudent.age);
    
    printf("Nhap GPA: ");
    scanf("%f", &newStudent.gpa);

    students[studentCount++] = newStudent;
    saveToFile();
    printf("\nThem sinh vien thanh cong\n");
}

void saveToFile() {
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) {
        printf("\nLoi: khong the mo file de ghi\n");
        return;
    }
    
    fwrite(&studentCount, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), studentCount, file);
    fclose(file);
}

void loadFromFile() {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("\nChua co du lieu sinh vien\n");
        return;
    }
    
    fread(&studentCount, sizeof(int), 1, file);
    fread(students, sizeof(Student), studentCount, file);
    fclose(file);
}
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
    printf("    HỆ THỐNG QUẢN LÝ SINH VIÊN    \n");
    printf("====================================\n");
    printf("1. Hiển thị danh sách sinh viên\n");
    printf("2. Thêm sinh viên mới\n");
    printf("0. Thoát\n");
    printf("====================================\n");
    printf("Vui lòng chọn chức năng: ");
}

void displayStudents() {
    if (studentCount == 0) {
        printf("\nDanh sách sinh viên trống!\n");
        return;
    }
    
    printf("\n=== DANH SÁCH SINH VIÊN ===\n");
    printf("%-10s %-30s %-10s %-10s\n", "MSSV", "Họ và tên", "Tuổi", "GPA");
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
        printf("\nDanh sách sinh viên đã đầy!\n");
        return;
    }

    Student newStudent;
    printf("\n=== THÊM SINH VIÊN MỚI ===\n");
    
    printf("Nhập MSSV: ");
    scanf("%s", newStudent.id);
    getchar();
    
    printf("Nhập họ và tên: ");
    fgets(newStudent.name, 50, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = 0; // Xóa ký tự xuống dòng
    
    printf("Nhập tuổi: ");
    scanf("%d", &newStudent.age);
    
    printf("Nhập GPA: ");
    scanf("%f", &newStudent.gpa);

    students[studentCount++] = newStudent;
    saveToFile();
    printf("\nThêm sinh viên thành công!\n");
}

void saveToFile() {
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) {
        printf("\nLỗi: Không thể mở file để ghi!\n");
        return;
    }
    
    fwrite(&studentCount, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), studentCount, file);
    fclose(file);
}

void loadFromFile() {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("\nChưa có dữ liệu sinh viên.\n");
        return;
    }
    
    fread(&studentCount, sizeof(int), 1, file);
    fread(students, sizeof(Student), studentCount, file);
    fclose(file);
}
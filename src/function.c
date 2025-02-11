#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/datatype.h"
#include "../include/function.h"

// #define FILENAME "./data/stu.bin"
#define FILENAME "./data/students.txt"

Student students[100];
int studentCount = 0;

void displayMenu() {
    printf("\n====================================\n");
    printf("    HE THONG QUAN LY SINH VIEN    \n");
    printf("====================================\n");
    printf("1. Hien thị danh sach sinh vien\n");
    printf("2. Them sinh vien moi\n");
    printf("3. Sua thong tin sinh vien\n");
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
    int soLuong;
    printf("\n=== THEM SINH VIEN MOI ===\n");
    printf("Nhap so luong sinh vien muon them: ");
    scanf("%d", &soLuong);
    getchar();

    // Tạo thư mục data nếu chưa tồn tại
#ifdef _WIN32
    system("mkdir data 2> nul");
#else
    system("mkdir -p data");
#endif

    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("\nLoi: Khong the mo file de ghi!\n");
        return;
    }

    // Ghi số lượng sinh viên
    fprintf(file, "So luong sinh vien: %d\n\n", soLuong);

    // Nhập và ghi từng sinh viên
    for (int i = 0; i < soLuong; i++) {
        Student sv;
        printf("\nNhap thong tin sinh vien thu %d:\n", i + 1);

        printf("MSSV: ");
        scanf("%s", sv.id);
        getchar();

        printf("Ho ten: ");
        fgets(sv.name, sizeof(sv.name), stdin);
        sv.name[strcspn(sv.name, "\n")] = 0;

        printf("Tuoi: ");
        scanf("%d", &sv.age);

        printf("GPA: ");
        scanf("%f", &sv.gpa);
        getchar();

        // Ghi sinh viên vào file với định dạng có nhãn
        fprintf(file, "=== Sinh vien %d ===\n", i + 1);
        fprintf(file, "MSSV: %s\n", sv.id);
        fprintf(file, "Ho ten: %s\n", sv.name);
        fprintf(file, "Tuoi: %d\n", sv.age);
        fprintf(file, "GPA: %.2f\n\n", sv.gpa);
    }

    fclose(file);
    printf("\nDa luu %d sinh vien vao file!\n", soLuong);
}


void editStudent() {
    char searchId[20];
    int found = 0;

    printf("\n=== SUA THONG TIN SINH VIEN ===\n");
    printf("Nhap MSSV can sua: ");
    scanf("%s", searchId);
    getchar();

    // Tìm sinh viên theo ID
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, searchId) == 0) {
            // Hiển thị thông tin hiện tại
            printf("\nThong tin hien tai:\n");
            printf("MSSV: %s\n", students[i].id);
            printf("Ho ten: %s\n", students[i].name);
            printf("Tuoi: %d\n", students[i].age);
            printf("GPA: %.2f\n", students[i].gpa);

            // Nhập thông tin mới
            printf("\nNhap thong tin moi:\n");
            printf("Ho ten moi: ");
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = 0;

            printf("Tuoi moi: ");
            scanf("%d", &students[i].age);

            printf("GPA moi: ");
            scanf("%f", &students[i].gpa);
            getchar();

            found = 1;

            // Lưu vào file
            FILE *file = fopen(FILENAME, "w");
            if (file == NULL) {
                printf("\nLoi: Khong the mo file de ghi!\n");
                return;
            }

            // Ghi số lượng sinh viên
            fprintf(file, "So luong sinh vien: %d\n\n", studentCount);

            // Ghi lại toàn bộ danh sách
            for (int j = 0; j < studentCount; j++) {
                fprintf(file, "=== Sinh vien %d ===\n", j + 1);
                fprintf(file, "MSSV: %s\n", students[j].id);
                fprintf(file, "Ho ten: %s\n", students[j].name);
                fprintf(file, "Tuoi: %d\n", students[j].age);
                fprintf(file, "GPA: %.2f\n\n", students[j].gpa);
            }

            fclose(file);
            printf("\nDa cap nhat thong tin sinh vien thanh cong!\n");
            break;
        }
    }

    if (!found) {
        printf("\nKhong tim thay sinh vien co MSSV: %s\n", searchId);
    }
}

void saveToFile() {
    // Tạo thư mục data nếu chưa tồn tại
#ifdef _WIN32
    system("mkdir data 2> nul");
#else
    system("mkdir -p data");
#endif

    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) {
        printf("\nLoi: Khong the mo file de ghi. Error: %s\n", strerror(errno));
        return;
    }

    // Ghi số lượng sinh viên
    fwrite(&studentCount, sizeof(int), 1, file);
    // Ghi mảng sinh viên
    fwrite(students, sizeof(Student), studentCount, file);

    fclose(file);
    printf("\nDa luu du lieu vao file thanh cong!\n");
}

void loadFromFile() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("\nChua co du lieu sinh vien!\n");
        return;
    }

    // Đọc số lượng sinh viên
    char line[100];
    fgets(line, sizeof(line), file);
    sscanf(line, "So luong sinh vien: %d", &studentCount);
    fgets(line, sizeof(line), file); // Đọc dòng trống

    // Đọc thông tin từng sinh viên
    for (int i = 0; i < studentCount; i++) {
        fgets(line, sizeof(line), file); // Đọc dòng === Sinh vien x ===

        fgets(line, sizeof(line), file);
        sscanf(line, "MSSV: %s", students[i].id);

        fgets(line, sizeof(line), file);
        sscanf(line, "Ho ten: %[^\n]", students[i].name);

        fgets(line, sizeof(line), file);
        sscanf(line, "Tuoi: %d", &students[i].age);

        fgets(line, sizeof(line), file);
        sscanf(line, "GPA: %f", &students[i].gpa);

        fgets(line, sizeof(line), file); // Đọc dòng trống
    }

    fclose(file);
    printf("\nDa tai du lieu tu file thanh cong!\n");
}
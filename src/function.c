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
    printf("4. Xoa sinh vien\n");
    printf("5. Tim kiem sinh vien theo ten\n");
    printf("6. Sap xep danh sach theo ten\n");
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

    // Kiểm tra số lượng hợp lệ
    if (soLuong <= 0 || soLuong > 100) {
        printf("So luong sinh vien khong hop le (1-100)!\n");
        return;
    }

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
        do {
            printf("\nNhap thong tin sinh vien thu %d:\n", i + 1);

            printf("MSSV (8 ky tu): ");
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

        } while (!validateStudent(&sv));

        // Thêm sinh viên vào mảng
        students[studentCount++] = sv;

        // Ghi sinh viên vào file
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




// Xóa sinh viên
void deleteStudent() {
    char searchId[20];
    int found = 0;
    char confirm;

    printf("\n=== XOA SINH VIEN ===\n");
    printf("Nhap MSSV can xoa: ");
    scanf("%s", searchId);
    getchar();

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, searchId) == 0) {
            printf("\nThong tin sinh vien can xoa:\n");
            printf("MSSV: %s\n", students[i].id);
            printf("Ho ten: %s\n", students[i].name);
            printf("Tuoi: %d\n", students[i].age);
            printf("GPA: %.2f\n", students[i].gpa);

            printf("\nBan co chac chan muon xoa? (y/n): ");
            scanf("%c", &confirm);
            getchar();

            if (confirm == 'y' || confirm == 'Y') {
                // Dịch chuyển các phần tử
                for (int j = i; j < studentCount - 1; j++) {
                    students[j] = students[j + 1];
                }
                studentCount--;

                // Cập nhật file
                FILE *file = fopen(FILENAME, "w");
                if (file == NULL) {
                    printf("\nLoi: Khong the mo file de ghi!\n");
                    return;
                }

                fprintf(file, "So luong sinh vien: %d\n\n", studentCount);
                for (int j = 0; j < studentCount; j++) {
                    fprintf(file, "=== Sinh vien %d ===\n", j + 1);
                    fprintf(file, "MSSV: %s\n", students[j].id);
                    fprintf(file, "Ho ten: %s\n", students[j].name);
                    fprintf(file, "Tuoi: %d\n", students[j].age);
                    fprintf(file, "GPA: %.2f\n\n", students[j].gpa);
                }

                fclose(file);
                printf("\nDa xoa sinh vien thanh cong!\n");
            } else {
                printf("\nDa huy xoa sinh vien!\n");
            }
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nKhong tim thay sinh vien co MSSV: %s\n", searchId);
    }
}

// Tìm kiếm sinh viên theo tên
void searchStudentByName() {
    char searchName[50];
    int found = 0;

    printf("\n=== TIM KIEM SINH VIEN ===\n");
    printf("Nhap ten sinh vien can tim: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = 0;

    printf("\nKet qua tim kiem:\n");
    printf("%-10s %-30s %-10s %-10s\n", "MSSV", "Ho va ten", "Tuoi", "GPA");

    for (int i = 0; i < studentCount; i++) {
        if (strstr(students[i].name, searchName) != NULL) {
            printf("%-10s %-30s %-10d %-10.2f\n",
                students[i].id,
                students[i].name,
                students[i].age,
                students[i].gpa);
            found = 1;
        }
    }

    if (!found) {
        printf("\nKhong tim thay sinh vien nao!\n");
    }
}

// Menu sắp xếp
void displaySortMenu() {
    printf("\n=== SAP XEP THEO TEN ===\n");
    printf("1. Tang dan (A-Z)\n");
    printf("2. Giam dan (Z-A)\n");
    printf("Chon kieu sap xep: ");
}

// Sắp xếp sinh viên theo tên
void sortStudentsByName() {
    int choice;
    displaySortMenu();
    scanf("%d", &choice);
    getchar();

    // Sắp xếp bubble sort
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            int compare = strcmp(students[j].name, students[j + 1].name);
            if ((choice == 1 && compare > 0) || (choice == 2 && compare < 0)) {
                // Hoán đổi vị trí
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    printf("\nDanh sach sau khi sap xep:\n");
    displayStudents();

    // Cập nhật file
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("\nLoi: Khong the mo file de ghi!\n");
        return;
    }

    fprintf(file, "So luong sinh vien: %d\n\n", studentCount);
    for (int i = 0; i < studentCount; i++) {
        fprintf(file, "=== Sinh vien %d ===\n", i + 1);
        fprintf(file, "MSSV: %s\n", students[i].id);
        fprintf(file, "Ho ten: %s\n", students[i].name);
        fprintf(file, "Tuoi: %d\n", students[i].age);
        fprintf(file, "GPA: %.2f\n\n", students[i].gpa);
    }

    fclose(file);
}

// Kiểm tra dữ liệu sinh viên hợp lệ
int validateStudent(Student *student) {
    // Kiểm tra độ dài MSSV
    if (strlen(student->id) != 5) {
        printf("MSSV phai co 5 ky tu!\n");
        return 0;
    }

    // Kiểm tra tên không được trống
    if (strlen(student->name) < 2) {
        printf("Ten sinh vien khong hop le!\n");
        return 0;
    }

    // Kiểm tra tuổi hợp lệ
    if (student->age < 15 || student->age > 100) {
        printf("Tuoi sinh vien khong hop le!\n");
        return 0;
    }

    // Kiểm tra GPA hợp lệ
    if (student->gpa < 0 || student->gpa > 10) {
        printf("GPA khong hop le!\n");
        return 0;
    }

    // Kiểm tra MSSV trùng
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, student->id) == 0) {
            printf("MSSV da ton tai!\n");
            return 0;
        }
    }

    return 1;
}



void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printLine(int length) {
    for(int i = 0; i < length; i++) {
        printf("=");
    }
    printf("\n");
}

void waitForEnter() {
    printf("\nNhan Enter de tiep tuc...");
    getchar();
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
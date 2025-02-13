// khai bao nguyen mẫu hàm

#ifndef FUNCTION_H
#define FUNCTION_H
#include "datatype.h"

void displayMenu();
void displayStudents();
void addStudent();
void editStudent();
void deleteStudent();
void searchStudentByName();
void sortStudentsByName();
int validateStudent(Student *student);
void displaySortMenu();
void clearScreen();  // Xóa màn hình
void printLine(int length);  // In đường kẻ
void waitForEnter();  // Đợi người dùng nhấn Enter
void saveToFile();
void loadFromFile();
#endif //FUNCTION_H

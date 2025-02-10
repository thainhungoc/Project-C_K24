#include <stdio.h>
// #include "../Project C students management/include/function.h"
#include "include/function.h"

int main() {
    int choice;
    loadFromFile();  // Load existing data when program starts

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayStudents();
            break;
            case 2:
                addStudent();
            break;
            case 0:
                printf("\nCảm ơn bạn đã sử dụng chương trình!\n");
            break;
            default:
                printf("\nLựa chọn không hợp lệ!\n");
        }
    } while (choice != 0);

    return 0;
}
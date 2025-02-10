#include <stdio.h>
// #include "../Project C students management/include/function.h"
#include "include/function.h"

int main() {
    int choice;
    loadFromFile();

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
                printf("\nCam on ban da su dung chuong trinh\n");
            break;
            default:
                printf("\nLua chon khong hop le\n");
        }
    } while (choice != 0);

    return 0;
}
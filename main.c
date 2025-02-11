#include <stdio.h>
#include "src/function.c"

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
            case 3:
                editStudent();
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
#include <stdio.h>

#include "src/lab1/lab1.h"
#include "src/lab2/lab2.h"
#include "src/lab3/lab3.h"
#include "src/lab4/lab4.h"
#include "src/lab5/lab5.h"

int main(void) {
    int choice;
    char filename[256];

    do {
        printf("\nВыберите лабораторную работу (1–5) или 0 для выхода:\n");
        printf("1. Лабораторная 1\n");
        printf("2. Лабораторная 2\n");
        printf("3. Лабораторная 3\n");
        printf("4. Лабораторная 4\n");
        printf("5. Лабораторная 5\n");
        printf("0. Выход\n");
        printf("Ваш выбор: ");

        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            printf("Введите имя файла (например quest.txt): ");
            scanf("%s", filename);

            char path[256];
            sprintf(path, "src/lab1/%s", filename);

            lab1_main(2, (char* []) { "lab1", path });
            break;
        }

        case 2:
            lab2_main();
            break;

        case 3:
            lab3_main();
            break;

        case 4:
            lab4_main("src/lab4/input.txt");
            break;

        case 5:
            lab5_main("src/lab5/graph.txt");
            break;

        case 0:
            printf("Выход...\n");
            break;

        default:
            printf("Неверный выбор\n");
        }

    } while (choice != 0);

    return 0;
}
